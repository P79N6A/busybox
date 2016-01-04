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

/* 
// ===  FUNCTION  ======================================================================
//         Name:  main
//  Description:  
// =====================================================================================
*/
int main(int argc, char *argv[])
{
	// unique_ptr可以看作是单例shared_ptr
	std::unique_ptr<int> p1(new int(1));
	std::unique_ptr<int> p2 = std::move(p1);
	// std::unique_ptr<int> p3 = p1	// error，只能move，不能copy

	return EXIT_SUCCESS;
}				// ----------  end of function main  ----------
