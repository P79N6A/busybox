/*
// =====================================================================================
// 
//       Filename:  main.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/03/2016 07:29:15 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Elwin.Gao (elwin), elwin.gao4444@gmail.com
//        Company:  
// 
// =====================================================================================
*/

#include <unistd.h>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <iostream>

#include "zookeeper_class.hpp"
#include "watched_event_class.hpp"
using zkclass::ZooKeeper;
using zkclass::Watcher;
using zkclass::WatchedEvent;

const std::string server = "localhost:2181";

int global_watcher_trigger = 0;
class global_watcher : public Watcher
{
	void process(const WatchedEvent &event)
	{
		++global_watcher_trigger;
		std::cout << "global_watcher is triggered: " << "\t";
		std::cout << "event.path[" << event.path() << "]\t";
		std::cout << "event.type[" << event.type().c_str() << "]\t";
		std::cout << "event.state[" << event.state().c_str() << "]" << std::endl;
	}
};

class path_watcher : public Watcher
{
	void process(const WatchedEvent &event)
	{
		++global_watcher_trigger;
		std::cout << "path_watcher is triggered: " << "\t";
		std::cout << "event.path[" << event.path() << "]\t";
		std::cout << "event.type[" << event.type().c_str() << "]\t";
		std::cout << "event.state[" << event.state().c_str() << "]" << std::endl;
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
	// case1：无watcher，无old session
	ZooKeeper zk1(server, 1024, nullptr, nullptr);
	usleep(20*1000);	// 由于这里没有watcher监控状态，所以只能坐等session建立完成
	assert(zk1.get_state().value() == ZOO_CONNECTED_STATE);
	clientid_t id1 = *zk1.get_client_id();
	assert(id1.client_id != 0);
	assert(id1.passwd[0] != 0);
	assert(zk1.get_session_timeout() >= 4000 && zk1.get_session_timeout() <= 40000);	// 4s - 40s是zk的默认配置
//	assert(zk1.close().value() == ZOK);

	// case2：无watcher，有old session
	ZooKeeper zk2(server, 1024, nullptr, &id1);
	usleep(20*1000);	// 由于这里没有watcher监控状态，所以只能坐等session建立完成
	assert(zk2.get_state().value() == ZOO_CONNECTED_STATE);
	assert(zk1.get_state().value() != ZOO_CONNECTED_STATE);	// session重连会导致之前的session失效
	clientid_t id2 = *zk2.get_client_id();
	assert(id2.client_id != 0);
	assert(id2.passwd[0] != 0);
	assert(zk2.get_session_timeout() >= 4000 && zk2.get_session_timeout() <= 40000);	// 4s - 40s是zk的默认配置
	assert(zk2.close().value() == ZOK);

	assert(zk1.get_state().value() != ZOO_CONNECTED_STATE);	// session重连会导致之前的session失效
	assert(zk2.get_state().value() != ZOO_CONNECTED_STATE);

	// case3：有watcher，无old session
	global_watcher watcher3;
	ZooKeeper zk3(server, 1024, &watcher3, nullptr);
	usleep(20*1000);	// 这里等待一段时间，确保watcher可以被触发
	assert(zk3.get_state().value() == ZOO_CONNECTED_STATE);
	assert(global_watcher_trigger == 1);
	clientid_t id3 = *zk3.get_client_id();
	assert(id3.client_id != 0);
	assert(id3.passwd[0] != 0);
	assert(zk3.get_session_timeout() >= 4000 && zk3.get_session_timeout() <= 40000);	// 4s - 40s是zk的默认配置
	assert(zk3.close().value() == ZOK);

	// case4：有watcher，有old session
	global_watcher watcher4;
	ZooKeeper zk4(server, 1024, &watcher4, &id3);
	usleep(20*1000);	// 这里等待一段时间，确保watcher可以被触发
	// 通过watcher可以发现，close并没有使zk3的session过期，而重用session id使得zk3的session过期
	// zk3的ZOO_EXPIRED_SESSION_STATE状态仅在watcher中能看到，直接get_state无法检测到
	assert(zk4.get_state().value() != ZOO_CONNECTED_STATE);	// 错误的client_id无法建立连接
	assert(zk4.close().value() == ZOK);

	std::cout << "\e[32mTest: test_connect_and_close() OK\e[0m" << std::endl;
}		// -----  end of static function test_connect_and_close  -----

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
	ZooKeeper zk(server, 1024, &gwatcher, nullptr);
	usleep(20*1000);	// 由于这里没有watcher监控状态，所以只能坐等session建立完成
	assert(zk.get_state().value() == ZOO_CONNECTED_STATE);
	std::string path("/zkclass_test_create");
	Stat stat;
	vector<ACL> acl = {{ZOO_PERM_ALL, ZOO_ANYONE_ID_UNSAFE}};
	assert(zk.exists(path, true, &stat).value() == ZNONODE);	// true表示使用init时注册的global watcher进行监听
	assert(zk.exists(path, true, &stat).value() == ZNONODE);	// 同一个path，同一个watcher，即使多次注册，也只监听1次
	assert(zk.exists(path, &pwatcher, &stat).value() == ZNONODE);	// 除了使用global watcher，也可以自己指定watcher
	assert(zk.create(path, "root node", 9, acl, 0, nullptr).value() == ZOK);
	assert(zk.exists(path, false, &stat).value() == ZOK);	// global watcher也是一次性监听，如果需要则每次设置
	assert(zk.exists(path, &pwatcher, &stat).value() == ZOK);	// 同一个path，同一个watcher，即使多次注册，也只监听1次
	assert(zk.exists(path, &pwatcher, &stat).value() == ZOK);
	assert(zk.exists(path, &pwatcher2, &stat).value() == ZOK);	// 相同path，不同watcher，作为两个不同的监听，会依次触发
	assert(zk.remove(path, stat.version).value() == ZOK);
	assert(zk.exists(path, false, &stat).value() == ZNONODE);
	assert(zk.exists(path, &pwatcher, &stat).value() == ZNONODE);

	// 测试临时节点
	std::string path_ephemeral("/zkclass_test_ephemeral");
	assert(zk.exists(path_ephemeral, false, &stat).value() == ZNONODE);
	assert(zk.create(path_ephemeral, "ephemeral node", 14, acl, ZOO_EPHEMERAL, nullptr).value() == ZOK);
	assert(zk.exists(path_ephemeral, false, &stat).value() == ZOK);

	// 测试临时顺序节点
	std::string path_sequence("/zkclass_test_sequence");
	std::string new_path;
	assert(zk.exists(path_sequence, false, &stat).value() == ZNONODE);
	assert(zk.create(path_sequence, "sequence node", 14, acl, ZOO_EPHEMERAL|ZOO_SEQUENCE, &new_path).value() == ZOK);
	assert(zk.exists(new_path, false, &stat).value() == ZOK);
	std::cout << new_path << std::endl;

	std::cout << "\e[32mTest: test_create_and_remove() OK\e[0m" << std::endl;
}		// -----  end of static function test_create_and_remove  -----

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
	ZooKeeper zk(server, 1024, &gwatcher, nullptr);
	usleep(20*1000);	// 由于这里没有watcher监控状态，所以只能坐等session建立完成
	assert(zk.get_state().value() == ZOO_CONNECTED_STATE);
	std::string path("/zkclass_test_set_get");
	Stat stat;
	vector<ACL> acl = {{ZOO_PERM_ALL, ZOO_ANYONE_ID_UNSAFE}};
	char data[1024];
	int data_size = 1024;
	assert(zk.get_data(path, data, &data_size, true, nullptr).value() == ZNONODE);	// get_data并不能监听到create事件，且在节点创建之前，对节点内容的监听都是无效的
	assert(zk.create(path, "", 0, acl, ZOO_EPHEMERAL, nullptr).value() == ZOK);
	assert(zk.exists(path, false, &stat).value() == ZOK);	// global watcher也是一次性监听，如果需要则每次设置
	assert(zk.get_data(path, data, &data_size, true, nullptr).value() == ZOK);
	assert(data_size == 0);
	assert(zk.get_data(path, data, &data_size, &pwatcher, &stat).value() == ZOK);
	assert(data_size == 0);
	assert(zk.set_data(path, "abcd", 4, stat.version).value() == ZOK);
	data_size = 1024;
	assert(zk.get_data(path, data, &data_size, false, &stat).value() == ZOK);
	assert(data_size == 4);
	assert(strncmp(data, "abcd", data_size) == 0);
	data_size = 2;	// get_data的size参数，既是入参也是出参
	assert(zk.get_data(path, data, &data_size, false, &stat).value() == ZOK);
	std::cout << data << data_size << std::endl;
	assert(data_size == 2);
	assert(strncmp(data, "ab", data_size) == 0);
	assert(zk.get_data(path, data, &data_size, false, &stat).value() == ZOK);
	int version = stat.version;
	assert(zk.set_data(path, "abcde", 5, stat.version, &stat).value() == ZOK);
	assert(stat.version == version + 1);
	assert(zk.remove(path, stat.version).value() == ZOK);

	std::cout << "\e[32mTest: test_set_and_get() OK\e[0m" << std::endl;
}		// -----  end of static function test_set_and_get  -----

/* 
// ===  FUNCTION  ======================================================================
//         Name:  test_acl
//  Description:   
// =====================================================================================
*/
static void test_acl()
{
	std::cout << "\e[32mTest: test_acl() OK\e[0m" << std::endl;
}		// -----  end of static function test_acl  -----

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
	test_acl();
	std::cout << "\e[32mAll Test is OK\e[0m" << std::endl;
//	zhandle_t *m_zh = zookeeper_init("localhost:2181", nullptr, 4000, nullptr, nullptr, 0);
//	usleep(20*1000);
//	std::cout << zoo_create(m_zh, "/zkclass_test", "root node", 9, &ZOO_OPEN_ACL_UNSAFE, 0, NULL, 0) << std::endl;
//	std::cout << zoo_create(m_zh, "/zkclass_test_ephemeral", "ephemeral root", 14, &ZOO_OPEN_ACL_UNSAFE, ZOO_EPHEMERAL, NULL, 0) << std::endl;
//	std::cout << zoo_delete(m_zh, "/zkclass_test", -1) << std::endl;
//	zookeeper_close(m_zh);
	return EXIT_SUCCESS;
}				// ----------  end of function main  ----------

