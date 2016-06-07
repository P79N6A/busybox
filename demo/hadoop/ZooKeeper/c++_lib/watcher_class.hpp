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

namespace zkclass
{
	class WatchedEvent;
	// =====================================================================================
	//        Class:  Watcher
	//  Description:  
	// =====================================================================================
	class Watcher
	{
	public:
		// ====================  INNER CLASS   =======================================

		// =====================================================================================
		//        Class:  Event
		//  Description:  
		// =====================================================================================
		class Event
		{
		public:
			// ====================  LIFECYCLE     =======================================
			Event(int event) : m_event(event)
			{
			}

			~Event()
			{
			}

			// ====================  INTERFACE     =======================================
			int value()
			{
				return m_event;
			}

			const char* c_str()
			{
				if (m_event == ZOO_CREATED_EVENT)
					return "ZOO_CREATED_EVENT";
				if (m_event == ZOO_DELETED_EVENT)
					return "ZOO_DELETED_EVENT";
				if (m_event == ZOO_CHANGED_EVENT)
					return "ZOO_CHANGED_EVENT";
				if (m_event == ZOO_CHILD_EVENT)
					return "ZOO_CHILD_EVENT";
				if (m_event == ZOO_SESSION_EVENT)
					return "ZOO_SESSION_EVENT";
				if (m_event == ZOO_NOTWATCHING_EVENT)
					return "ZOO_NOTWATCHING_EVENT";
			}

		private:
			// ==================== PRIVATE METHOD =======================================

			// ====================  DATA MEMBERS  =======================================
			int m_event;

		};		// -----  end of class Event  -----

		// =====================================================================================
		//        Class:  State
		//  Description:  
		// =====================================================================================
		class State
		{
		public:
			// ====================  LIFECYCLE     =======================================
			State(int state)
			{
				m_state = state;
			}

			~State()
			{
			}

			// ====================  INTERFACE     =======================================
			int value()
			{
				return m_state;
			}

			const char* c_str()
			{
				if (m_state == ZOO_EXPIRED_SESSION_STATE)
					return "ZOO_EXPIRED_SESSION_STATE";
				if (m_state == ZOO_AUTH_FAILED_STATE)
					return "ZOO_AUTH_FAILED_STATE";
				if (m_state == ZOO_CONNECTING_STATE)
					return "ZOO_CONNECTING_STATE";
				if (m_state == ZOO_ASSOCIATING_STATE)
					return "ZOO_ASSOCIATING_STATE";
				if (m_state == ZOO_CONNECTED_STATE)
					return "ZOO_CONNECTED_STATE";

				return "ZOO_UNKNOWN_STATE";
			}

		private:
			// ==================== PRIVATE METHOD =======================================

			// ====================  DATA MEMBERS  =======================================
			int m_state;

		};		// -----  end of class State  -----

		// ====================  INTERFACE     =======================================

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  process
		//  Description:   
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		virtual void process(const WatchedEvent &event) = 0;

	};		// -----  end of class Watcher  -----

}	// ----- #namespace zkclass  -----

#endif	// ----- #ifndef _WATCHER_CLASS_HPP_  -----
