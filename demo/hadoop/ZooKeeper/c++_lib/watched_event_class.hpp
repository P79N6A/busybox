/*
// =====================================================================================
// 
//       Filename:  watched_event_class.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/06/2016 04:06:02 PM
//       Revision:  All Rights Reserved
//       Compiler:  g++
// 
//         Author:  gaowei08@baidu.com
//        Company:  Baidu.com, Inc.
// 
// =====================================================================================
*/

#ifndef  _WATCHED_EVENT_CLASS_HPP_
#define  _WATCHED_EVENT_CLASS_HPP_

#include <string>

#include "watcher_class.hpp"

namespace zkclass {

// =====================================================================================
//        Class:  WatchedEvent
//  Description:  
// =====================================================================================
class WatchedEvent {
public:
    // ====================  LIFECYCLE     =======================================
    WatchedEvent(const std::string &path, int type, int state)
        : _path(path), _type(type), _state(state) {}

    ~WatchedEvent() {}

    // ====================  INTERFACE     =======================================

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_path
    //  Description:  获取当前监控被触发时的path信息
    // =====================================================================================
    */
    inline const std::string& path() const {
        return _path;
    }        // -----  end of function path  -----

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_type
    //  Description:  获取当前监控被触发时的type信息
    // =====================================================================================
    */
    inline Watcher::Event type() const {
        return Watcher::Event(_type);
    }        // -----  end of function type  -----

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_state
    //  Description:  获取当前监控被触发时的state信息
    // =====================================================================================
    */
    inline Watcher::State state() const {
        return Watcher::State(_state);
    }        // -----  end of function state  -----

private:
    // ==================== PRIVATE METHOD =======================================

    // ====================  DATA MEMBERS  =======================================
    std::string _path;
    int _type;
    int _state;

};        // -----  end of class WatchedEvent  -----

}    // ----- #namespace zkclass  -----

#endif    // ----- #ifndef _WATCHED_EVENT_CLASS_HPP_  -----

