/*
// =====================================================================================
// 
//       Filename:  watched_event.h
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

#ifndef  PS_SE_EDEN_COMMON_WATCHED_EVENT_H
#define  PS_SE_EDEN_COMMON_WATCHED_EVENT_H

#include <string>

#include "cppcurator/watcher.h"

namespace cppcurator {

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

}    // ----- #namespace cppcurator  -----

#endif    // ----- #ifndef PS_SE_EDEN_COMMON_WATCHED_EVENT_H  -----

