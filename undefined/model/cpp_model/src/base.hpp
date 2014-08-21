/*
// =====================================================================================
// 
//       Filename:  base.hpp
// 
//    Description:  基类声明
// 
//        Version:  1.0
//        Created:  01/16/2013 01:00:07 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Elwin.Gao (elwin), elwin.gao4444@gmail.com
//        Company:  
// 
// =====================================================================================
*/

#ifndef  BASE_HPP
#define  BASE_HPP

// =====================================================================================
//        Class:  Base
//  Description:  
// =====================================================================================
class Base
{
public:
	// ====================  LIFECYCLE     =======================================
	Base(){}		// constructor

	// ====================  INTERFACE     =======================================
	int base_fun_1();
	int base_fun_2();
	int base_fun_3();

private:
	// ====================  DATA MEMBERS  =======================================

};		// -----  end of class Base  -----

#endif  /*BASE_HPP*/
