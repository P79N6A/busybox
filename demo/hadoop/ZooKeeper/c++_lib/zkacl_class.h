/*
// =====================================================================================
// 
//       Filename:  zkacl_class.h
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/13/2016 05:04:53 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  gaowei08@baidu.com
//        Company:  Baidu.com, Inc.
// 
// =====================================================================================
*/

#ifndef  PS_SE_EDEN_COMMON_ZKACL_CLASS_H
#define  PS_SE_EDEN_COMMON_ZKACL_CLASS_H

namespace zkclass {

// =====================================================================================
//        Class:  ZKACL
//  Description:  
// =====================================================================================
class ZKACL {
public:
    // ====================  LIFECYCLE     =======================================
    ZKACL(const ZKACL &acl) = default;
    ZKACL(ZKACL &&acl) = default;

    ZKACL(const ACL &acl) {
        _perms = acl.perms;
        _scheme = acl.id.scheme;
        _id = acl.id.id;
    }

    ZKACL(int32_t perms, const std::string &scheme, const std::string &id) {
        _perms = perms;
        _scheme = scheme;
        _id = id;
    }

    ~ZKACL() {}

    // ====================  INTERFACE     =======================================

    int32_t perms() const {
        return _perms;
    }        // -----  end of function perms  -----
    
    std::string scheme() const {
        return _scheme;
    }        // -----  end of function scheme  -----

    std::string id() const {
        return _id;
    }        // -----  end of function id  -----

    // ====================  OPERATORS     =======================================
    ZKACL& operator=(ZKACL &acl) {
        _perms = acl.perms();
        _scheme = acl.scheme();
        _id = acl.id();
        return *this;
    }

private:
    // ==================== PRIVATE METHOD =======================================

    // ====================  DATA MEMBERS  =======================================
    int32_t _perms;
    std::string _scheme;
    std::string _id;

};        // -----  end of class ZKACL  -----

}    // ----- #namespace zkclass  -----

#endif    // ----- #ifndef PS_SE_EDEN_COMMON_ZKACL_CLASS_H  -----

