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

#include <cstdlib>
#include <cassert>
#include <iostream>

#include "zookeeper_class.hpp"
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
		std::cout << "event.type:" << event.type() << std::endl;
		std::cout << "event.state:" << event.state() << std::endl;
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
	// case1：无watcher，无权限
	ZooKeeper zk1(server, 10, nullptr);
	assert(zk1.ok());
	std::cout << "case1: connect to zookeeper server success!" << std::endl;
	assert(zk1.close() == ZOK);
	std::cout << "case1: close zookeeper connection success!" << std::endl;

	// case2：有watcher无权限
	mywatcher watcher;
	ZooKeeper zk2(server, 10, &watcher);
	assert(zk2.ok());
	std::cout << "case2: connect to zookeeper server success!" << std::endl;
	assert(zk2.close() == ZOK);
	std::cout << "case2: close zookeeper connection success!" << std::endl;

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
	return EXIT_SUCCESS;
}				// ----------  end of function main  ----------

