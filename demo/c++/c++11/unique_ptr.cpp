/*
// =====================================================================================
// 
//       Filename:  unique_ptr.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  01/04/2016 08:04:26 PM
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
#include <memory>

std::unique_ptr<int> fun()
{
	return std::unique_ptr<int>(new int(2));
}

/* 
// ===  FUNCTION  ======================================================================
//         Name:  main
//  Description:  
// =====================================================================================
*/
int main(int argc, char *argv[])
{
	// unique_ptr可以看作是单例shared_ptr
	// c++11中并没有类似make_shared<T>()函数类似的make_unique<T>()函数
	// make_unique<T>()函数在c++14中正式加入到std中
	std::unique_ptr<int> p1(new int(1));
	std::unique_ptr<int> p2 = std::move(p1);
	// std::unique_ptr<int> p3 = p1	// error，只能move，不能copy

	// unique_ptr另一个非常实用的用法，就是获取函数的内部返回值
	// 指针在函数内new，传递到函数外，不会造成内存泄漏
	std::unique_ptr<int> p3 = fun();
	std::cout << *p3 << std::endl;

	return EXIT_SUCCESS;
}				// ----------  end of function main  ----------

