/*
// =====================================================================================
// 
//       Filename:  hack_string.h
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/15/2016 12:00:03 PM
//       Revision:  All Rights Reserved
//       Compiler:  g++
// 
//         Author:  gaowei08@baidu.com
//        Company:  Baidu.com, Inc.
// 
// =====================================================================================
*/

#ifndef  PS_SE_EDEN_COMMON_HACK_STRING_H
#define  PS_SE_EDEN_COMMON_HACK_STRING_H

#include <string>

namespace cppcurator {

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  resize_string_uninitialized
 *  Description:  
 *   Parameters:  
 *  ReturnValue:  
 * =====================================================================================
 */
static std::string* resize_string_uninitialized(std::string *str, size_t size) {
    struct Rep {
        std::string::size_type length;
        std::string::size_type capacity;
        _Atomic_word refcount;
    };
    str->reserve(std::max(size, str->capacity()));
    char *base = const_cast<char*>(str->data());
    reinterpret_cast<Rep*>(base)[-1].length = size;
    base[size] = '\0';

    return str;
}        // -----  end of method ZooKeeper::resize_string_uninitialized  -----

}    // ----- #namespace cppcurator  -----

#endif	/* ----- #ifndef PS_SE_EDEN_COMMON_HACK_STRING_H  ----- */
