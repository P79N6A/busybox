/*
// =====================================================================================
// 
//       Filename:  watcher_class.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/03/2016 08:11:55 PM
//       Revision:  All Rights Reserved
//       Compiler:  g++
// 
//         Author:  gaowei08@baidu.com
//        Company:  Baidu.com, Inc.
// 
// =====================================================================================
*/

#ifndef  _WATCHER_CLASS_HPP_
#define  _WATCHER_CLASS_HPP_

namespace zkclass {

class WatchedEvent;

// =====================================================================================
//        Class:  Watcher
//  Description:  
// =====================================================================================
class Watcher {
public:
    // ====================  INNER CLASS   =======================================

    // =====================================================================================
    //        Class:  Event
    //  Description:  
    // =====================================================================================
    class Event {
    public:
        // ====================  LIFECYCLE     =======================================
        explicit Event(int event) : _event(event) {}

        ~Event() {}

        // ====================  INTERFACE     =======================================
        int value() {
            return _event;
        }

        const char* desc() {
            if (_event == ZOO_CREATED_EVENT) {
                return "zookeeper created event";
            }
            if (_event == ZOO_DELETED_EVENT) {
                return "zookeeper deleted event";
            }
            if (_event == ZOO_CHANGED_EVENT) {
                return "zookeeper changed event";
            }
            if (_event == ZOO_CHILD_EVENT) {
                return "zookeeper child event";
            }
            if (_event == ZOO_SESSION_EVENT) {
                return "zookeeper session event";
            }
            if (_event == ZOO_NOTWATCHING_EVENT) {
                return "zookeeper not watching event";
            }
            return "zookeeper unknown event";
        }

        // ====================  OPERATORS     =======================================
        Event& operator=(int value) {
            _event = value;
            return *this;
        }

        bool operator==(int value) {
            return _event == value;
        }

        bool operator!=(int value) {
            return !this->operator==(value);
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
    class State {
    public:
        // ====================  LIFECYCLE     =======================================
        explicit State(int state) : _state(state) {}

        ~State() {}

        // ====================  INTERFACE     =======================================
        int value() {
            return _state;
        }

        const char* desc() {
            if (_state == ZOO_EXPIRED_SESSION_STATE) {
                return "zookeeper expired session state";
            }
            if (_state == ZOO_AUTH_FAILED_STATE) {
                return "zookeeper auth failed state";
            }
            if (_state == ZOO_CONNECTING_STATE) {
                return "zookeeper connecting state";
            }
            if (_state == ZOO_ASSOCIATING_STATE) {
                return "zookeeper associating state";
            }
            if (_state == ZOO_CONNECTED_STATE) {
                return "zookeeper connected state";
            }
            return "zookeeper unknown state";
        }

        // ====================  OPERATORS     =======================================
        State& operator=(int value) {
            _state = value;
            return *this;
        }

        bool operator==(int value) {
            return _state == value;
        }

        bool operator!=(int value) {
            return !this->operator==(value);
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
