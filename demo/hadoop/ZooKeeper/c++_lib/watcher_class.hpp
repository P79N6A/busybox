/*
// =====================================================================================
// 
//       Filename:  watcher_class.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/03/2016 08:11:55 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Elwin.Gao (elwin), elwin.gao4444@gmail.com
//        Company:  
// 
// =====================================================================================
*/

#ifndef  _WATCHER_CLASS_HPP_
#define  _WATCHER_CLASS_HPP_

#include "watched_event_class.hpp"

namespace zkclass
{

	// =====================================================================================
	//        Class:  Watcher
	//  Description:  
	// =====================================================================================
	class Watcher
	{
	public:
		// ====================  INTERFACE     =======================================

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  process
		//  Description:   
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		virtual void process(WatchedEvent event) = 0;

	};		// -----  end of class Watcher  -----

}	// ----- #namespace zkclass  -----

#endif	// ----- #ifndef _WATCHER_CLASS_HPP_  -----
