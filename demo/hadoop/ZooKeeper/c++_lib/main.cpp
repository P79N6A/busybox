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
#include <iostream>

#include "zookeeper_class.hpp"
#include "watched_event_class.hpp"
using zkclass::ZooKeeper;
using zkclass::Watcher;
using zkclass::WatchedEvent;

const std::string server = "localhost:2181";

class mywatcher : public Watcher
{
	void process(const WatchedEvent &event)
	{
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
void test_connect_and_close()
{
	// case1：无watcher，无old session
	ZooKeeper zk1(server, 1024, nullptr);
	std::cout << "case1: connect to zookeeper server success!" << std::endl;
	usleep(20*1000);	// 由于这里没有watcher监控状态，所以只能坐等session建立完成
	assert(zk1.get_state().no() == ZOO_CONNECTED_STATE);
	clientid_t id1 = *zk1.get_client_id();
	std::cout << "case1: session id:[" << id1.client_id << "]" << "\t";
	std::cout << "case1: session passwd:[" << id1.passwd << "]" << "\t";
	std::cout << "case1: session timeout:[" << zk1.get_session_timeout() << "]" << std::endl;
//	assert(zk1.close().no() == ZOK);
//	std::cout << "case1: close zookeeper connection success!" << std::endl;

	// case2：无watcher，有old session
	ZooKeeper zk2(server, 1024, nullptr, &id1);
	assert(zk1.get_state().no() == ZOO_CONNECTED_STATE);
	std::cout << "case2: connect to zookeeper server success!" << std::endl;
	clientid_t id2 = *zk2.get_client_id();	// 由于此时session已经建立完成，所以无需等待
	std::cout << "case2: session id:[" << id2.client_id << "]" << "\t";
	std::cout << "case2: session passwd:[" << id2.passwd << "]" << "\t";
	std::cout << "case2: session timeout:[" << zk2.get_session_timeout() << "]" << std::endl;
	assert(zk2.close().no() == ZOK);
	std::cout << "case2: close zookeeper connection success!" << std::endl;

	assert(zk1.get_state().no() == ZOO_CONNECTED_STATE);
	assert(zk2.get_state().no() != ZOO_CONNECTED_STATE);

	// case1：有watcher，无old session
	mywatcher watcher;
	ZooKeeper zk3(server, 1024, &watcher);
	std::cout << "case3: connect to zookeeper server success!" << std::endl;
	usleep(20*1000);
	clientid_t id3 = *zk3.get_client_id();
	std::cout << "case3: session id:[" << id3.client_id << "]" << "\t";
	std::cout << "case3: session passwd:[" << id3.passwd << "]" << "\t";
	std::cout << "case3: session timeout:[" << zk3.get_session_timeout() << "]" << std::endl;
	assert(zk3.close().no() == ZOK);
	std::cout << "case3: close zookeeper connection success!" << std::endl;

	std::cout << "\e[32mTest: test_connect_and_close() OK\e[0m" << std::endl;
}		// -----  end of function test_connect_and_close  -----

/* 
// ===  FUNCTION  ======================================================================
//         Name:  main
//  Description:  
// =====================================================================================
*/
int main(int argc, char *argv[])
{
	test_connect_and_close();
	std::cout << "\e[32mAll Test is OK\e[0m" << std::endl;
//	zhandle_t *m_zh = zookeeper_init("localhost:2181",
//			nullptr, 0, nullptr, nullptr, 0);
//	const clientid_t *client_id = zoo_client_id(m_zh);
//	int timeout = zoo_recv_timeout(m_zh);
//	zookeeper_close(m_zh);
	return EXIT_SUCCESS;
}				// ----------  end of function main  ----------

