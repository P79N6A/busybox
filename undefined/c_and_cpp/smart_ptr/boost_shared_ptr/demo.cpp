/*
// =====================================================================================
// 
//       Filename:  demo.cpp
// 
//    Description:  ����boost(tr1)��shared_ptr���÷�
//    �ο���http://euyuil.com/2344/note-about-shared-ptr-in-cpp1x/
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
	/* ���ڲο��ĵ���˵�������������Ͳ���׸�� */
	std::tr1::shared_ptr<int> sp(new int(0));
	std::cout << "Hello World" << std::endl;
	return EXIT_SUCCESS;
}				// ----------  end of function main  ----------
