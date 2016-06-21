/*
// =====================================================================================
// 
//       Filename:  thread.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/21/2016 01:37:35 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Elwin.Gao (elwin), elwin.gao4444@gmail.com
//        Company:  
// 
// =====================================================================================
*/

#include <cstdlib>
#include <iostream>
#include <thread>
#include <chrono>

void fun0()
{
	std::cout << "fun() in new thread" << std::endl;
}

void fun1(int i)
{
	std::cout << "fun(int i) in new thread, i = " << i << std::endl;
}

void fun()
{
	// 这里的std::this_thread是一个namespace而不是一个对象，感觉怪怪的
	std::cout << "thread id: " << std::this_thread::get_id() << std::endl;
	std::cout << "core num: " << std::thread::hardware_concurrency() << std::endl;
	// 当前现成睡眠10毫秒
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

/* 
// ===  FUNCTION  ======================================================================
//         Name:  main
//  Description:  
// =====================================================================================
*/
int main(int argc, char *argv[])
{
	// thread的基本用法
	std::thread t0(fun0);
	t0.join();
	// thread还可以使用std::bind
	std::thread t1(std::bind(fun1, 1));
	t1.join();
	// thread还可以使用lambda表达式来注册线程函数
	std::thread t2([](int i, int j){std::cout << "lambda: i=" << i << ", j=" << j << std::endl;}, 2, 3);
	t2.join();

	// 获取thread相关信息
	std::thread t(fun);
	t.join();

	std::cout << "Hello World" << std::endl;
	return EXIT_SUCCESS;
}				// ----------  end of function main  ----------

