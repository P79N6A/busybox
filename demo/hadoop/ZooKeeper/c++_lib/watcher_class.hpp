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
            Event(int event) : _event(event) {}

            ~Event() {}

            // ====================  INTERFACE     =======================================
            int value()
            {
                return _event;
            }

            const char* c_str()
            {
                if (_event == ZOO_CREATED_EVENT) {
                    return "ZOO_CREATED_EVENT";
                }
                if (_event == ZOO_DELETED_EVENT) {
                    return "ZOO_DELETED_EVENT";
                }
                if (_event == ZOO_CHANGED_EVENT) {
                    return "ZOO_CHANGED_EVENT";
                }
                if (_event == ZOO_CHILD_EVENT) {
                    return "ZOO_CHILD_EVENT";
                }
                if (_event == ZOO_SESSION_EVENT) {
                    return "ZOO_SESSION_EVENT";
                }
                if (_event == ZOO_NOTWATCHING_EVENT) {
                    return "ZOO_NOTWATCHING_EVENT";
                }
        return "ZOO_UNKNOWN_EVENT";
            }

            // ====================  OPERATORS     =======================================
            bool operator==(int value)
            {
                return _event == value;
            }

            bool operator!=(int value)
            {
                return _event != value;
            }

        private:
            // ==================== PRIVATE METHOD =======================================

            // ====================  DATA MEMBERS  =======================================
            int _event;

        };        // -----  end of class Event  -----

        // =====================================================================================
        //        Class:  State
        //  Description:  
        // =====================================================================================
        class State
        {
        public:
            // ====================  LIFECYCLE     =======================================
            State(int state) : _state(state) {}

            ~State() {}

            // ====================  INTERFACE     =======================================
            int value()
            {
                return _state;
            }

            const char* c_str()
            {
                if (_state == ZOO_EXPIRED_SESSION_STATE) {
                    return "ZOO_EXPIRED_SESSION_STATE";
                }
                if (_state == ZOO_AUTH_FAILED_STATE) {
                    return "ZOO_AUTH_FAILED_STATE";
                }
                if (_state == ZOO_CONNECTING_STATE) {
                    return "ZOO_CONNECTING_STATE";
                }
                if (_state == ZOO_ASSOCIATING_STATE) {
                    return "ZOO_ASSOCIATING_STATE";
                }
                if (_state == ZOO_CONNECTED_STATE) {
                    return "ZOO_CONNECTED_STATE";
                }
                return "ZOO_UNKNOWN_STATE";
            }

            // ====================  OPERATORS     =======================================
            bool operator==(int value)
            {
                return _state == value;
            }

            bool operator!=(int value)
            {
                return _state != value;
            }

        private:
            // ==================== PRIVATE METHOD =======================================

            // ====================  DATA MEMBERS  =======================================
            int _state;

        };        // -----  end of class State  -----

        // ====================  INTERFACE     =======================================

        /* 
        // ===  FUNCTION  ======================================================================
        //         Name:  process
        //  Description:  Watcher的回调接口
        //   Parameters:  event: WatchedEvent对象的引用，用于获取Watcher被触发时的相关参数
        //  ReturnValue:  
        // =====================================================================================
        */
        virtual void process(const WatchedEvent &event) = 0;

    };        // -----  end of class Watcher  -----

}    // ----- #namespace zkclass  -----

#endif    // ----- #ifndef _WATCHER_CLASS_HPP_  -----
