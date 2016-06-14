/*
// =====================================================================================
// 
//       Filename:  test_zookeeper.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/12/2016 07:39:56 PM
//       Revision:  All Rights Reserved
//       Compiler:  g++
// 
//         Author:  gaowei08@baidu.com
//        Company:  Baidu.com, Inc.
// 
// =====================================================================================
*/

#include <unistd.h>
#include <pthread.h>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <iostream>

#include <gtest/gtest.h>

#include "cppcurator/zookeeper.h"
#include "cppcurator/watched_event.h"

using cppcurator::ZooKeeper;
using cppcurator::Watcher;
using cppcurator::WatchedEvent;
using cppcurator::ZKACL;

static pthread_mutex_t s_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t s_cond = PTHREAD_COND_INITIALIZER;

#define wait_watcher() \
    pthread_mutex_lock(&s_mutex);\
    s_global_watcher_trigger = 0; \
    s_path_watcher_trigger = 0; \
    while (!(s_global_watcher_trigger | s_path_watcher_trigger)) { \
        pthread_cond_wait(&s_cond, &s_mutex); \
    } \
    pthread_mutex_unlock(&s_mutex);

static const std::string server = "localhost:2181";

static int s_global_watcher_trigger = 0;
static int s_path_watcher_trigger = 0;

class GlobalWatcher : public Watcher
{
    void process(const WatchedEvent &event)
    {
        std::cout << "GlobalWatcher is triggered: " << "\t";
        std::cout << "event.path[" << event.path() << "]\t";
        std::cout << "event.type[" << event.type().desc() << "]\t";
        std::cout << "event.state[" << event.state().desc() << "]" << std::endl;
        if (event.type() == ZOO_SESSION_EVENT) {
            pthread_mutex_lock(&s_mutex);
            s_global_watcher_trigger = 1;
            pthread_cond_signal(&s_cond);
            pthread_mutex_unlock(&s_mutex);
        }
    }
};

class PathWatcher : public Watcher
{
    void process(const WatchedEvent &event)
    {
        ++s_path_watcher_trigger;
        std::cout << "PathWatcher is triggered: " << "\t";
        std::cout << "event.path[" << event.path() << "]\t";
        std::cout << "event.type[" << event.type().desc() << "]\t";
        std::cout << "event.state[" << event.state().desc() << "]" << std::endl;
        if (event.type() == ZOO_SESSION_EVENT) {
            pthread_mutex_lock(&s_mutex);
            s_path_watcher_trigger = 1;
            pthread_cond_signal(&s_cond);
            pthread_mutex_unlock(&s_mutex);
        }
    }
};

class TestZooKeeperClass : public ::testing::Test
{
public:
    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

/* 
// ===  FUNCTION  ======================================================================
//         Name:  test_connect_and_close
//  Description:   
// =====================================================================================
*/
TEST_F(TestZooKeeperClass, test_connect_and_close)
{
    // case0：测试host异常
    ZooKeeper zk_error1("invalid string", 1024, nullptr);
    usleep(100*1000);    // 由于这里没有watcher监控状态，所以只能坐等session建立完成
    EXPECT_NE(zk_error1.get_state(), ZOO_CONNECTED_STATE);

    ZooKeeper zk_error2("localhost:65535", 1024, nullptr);
    usleep(100*1000);    // 由于这里没有watcher监控状态，所以只能坐等session建立完成
    EXPECT_NE(zk_error2.get_state(), ZOO_CONNECTED_STATE);

    // case1：无watcher，无old session
    ZooKeeper zk1(server, 1024, nullptr);
    usleep(100*1000);    // 由于这里没有watcher监控状态，所以只能坐等session建立完成
    EXPECT_EQ(zk1.get_state(), ZOO_CONNECTED_STATE);
    clientid_t id1 = *zk1.get_client_id();
    EXPECT_NE(id1.client_id, 0);
    EXPECT_NE(id1.passwd[0], 0);
    EXPECT_TRUE(zk1.get_session_timeout() >= 4000 && zk1.get_session_timeout() <= 40000);    // 4s - 40s是zk的默认配置

    // case2：无watcher，有old session
    ZooKeeper zk2(server, 1024, nullptr, &id1);
    usleep(100*1000);    // 由于这里没有watcher监控状态，所以只能坐等session建立完成
    EXPECT_EQ(zk2.get_state(), ZOO_CONNECTED_STATE);
    EXPECT_NE(zk1.get_state(), ZOO_CONNECTED_STATE);    // session重连会导致之前的session失效
    clientid_t id2 = *zk2.get_client_id();
    EXPECT_NE(id2.client_id, 0);
    EXPECT_NE(id2.passwd[0], 0);
    EXPECT_TRUE(zk2.get_session_timeout() >= 4000 && zk2.get_session_timeout() <= 40000);    // 4s - 40s是zk的默认配置
    EXPECT_EQ(zk2.close(), ZOK);

    EXPECT_NE(zk1.get_state(), ZOO_CONNECTED_STATE);    // session重连会导致之前的session失效
    EXPECT_NE(zk2.get_state(), ZOO_CONNECTED_STATE);

    // case3：有watcher，无old session
    GlobalWatcher watcher3;
    ZooKeeper zk3(server, 1024, &watcher3);
    wait_watcher();
    EXPECT_EQ(zk3.get_state(), ZOO_CONNECTED_STATE);
    EXPECT_EQ(s_global_watcher_trigger, 1);
    clientid_t id3 = *zk3.get_client_id();
    EXPECT_NE(id3.client_id, 0);
    EXPECT_NE(id3.passwd[0], 0);
    EXPECT_TRUE(zk3.get_session_timeout() >= 4000 && zk3.get_session_timeout() <= 40000);    // 4s - 40s是zk的默认配置
    EXPECT_EQ(zk3.close(), ZOK);

    // case4：有watcher，有old session
    GlobalWatcher watcher4;
    ZooKeeper zk4(server, 1024, &watcher4, &id3);
    wait_watcher();
    // 通过watcher可以发现，close并没有使zk3的session过期，而重用session id使得zk3的session过期
    // zk3的ZOO_EXPIRED_SESSION_STATE状态仅在watcher中能看到，直接get_state无法检测到
    EXPECT_NE(zk4.get_state(), ZOO_CONNECTED_STATE);    // 错误的client_id无法建立连接
    EXPECT_EQ(zk4.close(), ZOK);
}

/* 
// ===  FUNCTION  ======================================================================
//         Name:  test_create_and_remove
//  Description:   
// =====================================================================================
*/
TEST_F(TestZooKeeperClass, test_create_and_remove)
{
    GlobalWatcher gwatcher;
    PathWatcher pwatcher;
    PathWatcher pwatcher2;

    // 测试普通节点
    ZooKeeper zk(server, 1024, &gwatcher);
    wait_watcher();
    EXPECT_EQ(zk.get_state(), ZOO_CONNECTED_STATE);
    std::string path("/zkclass_test_create");
    Stat stat;
    std::vector<ZKACL> acl = {{ZOO_PERM_ALL, "world", "anyone"}};
    EXPECT_EQ(zk.exists(path, true), ZNONODE);    // true表示使用init时注册的global watcher进行监听
    EXPECT_EQ(zk.exists(path, true), ZNONODE);    // 同一个path，同一个watcher，即使多次注册，也只监听1次
    EXPECT_EQ(zk.exists(path, &pwatcher), ZNONODE);    // 除了使用global watcher，也可以自己指定watcher
    EXPECT_EQ(zk.create(path, std::string("root node"), acl), ZOK);
    EXPECT_EQ(zk.exists(path), ZOK);    // global watcher也是一次性监听，如果需要则每次设置
    EXPECT_EQ(zk.exists(path, &pwatcher), ZOK);    // 同一个path，同一个watcher，即使多次注册，也只监听1次
    EXPECT_EQ(zk.exists(path, &pwatcher), ZOK);
    EXPECT_EQ(zk.exists(path, &pwatcher2, &stat), ZOK);    // 相同path，不同watcher，作为两个不同的监听，会依次触发
    EXPECT_EQ(zk.exists(path, &stat), ZOK);
    EXPECT_EQ(zk.remove(path, stat.version), ZOK);
    EXPECT_EQ(zk.exists(path), ZNONODE);

    // 测试临时节点
    std::string path_ephemeral("/zkclass_test_ephemeral");
    EXPECT_EQ(zk.exists(path_ephemeral), ZNONODE);
    EXPECT_EQ(zk.create(path_ephemeral, std::string("ephemeral node"), acl, ZOO_EPHEMERAL), ZOK);
    EXPECT_EQ(zk.exists(path_ephemeral), ZOK);

    // 测试临时顺序节点
    std::string path_sequence("/zkclass_test_sequence");
    std::string new_path;
    EXPECT_EQ(zk.exists(path_sequence), ZNONODE);
    EXPECT_EQ(zk.create(path_sequence, std::string("sequence node"), acl, ZOO_EPHEMERAL|ZOO_SEQUENCE, &new_path), ZOK);
    EXPECT_EQ(zk.exists(new_path), ZOK);
    std::cout << new_path << std::endl;

}

/* 
// ===  FUNCTION  ======================================================================
//         Name:  test_set_and_get
//  Description:   
// =====================================================================================
*/
TEST_F(TestZooKeeperClass, test_set_and_get)
{
    GlobalWatcher gwatcher;
    PathWatcher pwatcher;
    ZooKeeper zk(server, 1024, &gwatcher);
    wait_watcher();
    EXPECT_EQ(zk.get_state(), ZOO_CONNECTED_STATE);
    std::string path("/zkclass_test_set_get");
    Stat stat;
    std::vector<ZKACL> acl = {{ZOO_PERM_ALL, "world", "anyone"}};
    std::string data;
    EXPECT_EQ(zk.get_data(path, &data, true), ZNONODE);    // get_data并不能监听到create事件，且在节点创建之前，对节点内容的监听都是无效的
    EXPECT_EQ(zk.create(path, std::string(), acl, ZOO_EPHEMERAL), ZOK);
    EXPECT_EQ(zk.exists(path), ZOK);
    EXPECT_EQ(zk.get_data(path, &data, true), ZOK);
    EXPECT_EQ(data.size(), 0);
    EXPECT_EQ(zk.get_data(path, &data, &pwatcher, &stat), ZOK);
    EXPECT_EQ(data.size(), 0);
    EXPECT_EQ(zk.set_data(path, std::string("abcdefghijklmnopqrstuvwxyz"), stat.version), ZOK);
    EXPECT_EQ(zk.get_data(path, &data), ZOK);
    EXPECT_EQ(data.size(), 26);
    EXPECT_EQ(data, "abcdefghijklmnopqrstuvwxyz");
    EXPECT_EQ(zk.get_data(path, &data, &stat), ZOK);
    int version = stat.version;
    EXPECT_EQ(zk.set_data(path, std::string("abcdefghijklmnopqrstuvwxyz"), stat.version, &stat), ZOK);
    EXPECT_EQ(stat.version, version + 1);
    EXPECT_EQ(zk.remove(path, stat.version), ZOK);
}

/* 
// ===  FUNCTION  ======================================================================
//         Name:  test_get_children
//  Description:   
// =====================================================================================
*/
TEST_F(TestZooKeeperClass, test_get_children)
{
    GlobalWatcher gwatcher;
    PathWatcher pwatcher;
    ZooKeeper zk(server, 1024, &gwatcher);
    wait_watcher();
    std::vector<ZKACL> acl = {{ZOO_PERM_ALL, "world", "anyone"}};
    std::string path("/zkclass_test_get_children");
    Stat stat;
    std::vector<std::string> list;
    EXPECT_EQ(zk.create(path, std::string(), acl), ZOK);    // 为什么这一行会导致valgrind内存泄漏：possibly lost
    EXPECT_EQ(zk.create(path+"/a", std::string(), acl, ZOO_EPHEMERAL), ZOK);
    EXPECT_EQ(zk.create(path+"/b", std::string(), acl, ZOO_EPHEMERAL), ZOK);
    EXPECT_EQ(zk.create(path+"/c", std::string(), acl, ZOO_EPHEMERAL), ZOK);
    EXPECT_EQ(zk.create(path+"/d", std::string(), acl, ZOO_EPHEMERAL), ZOK);
    EXPECT_EQ(zk.get_children(path, &list, false), ZOK);
    EXPECT_EQ(list.size(), 4);
    EXPECT_EQ(zk.remove(path+"/a", -1), ZOK);
    list.clear();
    EXPECT_EQ(zk.get_children(path, &list, false, &stat), ZOK);
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(zk.remove(path+"/b", -1), ZOK);
    list.clear();
    EXPECT_EQ(zk.get_children(path, &list, &pwatcher), ZOK);    // tcmalloc检测内存泄漏
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(zk.remove(path+"/c", -1), ZOK);
    list.clear();
    EXPECT_EQ(zk.get_children(path, &list, &pwatcher, &stat), ZOK);    // tcmalloc检测内存泄漏
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(zk.remove(path+"/d", -1), ZOK);
    EXPECT_EQ(zk.remove(path, -1), ZOK);    // 为什么这一行会导致valgrind内存泄漏？
}

/* 
// ===  FUNCTION  ======================================================================
//         Name:  test_acl
//  Description:   
// =====================================================================================
*/
TEST_F(TestZooKeeperClass, test_acl)
{
    GlobalWatcher gwatcher;
    std::vector<ZKACL> acl = {{(ZOO_PERM_ALL&~ZOO_PERM_WRITE), "world", "anyone"}};
    Stat stat;
    ZooKeeper zk(server, 1024, &gwatcher);
    std::string path("/zkclass_test_acl");
    wait_watcher();    // tcmalloc检测内存泄漏
    EXPECT_EQ(zk.get_state(), ZOO_CONNECTED_STATE);
    EXPECT_EQ(zk.create(path, std::string("acl node"), acl), ZOK);    // 为什么这一行会导致valgrind内存泄漏：possibly lost
    acl.clear();
    EXPECT_EQ(zk.get_acl(path, &acl, &stat), ZOK);
    EXPECT_EQ(acl.size(), 1);
    EXPECT_EQ(acl[0].perms(), (ZOO_PERM_ALL&~ZOO_PERM_WRITE));
    EXPECT_EQ(acl[0].scheme(), std::string("world"));
    EXPECT_EQ(acl[0].id(), std::string("anyone"));
    acl.push_back({ZOO_PERM_WRITE, "digest", "test:V28q/NynI4JI3Rk54h0r8O5kMug="});
    EXPECT_EQ(zk.set_acl(path, acl, stat.version), ZOK);
    acl.clear();
    EXPECT_EQ(zk.get_acl(path, &acl), ZOK);
    EXPECT_EQ(acl.size(), 2);    // tcmalloc检测内存泄漏
    EXPECT_EQ(acl[1].perms(), ZOO_PERM_WRITE);
    EXPECT_EQ(acl[1].scheme(), std::string("digest"));    // digest类型的id格式为："user:base64(sha1("user:passwd"))"
    EXPECT_EQ(acl[1].id(), std::string("test:V28q/NynI4JI3Rk54h0r8O5kMug="));
    EXPECT_EQ(zk.set_data(path, std::string("acl write"), -1), ZNOAUTH);
    EXPECT_EQ(zk.add_auth_info("digest", "test:test"), ZOK);
    EXPECT_EQ(zk.set_data(path, std::string("acl write"), -1), ZOK);
    EXPECT_EQ(zk.remove(path, -1), ZOK);    // 为什么这一行会导致valgrind内存泄漏？
}

/* 
// ===  FUNCTION  ======================================================================
//         Name:  test_watcher
//  Description:   
// =====================================================================================
*/
TEST_F(TestZooKeeperClass, test_watcher)
{
    GlobalWatcher gwatcher;
    PathWatcher pwatcher;
    ZooKeeper zk(server, 1024, &gwatcher);
    zk.register_watcher(&pwatcher);
    wait_watcher();    // tcmalloc检测内存泄漏
    EXPECT_EQ(s_global_watcher_trigger, 0);
    EXPECT_EQ(s_path_watcher_trigger, 1);
}

