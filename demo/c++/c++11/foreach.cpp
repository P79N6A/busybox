/*
// =====================================================================================
// 
//       Filename:  foreach.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  01/04/2016 04:15:02 PM
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
#include <string>

/* 
// ===  FUNCTION  ======================================================================
//         Name:  main
//  Description:  
// =====================================================================================
*/
int main(int argc, char *argv[])
{
	// c++ 支持的foreach循环，循环变量与迭代器用法中的迭代器变量*it等效
	std::string str = std::string("abc");
	for (const auto &c : str) {	// 即使没有定义const，使用foreach语法时，元素变量默认也是const的
		// 在循环过程中，对元素进行修改，将会导致迭代器失效，出现迭代异常
		std::cout << c << std::endl;
	}

	return EXIT_SUCCESS;
}				// ----------  end of function main  ----------
