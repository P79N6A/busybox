/*
// =====================================================================================
// 
//       Filename:  zookeeper.h
// 
//    Description:  zookeeper的对象化封装，模拟Java接口
//                  接口设计参照：https://zookeeper.apache.org/doc/r3.4.8/api/index.html
// 
//        Version:  1.0
//        Created:  06/03/2016 08:02:15 PM
//       Revision:  All Rights Reserved
//       Compiler:  g++
// 
//         Author:  gaowei08@baidu.com
//        Company:  Baidu.com, Inc.
// 
// =====================================================================================
*/

#ifndef  PS_SE_EDEN_COMMON_ZOOKEEPER_H
#define  PS_SE_EDEN_COMMON_ZOOKEEPER_H

#include <cstring>

#include <string>
#include <vector>
#include <memory>

#include "zookeeper.h"

#include "cppcurator/watcher.h"
#include "cppcurator/watched_event.h"
#include "cppcurator/zkacl.h"

namespace cppcurator {

// =====================================================================================
//        Class:  ZooKeeper
//  Description:  
// =====================================================================================
class ZooKeeper {
public:
    // ====================  INNER CLASS   =======================================

    // =====================================================================================
    //        Class:  Error
    //  Description:  
    // =====================================================================================
    class Error {
    public:
        // ====================  LIFECYCLE     =======================================
        Error() : _error(ZOK) {}

        explicit Error(int error) : _error(error) {}

        ~Error() {}

        // ====================  OPERATORS     =======================================
        Error& operator=(int value) {
            _error = value;
            return *this;
        }

        Error& operator=(const Error &e) {
            _error = e.value();
            return *this;
        }

        bool operator==(int value) const {
            return _error == value;
        }

        bool operator==(const Error &e) const {
            return _error == e.value();
        }

        bool operator!=(int value) const {
            return !this->operator==(value);
        }

        bool operator!=(const Error &e) const {
            return !this->operator==(e);
        }

        // ====================  INTERFACE     =======================================
        int value() const {
            return _error;
        }

        const char* desc() const {
            return zerror(_error);
        }

    private:
        // ==================== PRIVATE METHOD =======================================

        // ====================  DATA MEMBERS  =======================================
        int _error;

    };        // -----  end of class Error  -----

    using State = Watcher::State;

    // ====================  LIFECYCLE     =======================================

    ZooKeeper(const ZooKeeper &obj) = delete;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  ZooKeeper
    //  Description:  构造函数，负责创建ZooKeeper的连接，并建立Session
    //   Parameters:  connect_string: 连接字符串必须符合“host:port”格式
    //
    //                session_timeout: 超时时间。ZooKeeper的超时时间并不是设置多少就是多少，
    //                而是client和server协商的结果，这里的session_timeout只是client的建议值，
    //                而不是最终的使用值，最终使用值需要在ZooKeeper在建立Session完毕之后，由
    //
    //                get_session_timeout()接口查询获取
    //
    //                Watcher: 这里应该是Watcher接口的实现类的指针，用于注册ZooKeeper的监视器
    //
    //  ReturnValue:  void 执行结果无返回值，连接状态可通过get_state()接口查询
    // =====================================================================================
    */
    ZooKeeper(const std::string &connect_string, int session_timeout, Watcher *watcher);

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  ZooKeeper
    //  Description:  构造函数，负责创建ZooKeeper的连接，并建立Session
    //   Parameters:  connect_string: 连接字符串必须符合“host:port”格式
    //
    //                session_timeout: 超时时间。ZooKeeper的超时时间并不是设置多少就是多少，
    //                而是client和server协商的结果，这里的session_timeout只是client的建议值，
    //                而不是最终的使用值，最终使用值需要在ZooKeeper在建立Session完毕之后，由
    //                get_session_timeout()接口查询获取
    //
    //                Watcher: 这里应该是Watcher接口的实现类的指针，用于注册ZooKeeper的监视器
    //
    //                clientid: 使用指定的clientid进行重连，重连之前建议使用recoverable()接口
    //                来查询session是否有恢复的可能
    //
    //  ReturnValue:  void 执行结果无返回值，连接状态可通过get_state()接口查询
    // =====================================================================================
    */
    ZooKeeper(const std::string &connect_string, int session_timeout, Watcher *watcher,
            clientid_t *clientid);

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  ~ZooKeeper
    //  Description:  析够函数，释放资源
    // =====================================================================================
    */
    ~ZooKeeper();

    // ====================  INTERFACE     =======================================

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  close
    //  Description:  关闭ZooKeeper连接
    // =====================================================================================
    */
    ZooKeeper::Error close();

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  create
    //  Description:  创建一个指定节点
    //   Parameters:  path: 节点路径（无法递归创建新节点）
    //                data: 节点内容
    //                acl: 节点权限
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error create(const std::string &path, const std::string &data,
            const std::vector<ZKACL> &acl);

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  create
    //  Description:  创建一个指定节点
    //   Parameters:  path: 节点路径（无法递归创建新节点）
    //                data: 节点内容
    //                acl: 节点权限
    //                create_flag: 节点类型（ZOO_EPHEMERAL / ZOO_SEQUENCE）
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error create(const std::string &path, const std::string &data,
            const std::vector<ZKACL> &acl, int create_flag);

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  create
    //   Parameters:  path: 节点路径（无法递归创建新节点）
    //                data: 节点内容
    //                acl: 节点权限
    //                create_flag: 节点类型（ZOO_EPHEMERAL / ZOO_SEQUENCE）
    //                new_path: 实际创建节点的名字，一般用于带有ZOO_SEQUENCE标记的创建过程
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error create(const std::string &path, const std::string &data,
            const std::vector<ZKACL> &acl, int create_flag, std::string *new_path);

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  remove
    //  Description:  删除节点
    //   Parameters:  path: 节点路径（无法递归删除指定节点）
    //                version: 节点版本（-1为强制删除，无视版本）
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error remove(const std::string &path, int version);

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  exists
    //  Description:  检查指定节点是否存在
    //   Parameters:  path: 节点路径
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error exists(const std::string &path) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  exists
    //  Description:  检查指定节点是否存在
    //   Parameters:  path: 节点路径
    //                stat: 出参：返回节点状态（如果存在的话）
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error exists(const std::string &path, Stat *stat) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  exists
    //  Description:  检查指定节点是否存在
    //   Parameters:  path: 节点路径
    //                watch: 设置是否注册到默认Watcher监控
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error exists(const std::string &path, bool watch) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  exists
    //  Description:  检查指定节点是否存在
    //   Parameters:  path: 节点路径
    //                watch: 设置是否注册到默认Watcher监控
    //                stat: 出参：返回节点状态（如果存在的话）
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error exists(const std::string &path, bool watch, Stat *stat) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  exists
    //  Description:  检查指定节点是否存在
    //   Parameters:  path: 节点路径
    //                watcher: 注册一个自定义的Watcher监控对象
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error exists(const std::string &path, Watcher *watcher) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  exists
    //  Description:  检查指定节点是否存在
    //   Parameters:  path: 节点路径
    //                watcher: 注册一个自定义的Watcher监控对象
    //                stat: 出参：返回节点状态（如果存在的话）
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error exists(const std::string &path, Watcher *watcher, Stat *stat) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  set_data
    //  Description:  设置节点数据
    //   Parameters:  path: 节点路径
    //                data: 节点数据
    //                version: 节点版本号（-1为无视节点版本，强行修改）
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error set_data(const std::string &path, const std::string &data, int version);

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  set_data
    //  Description:  设置节点数据
    //   Parameters:  path: 节点路径
    //                data: 节点数据
    //                version: 节点版本号（-1为无视节点版本，强行修改）
    //                stat: 出参：返回节点状态（如果存在的话）
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error set_data(const std::string &path, const std::string &data, int version,
            Stat *stat);

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_data
    //  Description:  获取节点数据
    //   Parameters:  path: 节点路径
    //                data: 出参：节点数据
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error get_data(const std::string &path, std::string *data) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_data
    //  Description:  获取节点数据
    //   Parameters:  path: 节点路径
    //                data: 出参：节点数据
    //                stat: 出参：返回节点状态（如果存在的话）
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error get_data(const std::string &path, std::string *data, Stat *stat) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_data
    //  Description:  获取节点数据
    //   Parameters:  path: 节点路径
    //                data: 出参：节点数据
    //                watch: 设置是否注册到默认Watcher监控
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error get_data(const std::string &path, std::string *data, bool watch) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_data
    //  Description:  获取节点数据
    //   Parameters:  path: 节点路径
    //                data: 出参：节点数据
    //                watch: 设置是否注册到默认Watcher监控
    //                stat: 出参：返回节点状态（如果存在的话）
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error get_data(const std::string &path, std::string *data,
            bool watch, Stat *stat) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_data
    //  Description:  获取节点数据
    //   Parameters:  path: 节点路径
    //                data: 出参：节点数据
    //                watcher: 注册一个自定义的Watcher监控对象
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error get_data(const std::string &path, std::string *data,
            Watcher *watcher) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_data
    //  Description:  获取节点数据
    //   Parameters:  path: 节点路径
    //                data: 出参：节点数据
    //                watcher: 注册一个自定义的Watcher监控对象
    //                stat: 出参：返回节点状态（如果存在的话）
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error get_data(const std::string &path, std::string *data,
            Watcher *watcher, Stat *stat) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_children
    //  Description:  获取指定节点的子节点列表
    //   Parameters:  path: 节点路径
    //                children: 子节点列表
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error get_children(const std::string path, std::vector<std::string> *children) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_children
    //  Description:  获取指定节点的子节点列表
    //   Parameters:  path: 节点路径
    //                children: 子节点列表
    //                stat: 出参：返回节点状态（如果存在的话）
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error get_children(const std::string path, std::vector<std::string> *children,
            Stat *stat) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_children
    //  Description:  获取指定节点的子节点列表
    //   Parameters:  path: 节点路径
    //                children: 子节点列表
    //                watch: 设置是否注册到默认Watcher监控
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error get_children(const std::string path, std::vector<std::string> *children,
            bool watch) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_children
    //  Description:  获取指定节点的子节点列表
    //   Parameters:  path: 节点路径
    //                children: 子节点列表
    //                watcher: 注册一个自定义的Watcher监控对象
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error get_children(const std::string path, std::vector<std::string> *children,
            Watcher *watcher) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_children
    //  Description:  获取指定节点的子节点列表
    //   Parameters:  path: 节点路径
    //                children: 子节点列表
    //                watch: 设置是否注册到默认Watcher监控
    //                stat: 出参：返回节点状态（如果存在的话）
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error get_children(const std::string path, std::vector<std::string> *children,
            bool watch, Stat *stat) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_children
    //  Description:  获取指定节点的子节点列表
    //   Parameters:  path: 节点路径
    //                children: 子节点列表
    //                watcher: 注册一个自定义的Watcher监控对象
    //                stat: 出参：返回节点状态（如果存在的话）
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error get_children(const std::string path, std::vector<std::string> *children,
            Watcher *watcher, Stat *stat) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  add_auth_info
    //  Description:  为当前连接增加权限
    //   Parameters:  scheme: 权限模式
    //                cert: 具体权限
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error add_auth_info(const std::string &scheme, const std::string &cert);

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  set_acl
    //  Description:  设置节点的ACL权限
    //   Parameters:  path: 节点路径
    //                acl: 节点的ACL权限列表
    //                version: 节点版本（-1为强行设置，无视版本）
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error set_acl(const std::string path, std::vector<ZKACL> acl, int version);

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_acl
    //  Description:  获取节点ACL权限
    //   Parameters:  path: 节点路径
    //                acl: 出参：节点的ACL权限列表
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error get_acl(const std::string path, std::vector<ZKACL> *acl) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_acl
    //  Description:  获取节点ACL权限
    //   Parameters:  path: 节点路径
    //                acl: 出参：节点的ACL权限列表
    //                stat: 出参：返回节点状态（如果存在的话）
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error get_acl(const std::string path, std::vector<ZKACL> *acl, Stat *stat) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  register_watcher
    //  Description:  注册（替换）默认监视器
    //   Parameters:  watcher: 这里应该是Watcher接口的实现类的指针，用于注册ZooKeeper的监视器
    //  ReturnValue:  void
    // =====================================================================================
    */
    void register_watcher(Watcher *watcher);

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_client_id
    //  Description:  获取当前会话的clientid
    //   Parameters:  
    //  ReturnValue:  当前会话的clientid的指针
    // =====================================================================================
    */
    const clientid_t* get_client_id() const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_session_timeout
    //  Description:  获取当前会话的timeout
    //   Parameters:  
    //  ReturnValue:  timeout
    // =====================================================================================
    */
    int get_session_timeout() const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_state
    //  Description:  获取当前ZooKeeper的连接状态
    //   Parameters:  
    //  ReturnValue:  State class
    // =====================================================================================
    */
    ZooKeeper::State get_state() const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  recoverable
    //  Description:  检查当前zookeeper连接是否是可恢复的
    //   Parameters:  
    //  ReturnValue:  true or false
    // =====================================================================================
    */
    bool recoverable() const;

private:
    // ==================== PRIVATE METHOD =======================================

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  init
    //  Description:   
    //   Parameters:  
    //  ReturnValue:  
    // =====================================================================================
    */
    void init(const std::string &connect_string, int session_timeout, Watcher *watcher, clientid_t *clientid);

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  vector_to_array
    //  Description:   
    //   Parameters:  
    //  ReturnValue:  
    // =====================================================================================
    */
    inline std::unique_ptr<ACL[]> vector_to_array(std::vector<ZKACL> vec) {
        std::unique_ptr<ACL[]> array(new ACL[vec.size()]);
        for (size_t i = 0; i < vec.size(); ++i) {
            array[i].perms = vec[i].perms();
            array[i].id.scheme = (char*)vec[i].scheme().c_str();
            array[i].id.id = (char*)vec[i].id().c_str();
        }
        return array;
    }        // -----  end of template function vector_to_array  -----

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  watcher_callback
    //  Description:   
    //   Parameters:  
    //  ReturnValue:  
    // =====================================================================================
    */
    static void watcher_callback(zhandle_t *zh, int type,
            int state, const char *path,void *watcherCtx);

    // ====================  DATA MEMBERS  =======================================
    zhandle_t *_zhandler;

};        // -----  end of class ZooKeeper  -----

}    // ----- #namespace cppcurator  -----

#endif    // ----- #ifndef PS_SE_EDEN_COMMON_ZOOKEEPER_H  -----
