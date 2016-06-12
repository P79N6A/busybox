/*
// =====================================================================================
// 
//       Filename:  main.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/03/2016 07:29:15 PM
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
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

#include "zookeeper_class.hpp"
#include "watched_event_class.hpp"
using zkclass::ZooKeeper;
using zkclass::Watcher;
using zkclass::WatchedEvent;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

#define wait_watcher() \
    pthread_mutex_lock(&mutex);\
    global_watcher_trigger = 0; \
    path_watcher_trigger = 0; \
    while (!(global_watcher_trigger | path_watcher_trigger)) { \
        pthread_cond_wait(&cond, &mutex); \
    } \
    pthread_mutex_unlock(&mutex); \

int Base64Encode(const unsigned char* buffer, size_t length, char** b64text) { //Encodes a binary safe base 64 string
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); //Ignore newlines - write everything in one line
    BIO_write(bio, buffer, length);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);
    BIO_set_close(bio, BIO_NOCLOSE);
    BIO_free_all(bio);

    *b64text=(*bufferPtr).data;

    return (0); //success
}

const std::string server = "localhost:2181";

int global_watcher_trigger = 0;
int path_watcher_trigger = 0;
class global_watcher : public Watcher
{
    void process(const WatchedEvent &event)
    {
        std::cout << "global_watcher is triggered: " << "\t";
        std::cout << "event.path[" << event.path() << "]\t";
        std::cout << "event.type[" << event.type().c_str() << "]\t";
        std::cout << "event.state[" << event.state().c_str() << "]" << std::endl;
        if (event.type() == ZOO_SESSION_EVENT) {
            pthread_mutex_lock(&mutex);
            global_watcher_trigger = 1;
            pthread_cond_signal(&cond);
            pthread_mutex_unlock(&mutex);
        }
    }
};

class path_watcher : public Watcher
{
    void process(const WatchedEvent &event)
    {
        ++path_watcher_trigger;
        std::cout << "path_watcher is triggered: " << "\t";
        std::cout << "event.path[" << event.path() << "]\t";
        std::cout << "event.type[" << event.type().c_str() << "]\t";
        std::cout << "event.state[" << event.state().c_str() << "]" << std::endl;
        if (event.type() == ZOO_SESSION_EVENT) {
            pthread_mutex_lock(&mutex);
            path_watcher_trigger = 1;
            pthread_cond_signal(&cond);
            pthread_mutex_unlock(&mutex);
        }
    }
};

/* 
// ===  FUNCTION  ======================================================================
//         Name:  test_connect_and_close
//  Description:   
// =====================================================================================
*/
static void test_connect_and_close()
{
    // case0：测试host异常
    ZooKeeper zk_error1("invalid string", 1024, nullptr);
    usleep(100*1000);    // 由于这里没有watcher监控状态，所以只能坐等session建立完成
    assert(zk_error1.get_state() != ZOO_CONNECTED_STATE);

    ZooKeeper zk_error2("localhost:65535", 1024, nullptr);
    usleep(100*1000);    // 由于这里没有watcher监控状态，所以只能坐等session建立完成
    assert(zk_error2.get_state() != ZOO_CONNECTED_STATE);

    // case1：无watcher，无old session
    ZooKeeper zk1(server, 1024, nullptr);
    usleep(100*1000);    // 由于这里没有watcher监控状态，所以只能坐等session建立完成
    assert(zk1.get_state() == ZOO_CONNECTED_STATE);
    clientid_t id1 = *zk1.get_client_id();
    assert(id1.client_id != 0);
    assert(id1.passwd[0] != 0);
    assert(zk1.get_session_timeout() >= 4000 && zk1.get_session_timeout() <= 40000);    // 4s - 40s是zk的默认配置
//    assert(zk1.close() == ZOK);

    // case2：无watcher，有old session
    ZooKeeper zk2(server, 1024, nullptr, &id1);
    usleep(100*1000);    // 由于这里没有watcher监控状态，所以只能坐等session建立完成
    assert(zk2.get_state() == ZOO_CONNECTED_STATE);
    assert(zk1.get_state() != ZOO_CONNECTED_STATE);    // session重连会导致之前的session失效
    clientid_t id2 = *zk2.get_client_id();
    assert(id2.client_id != 0);
    assert(id2.passwd[0] != 0);
    assert(zk2.get_session_timeout() >= 4000 && zk2.get_session_timeout() <= 40000);    // 4s - 40s是zk的默认配置
    assert(zk2.close() == ZOK);

    assert(zk1.get_state() != ZOO_CONNECTED_STATE);    // session重连会导致之前的session失效
    assert(zk2.get_state() != ZOO_CONNECTED_STATE);

    // case3：有watcher，无old session
    global_watcher watcher3;
    ZooKeeper zk3(server, 1024, &watcher3);
    wait_watcher();
    assert(zk3.get_state() == ZOO_CONNECTED_STATE);
    assert(global_watcher_trigger == 1);
    clientid_t id3 = *zk3.get_client_id();
    assert(id3.client_id != 0);
    assert(id3.passwd[0] != 0);
    assert(zk3.get_session_timeout() >= 4000 && zk3.get_session_timeout() <= 40000);    // 4s - 40s是zk的默认配置
    assert(zk3.close() == ZOK);

    // case4：有watcher，有old session
    global_watcher watcher4;
    ZooKeeper zk4(server, 1024, &watcher4, &id3);
    wait_watcher();
    // 通过watcher可以发现，close并没有使zk3的session过期，而重用session id使得zk3的session过期
    // zk3的ZOO_EXPIRED_SESSION_STATE状态仅在watcher中能看到，直接get_state无法检测到
    assert(zk4.get_state() != ZOO_CONNECTED_STATE);    // 错误的client_id无法建立连接
    assert(zk4.close() == ZOK);

    std::cout << "\e[32mTest: test_connect_and_close() OK\e[0m" << std::endl;
}        // -----  end of static function test_connect_and_close  -----

/* 
// ===  FUNCTION  ======================================================================
//         Name:  test_create_and_remove
//  Description:   
// =====================================================================================
*/
static void test_create_and_remove()
{
    global_watcher gwatcher;
    path_watcher pwatcher;
    path_watcher pwatcher2;

    // 测试普通节点
    ZooKeeper zk(server, 1024, &gwatcher);
    wait_watcher();
    assert(zk.get_state() == ZOO_CONNECTED_STATE);
    std::string path("/zkclass_test_create");
    Stat stat;
    std::vector<ACL> acl = {{ZOO_PERM_ALL, ZOO_ANYONE_ID_UNSAFE}};
    assert(zk.exists(path, true) == ZNONODE);    // true表示使用init时注册的global watcher进行监听
    assert(zk.exists(path, true) == ZNONODE);    // 同一个path，同一个watcher，即使多次注册，也只监听1次
    assert(zk.exists(path, &pwatcher) == ZNONODE);    // 除了使用global watcher，也可以自己指定watcher
    assert(zk.create(path, std::string("root node"), acl) == ZOK);
    assert(zk.exists(path) == ZOK);    // global watcher也是一次性监听，如果需要则每次设置
    assert(zk.exists(path, &pwatcher) == ZOK);    // 同一个path，同一个watcher，即使多次注册，也只监听1次
    assert(zk.exists(path, &pwatcher) == ZOK);
    assert(zk.exists(path, &pwatcher2, &stat) == ZOK);    // 相同path，不同watcher，作为两个不同的监听，会依次触发
    assert(zk.exists(path, &stat) == ZOK);
    assert(zk.remove(path, stat.version) == ZOK);
    assert(zk.exists(path) == ZNONODE);

    // 测试临时节点
    std::string path_ephemeral("/zkclass_test_ephemeral");
    assert(zk.exists(path_ephemeral) == ZNONODE);
    assert(zk.create(path_ephemeral, std::string("ephemeral node"), acl, ZOO_EPHEMERAL) == ZOK);
    assert(zk.exists(path_ephemeral) == ZOK);

    // 测试临时顺序节点
    std::string path_sequence("/zkclass_test_sequence");
    std::string new_path;
    assert(zk.exists(path_sequence) == ZNONODE);
    assert(zk.create(path_sequence, std::string("sequence node"), acl, ZOO_EPHEMERAL|ZOO_SEQUENCE, &new_path) == ZOK);
    assert(zk.exists(new_path) == ZOK);
    std::cout << new_path << std::endl;

    std::cout << "\e[32mTest: test_create_and_remove() OK\e[0m" << std::endl;
}        // -----  end of static function test_create_and_remove  -----

/* 
// ===  FUNCTION  ======================================================================
//         Name:  test_set_and_get
//  Description:   
// =====================================================================================
*/
static void test_set_and_get()
{
    global_watcher gwatcher;
    path_watcher pwatcher;
    ZooKeeper zk(server, 1024, &gwatcher);
    wait_watcher();
    assert(zk.get_state() == ZOO_CONNECTED_STATE);
    std::string path("/zkclass_test_set_get");
    Stat stat;
    std::vector<ACL> acl = {{ZOO_PERM_ALL, ZOO_ANYONE_ID_UNSAFE}};
    std::string data;
    assert(zk.get_data(path, &data, true) == ZNONODE);    // get_data并不能监听到create事件，且在节点创建之前，对节点内容的监听都是无效的
    assert(zk.create(path, std::string(), acl, ZOO_EPHEMERAL) == ZOK);
    assert(zk.exists(path) == ZOK);
    assert(zk.get_data(path, &data, true) == ZOK);
    assert(data.size() == 0);
    assert(zk.get_data(path, &data, &pwatcher, &stat) == ZOK);
    assert(data.size() == 0);
    assert(zk.set_data(path, std::string("abcd"), stat.version) == ZOK);
    assert(zk.get_data(path, &data) == ZOK);
    assert(data.size() == 4);
    assert(data == "abcd");
    assert(zk.get_data(path, &data, &stat) == ZOK);
    int version = stat.version;
    assert(zk.set_data(path, std::string("abcde"), stat.version, &stat) == ZOK);
    assert(stat.version == version + 1);
    assert(zk.remove(path, stat.version) == ZOK);

    std::cout << "\e[32mTest: test_set_and_get() OK\e[0m" << std::endl;
}        // -----  end of static function test_set_and_get  -----

/* 
// ===  FUNCTION  ======================================================================
//         Name:  test_get_children
//  Description:   
// =====================================================================================
*/
static void test_get_children()
{
    global_watcher gwatcher;
    path_watcher pwatcher;
    ZooKeeper zk(server, 1024, &gwatcher);
    wait_watcher();
    assert(zk.get_state() == ZOO_CONNECTED_STATE);
    std::string path("/zkclass_test_get_children");
    Stat stat;
    std::vector<ACL> acl = {{ZOO_PERM_ALL, ZOO_ANYONE_ID_UNSAFE}};
    std::vector<std::string> list;
    assert(zk.create(path, std::string(), acl) == ZOK);    // 为什么这一行会导致valgrind内存泄漏：possibly lost
    assert(zk.create(path+"/a", std::string(), acl, ZOO_EPHEMERAL) == ZOK);
    assert(zk.create(path+"/b", std::string(), acl, ZOO_EPHEMERAL) == ZOK);
    assert(zk.create(path+"/c", std::string(), acl, ZOO_EPHEMERAL) == ZOK);
    assert(zk.create(path+"/d", std::string(), acl, ZOO_EPHEMERAL) == ZOK);
    assert(zk.get_children(path, &list, false) == ZOK);
    assert(list.size() == 4);
    assert(zk.remove(path+"/a", -1) == ZOK);
    list.clear();
    assert(zk.get_children(path, &list, false, &stat) == ZOK);
    assert(list.size() == 3);
    assert(zk.remove(path+"/b", -1) == ZOK);
    list.clear();
    assert(zk.get_children(path, &list, &pwatcher) == ZOK);
    assert(list.size() == 2);
    assert(zk.remove(path+"/c", -1) == ZOK);
    list.clear();
    assert(zk.get_children(path, &list, &pwatcher, &stat) == ZOK);
    assert(list.size() == 1);
    assert(zk.remove(path+"/d", -1) == ZOK);
    assert(zk.remove(path, -1) == ZOK);    // 为什么这一行会导致valgrind内存泄漏？
    std::cout << "\e[32mTest: test_get_children() OK\e[0m" << std::endl;
}        // -----  end of static function test_get_children  -----

/* 
// ===  FUNCTION  ======================================================================
//         Name:  test_acl
//  Description:   
// =====================================================================================
*/
static void test_acl()
{
    global_watcher gwatcher;
    std::vector<ACL> acl = {{ZOO_PERM_ALL&~ZOO_PERM_WRITE, ZOO_ANYONE_ID_UNSAFE}};
    Stat stat;
    ZooKeeper zk(server, 1024, &gwatcher);
    std::string path("/zkclass_test_acl");
    wait_watcher();
    assert(zk.get_state() == ZOO_CONNECTED_STATE);
    assert(zk.create(path, std::string("acl node"), acl) == ZOK);    // 为什么这一行会导致valgrind内存泄漏：possibly lost
    acl.clear();
    assert(zk.get_acl(path, &acl, &stat) == ZOK);
    assert(acl.size() == 1);
    assert(acl[0].perms == (ZOO_PERM_ALL&~ZOO_PERM_WRITE));
    assert(strcmp(acl[0].id.scheme, "world") == 0);
    assert(strcmp(acl[0].id.id, "anyone") == 0);
    acl.push_back({ZOO_PERM_WRITE, {"digest", "test:V28q/NynI4JI3Rk54h0r8O5kMug="}});
    assert(zk.set_acl(path, acl, stat.version) == ZOK);
    acl.clear();
    assert(zk.get_acl(path, &acl) == ZOK);
    assert(acl.size() == 2);
    assert(acl[1].perms == ZOO_PERM_WRITE);
    assert(strcmp(acl[1].id.scheme, "digest") == 0);    // digest类型的id格式为："user:base64(sha1("user:passwd"))"
    assert(strcmp(acl[1].id.id, "test:V28q/NynI4JI3Rk54h0r8O5kMug=") == 0);
    assert(zk.set_data(path, std::string("acl write"), -1) == ZNOAUTH);
    assert(zk.add_auth_info("digest", "test:test") == ZOK);
    assert(zk.set_data(path, std::string("acl write"), -1) == ZOK);
    assert(zk.remove(path, -1) == ZOK);    // 为什么这一行会导致valgrind内存泄漏？
    std::cout << "\e[32mTest: test_acl() OK\e[0m" << std::endl;
}        // -----  end of static function test_acl  -----

/* 
// ===  FUNCTION  ======================================================================
//         Name:  test_watcher
//  Description:   
// =====================================================================================
*/
static void test_watcher()
{
    global_watcher gwatcher;
    path_watcher pwatcher;
    ZooKeeper zk(server, 1024, &gwatcher);
    zk.register_watcher(&pwatcher);
    wait_watcher();
    assert(global_watcher_trigger == 0);
    assert(path_watcher_trigger == 1);
    std::cout << "\e[32mTest: test_watcher() OK\e[0m" << std::endl;
}        // -----  end of static function test_watcher  -----

/* 
// ===  FUNCTION  ======================================================================
//         Name:  main
//  Description:  
// =====================================================================================
*/
int main(int argc, char *argv[])
{
    test_connect_and_close();
    test_create_and_remove();
    test_set_and_get();
    test_get_children();
    test_acl();
    test_watcher();
    std::cout << "\e[32mAll Test is OK\e[0m" << std::endl;

//  zhandle_t *m_zh = zookeeper_init("localhost:2181", nullptr, 4000, nullptr, nullptr, 0);
//  usleep(20*1000);
//  std::cout << zoo_create(m_zh, "/zkclass_test", "root node", 9, &ZOO_OPEN_ACL_UNSAFE, 0, NULL, 0) << std::endl;
//  std::cout << zoo_create(m_zh, "/zkclass_test_ephemeral", "ephemeral root", 14, &ZOO_OPEN_ACL_UNSAFE, ZOO_EPHEMERAL, NULL, 0) << std::endl;
//  std::cout << zoo_delete(m_zh, "/zkclass_test", -1) << std::endl;
//  zookeeper_close(m_zh);

//  const unsigned char input[] = "test:test";
//  unsigned char output[SHA_DIGEST_LENGTH];
//  SHA1(input, strlen((const char*)input), output);
//  std::cout << output << std::endl;
//  char* base64EncodeOutput;
//  Base64Encode(output, SHA_DIGEST_LENGTH, &base64EncodeOutput);
//  std::cout << base64EncodeOutput << std::endl;
    return EXIT_SUCCESS;
}                // ----------  end of function main  ----------

