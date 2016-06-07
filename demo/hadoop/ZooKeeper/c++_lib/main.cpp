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

int mywatcher_trigger = 0;
class mywatcher : public Watcher
{
	void process(const WatchedEvent &event)
	{
		++mywatcher_trigger;
		std::cout << "mywatcher is  triggered" << std::endl;
		std::cout << "event.path:" << event.path() << std::endl;
		std::cout << "event.type:" << event.type().c_str() << std::endl;
		std::cout << "event.state:" << event.state().c_str() << std::endl;
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
	ZooKeeper zk1(server, 1024, nullptr);
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
	mywatcher watcher3;
	ZooKeeper zk3(server, 1024, &watcher3);
	usleep(20*1000);	// 这里等待一段时间，确保watcher可以被触发
	assert(zk3.get_state().value() == ZOO_CONNECTED_STATE);
	assert(mywatcher_trigger == 1);
	clientid_t id3 = *zk3.get_client_id();
	assert(id3.client_id != 0);
	assert(id3.passwd[0] != 0);
	assert(zk3.get_session_timeout() >= 4000 && zk3.get_session_timeout() <= 40000);	// 4s - 40s是zk的默认配置
	assert(zk3.close().value() == ZOK);

	// case4：有watcher，有old session
	mywatcher watcher4;
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
	ZooKeeper zk(server, 1024, nullptr);
	usleep(20*1000);	// 由于这里没有watcher监控状态，所以只能坐等session建立完成
	assert(zk.get_state().value() == ZOO_CONNECTED_STATE);
	std::string path("/zkclass_test");
	vector<ACL> acl = {{ZOO_PERM_ALL, ZOO_ANYONE_ID_UNSAFE}};
	assert(zk.create(path, "root node", acl, 0, nullptr).value() == ZOK);
	assert(zk.remove(path, -1).value() == ZOK);
}		// -----  end of static function test_create_and_remove  -----

/* 
// ===  FUNCTION  ======================================================================
//         Name:  main
//  Description:  
// =====================================================================================
*/
int main(int argc, char *argv[])
{
//	test_connect_and_close();
	test_create_and_remove();
	std::cout << "\e[32mAll Test is OK\e[0m" << std::endl;
//	zhandle_t *m_zh = zookeeper_init("localhost:2181", nullptr, 4000, nullptr, nullptr, 0);
//	usleep(20*1000);
//	std::cout << zoo_create(m_zh, "/zkclass_test", "root node", 9, &ZOO_OPEN_ACL_UNSAFE, 0, NULL, 0) << std::endl;
//	std::cout << zoo_delete(m_zh, "/zkclass_test", -1) << std::endl;
//	zookeeper_close(m_zh);
	return EXIT_SUCCESS;
}				// ----------  end of function main  ----------

