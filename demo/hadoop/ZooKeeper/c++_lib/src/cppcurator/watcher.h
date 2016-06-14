/*
// =====================================================================================
// 
//       Filename:  watcher.h
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

#ifndef  PS_SE_EDEN_COMMON_WATCHER_H
#define  PS_SE_EDEN_COMMON_WATCHER_H

#include <zookeeper.h>

namespace cppcurator {

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
        int value() const {
            return _event;
        }

        const char* desc() const {
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
        Event& operator=(const Event &e) = default;

        bool operator==(const Event &e) const {
            return _event == e.value();
        }

        bool operator==(int value) const {
            return _event == value;
        }

        bool operator!=(const Event &e) const {
            return !this->operator==(e);
        }

        bool operator!=(int value) const {
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
        int value() const {
            return _state;
        }

        const char* desc() const {
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
        State& operator=(const State &s) = default;

        bool operator==(const State &s) const {
            return _state == s.value();
        }

        bool operator==(int value) const {
            return _state == value;
        }

        bool operator!=(const State &s) const {
            return !this->operator==(s);
        }

        bool operator!=(int value) const {
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

}    // ----- #namespace cppcurator  -----

#endif    // ----- #ifndef PS_SE_EDEN_COMMON_WATCHER_H  -----
