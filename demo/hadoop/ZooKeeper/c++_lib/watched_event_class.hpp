/*
// =====================================================================================
// 
//       Filename:  watched_event_class.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/06/2016 04:06:02 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Elwin.Gao (elwin), elwin.gao4444@gmail.com
//        Company:  
// 
// =====================================================================================
*/

#ifndef  _WATCHED_EVENT_CLASS_HPP_
#define  _WATCHED_EVENT_CLASS_HPP_

#include <string>

using std::string;

namespace zkclass
{

	// =====================================================================================
	//        Class:  WatchedEvent
	//  Description:  
	// =====================================================================================
	class WatchedEvent
	{
		class EventType
		{
		};

		class KeeperState
		{
		};
	public:
		// ====================  LIFECYCLE     =======================================
		WatchedEvent();
		~WatchedEvent();

		// ====================  INTERFACE     =======================================

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_path
		//  Description:   
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		string get_path();

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_type
		//  Description:   
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		WatchedEvent::EventType get_type();

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_state
		//  Description:   
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		WatchedEvent::KeeperState get_state();

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_wrapper
		//  Description:   
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		void get_wrapper();

	private:
		// ==================== PRIVATE METHOD =======================================

		// ====================  DATA MEMBERS  =======================================
		string path;
		WatchedEvent::EventType type;
		WatchedEvent::KeeperState state;

	};		// -----  end of class WatchedEvent  -----

}	// ----- #namespace zkclass  -----

#endif	// ----- #ifndef _WATCHED_EVENT_CLASS_HPP_  -----

