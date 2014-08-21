/*
// =====================================================================================
// 
//       Filename:  demo.cpp
// 
//    Description:  介绍boost(tr1)中shared_ptr的用法
//    参考：http://euyuil.com/2344/note-about-shared-ptr-in-cpp1x/
// 
//        Version:  1.0
//        Created:  10/10/2012 07:57:33 PM
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
#include <tr1/memory>

/* 
// ===  FUNCTION  ======================================================================
//         Name:  main
//  Description:  demo
// =====================================================================================
*/
int main(int argc, char *argv[])
{
	/* 由于参考文档的说明很清楚，这里就不再赘述 */
	std::tr1::shared_ptr<int> sp(new int(0));
	std::cout << "Hello World" << std::endl;
	return EXIT_SUCCESS;
}				// ----------  end of function main  ----------
