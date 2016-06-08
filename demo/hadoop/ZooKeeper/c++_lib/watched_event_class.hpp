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

#include "watcher_class.hpp"

namespace zkclass
{

	// =====================================================================================
	//        Class:  WatchedEvent
	//  Description:  
	// =====================================================================================
	class WatchedEvent
	{
	public:
		// ====================  LIFECYCLE     =======================================
		WatchedEvent(const std::string &path, int type, int state)
			: m_path(path), m_type(type), m_state(state)
		{
		}

		~WatchedEvent()
		{
		}

		// ====================  INTERFACE     =======================================

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_path
		//  Description:   
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		inline const std::string& path() const
		{
			return m_path;
		}		// -----  end of function path  -----

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_type
		//  Description:   
		// =====================================================================================
		*/
		inline Watcher::Event type() const
		{
			return Watcher::Event(m_type);
		}		// -----  end of function type  -----

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_state
		//  Description:   
		// =====================================================================================
		*/
		inline Watcher::State state() const
		{
			return Watcher::State(m_state);
		}		// -----  end of function state  -----

	private:
		// ==================== PRIVATE METHOD =======================================

		// ====================  DATA MEMBERS  =======================================
		std::string m_path;
		int m_type;
		int m_state;

	};		// -----  end of class WatchedEvent  -----

}	// ----- #namespace zkclass  -----

#endif	// ----- #ifndef _WATCHED_EVENT_CLASS_HPP_  -----

