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
#include <cassert>
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>

std::once_flag flag;

void fun0()
{
	std::call_once(flag, [](){ std::cout << "Simple example: called once\n"; });	// 共用一个flag的call_once函数全程只会调用一次

	std::cout << "fun() in new thread" << std::endl;
}

void fun1(int i)
{
	std::call_once(flag, [](){ std::cout << "Simple example: called once\n"; });	// 共用一个flag的call_once函数全程只会调用一次

	std::cout << "fun(int i) in new thread, i = " << i << std::endl;
}

void fun()
{
	std::call_once(flag, [](){ std::cout << "Simple example: called once\n"; });	// 共用一个flag的call_once函数全程只会调用一次

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

	// mutex用法
	// 另外还有metex的可递归版本： recursive_mutex
	std::mutex mtx;
	mtx.lock();
	assert(mtx.try_lock() == false);
	mtx.unlock();
	std::lock_guard<std::mutex> guard_mtx(mtx);	// 常见的用法是配合lock_guard一起使用
	// lock_guard还可以配合std::adopt_lock参数使用，用于承接已经lock的mutex
	// 这里的用法是有问题的mtx由于被两个guard_mtx所管理，虽然std::adopt_lock参数不会再次lock
	// 但是，会出现两次unlock的情况，官方文档中对于unlock两次的行为是未定义的
//	std::lock_guard<std::mutex> guard_mtx2(mtx, std::adopt_lock);

	// timed_mutex用法
	// 另外还有metex的可递归版本： recursive_timed_mutex
	std::timed_mutex tmtx;
	tmtx.lock();
	assert(tmtx.try_lock() == false);
	assert(tmtx.try_lock_for(std::chrono::milliseconds(10)) == false);
	assert(tmtx.try_lock_until(std::chrono::steady_clock::now() + std::chrono::milliseconds(10)) == false);
	tmtx.unlock();
	std::lock_guard<std::timed_mutex> guard_tmtx(tmtx);	// 常见的用法是配合lock_guard一起使用

	// lock_guard用法简单，性能良好，但有时会显得功能不足，此时std::unique_lock可以提供更多的功能
	// unique_lock可以使用4种不同的参数形式（lock_guard只有两种：默认和std::adopt_lock）：
	// 策略 		tag type 		描述
	// (默认) 		无 			请求锁，阻塞当前线程直到成功获得锁。
	// std::defer_lock 	std::defer_lock_t 	不请求锁。
	// std::try_to_lock 	std::try_to_lock_t 	尝试请求锁，但不阻塞线程，锁不可用时也会立即返回。
	// std::adopt_lock 	std::adopt_lock_t 	假定当前线程已经获得互斥对象的所有权，所以不再请求锁。
	// 
	// 另外，unique_lock的另一种非常重要的用法是作为返回值将锁传递出去，这一点是lock_guard做不到的
	std::mutex mtx_uniq;
	std::unique_lock<std::mutex> uniq_lock(mtx_uniq, std::defer_lock);	//这是一种只创建，不加锁的初始化方式

	// 当需要同时对多个mutex进行加锁的时候，传统的方法是将加锁顺序固定，以避免死锁，
	// 新的方式是使用std::lock(std::try_lock)进行一次事物性的连续加锁
	// 由于并没有std::unlock方法，所以解锁过程需要手动一个个的unlock，一般使用lock_guard和unique_lock来帮助进行自动解锁
	std::mutex mtx1, mtx2, mtx3;
	std::lock(mtx1, mtx2, mtx3);	// 先锁后guard的方式
	std::lock_guard<std::mutex> lock1(mtx1, std::adopt_lock);
	std::lock_guard<std::mutex> lock2(mtx2, std::adopt_lock);
	std::lock_guard<std::mutex> lock3(mtx3, std::adopt_lock);

	std::mutex mtx4, mtx5, mtx6;
	std::unique_lock<std::mutex> lock4(mtx4, std::defer_lock);
	std::unique_lock<std::mutex> lock5(mtx5, std::defer_lock);
	std::unique_lock<std::mutex> lock6(mtx6, std::defer_lock);
	std::lock(mtx4, mtx5, mtx6);	// 先guard后锁的方式

	// 原子变量
	// 原子变量的用法十分简单，但是接口众多，详细内容参考：
	// http://en.cppreference.com/w/cpp/atomic/atomic
	std::atomic<int> i(0);	// 原子变量的使用和普通int类型一样，基本没有差别
	std::atomic<int> j(1);
	i=1; ++i; --i; i+=2; i+=j;

	std::cout << "Hello World" << std::endl;
	return EXIT_SUCCESS;
}				// ----------  end of function main  ----------

