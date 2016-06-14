/*
// =====================================================================================
// 
//       Filename:  zookeeper.h
// 
//    Description:  zookeeper�Ķ��󻯷�װ��ģ��Java�ӿ�
//                  �ӿ���Ʋ��գ�https://zookeeper.apache.org/doc/r3.4.8/api/index.html
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
    //  Description:  ���캯�������𴴽�ZooKeeper�����ӣ�������Session
    //   Parameters:  connect_string: �����ַ���������ϡ�host:port����ʽ
    //
    //                session_timeout: ��ʱʱ�䡣ZooKeeper�ĳ�ʱʱ�䲢�������ö��پ��Ƕ��٣�
    //                ����client��serverЭ�̵Ľ���������session_timeoutֻ��client�Ľ���ֵ��
    //                ���������յ�ʹ��ֵ������ʹ��ֵ��Ҫ��ZooKeeper�ڽ���Session���֮����
    //
    //                get_session_timeout()�ӿڲ�ѯ��ȡ
    //
    //                Watcher: ����Ӧ����Watcher�ӿڵ�ʵ�����ָ�룬����ע��ZooKeeper�ļ�����
    //
    //  ReturnValue:  void ִ�н���޷���ֵ������״̬��ͨ��get_state()�ӿڲ�ѯ
    // =====================================================================================
    */
    ZooKeeper(const std::string &connect_string, int session_timeout, Watcher *watcher);

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  ZooKeeper
    //  Description:  ���캯�������𴴽�ZooKeeper�����ӣ�������Session
    //   Parameters:  connect_string: �����ַ���������ϡ�host:port����ʽ
    //
    //                session_timeout: ��ʱʱ�䡣ZooKeeper�ĳ�ʱʱ�䲢�������ö��پ��Ƕ��٣�
    //                ����client��serverЭ�̵Ľ���������session_timeoutֻ��client�Ľ���ֵ��
    //                ���������յ�ʹ��ֵ������ʹ��ֵ��Ҫ��ZooKeeper�ڽ���Session���֮����
    //                get_session_timeout()�ӿڲ�ѯ��ȡ
    //
    //                Watcher: ����Ӧ����Watcher�ӿڵ�ʵ�����ָ�룬����ע��ZooKeeper�ļ�����
    //
    //                clientid: ʹ��ָ����clientid��������������֮ǰ����ʹ��recoverable()�ӿ�
    //                ����ѯsession�Ƿ��лָ��Ŀ���
    //
    //  ReturnValue:  void ִ�н���޷���ֵ������״̬��ͨ��get_state()�ӿڲ�ѯ
    // =====================================================================================
    */
    ZooKeeper(const std::string &connect_string, int session_timeout, Watcher *watcher,
            clientid_t *clientid);

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  ~ZooKeeper
    //  Description:  �����������ͷ���Դ
    // =====================================================================================
    */
    ~ZooKeeper();

    // ====================  INTERFACE     =======================================

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  close
    //  Description:  �ر�ZooKeeper����
    // =====================================================================================
    */
    ZooKeeper::Error close();

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  create
    //  Description:  ����һ��ָ���ڵ�
    //   Parameters:  path: �ڵ�·�����޷��ݹ鴴���½ڵ㣩
    //                data: �ڵ�����
    //                acl: �ڵ�Ȩ��
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error create(const std::string &path, const std::string &data,
            const std::vector<ZKACL> &acl);

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  create
    //  Description:  ����һ��ָ���ڵ�
    //   Parameters:  path: �ڵ�·�����޷��ݹ鴴���½ڵ㣩
    //                data: �ڵ�����
    //                acl: �ڵ�Ȩ��
    //                create_flag: �ڵ����ͣ�ZOO_EPHEMERAL / ZOO_SEQUENCE��
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error create(const std::string &path, const std::string &data,
            const std::vector<ZKACL> &acl, int create_flag);

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  create
    //   Parameters:  path: �ڵ�·�����޷��ݹ鴴���½ڵ㣩
    //                data: �ڵ�����
    //                acl: �ڵ�Ȩ��
    //                create_flag: �ڵ����ͣ�ZOO_EPHEMERAL / ZOO_SEQUENCE��
    //                new_path: ʵ�ʴ����ڵ�����֣�һ�����ڴ���ZOO_SEQUENCE��ǵĴ�������
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error create(const std::string &path, const std::string &data,
            const std::vector<ZKACL> &acl, int create_flag, std::string *new_path);

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  remove
    //  Description:  ɾ���ڵ�
    //   Parameters:  path: �ڵ�·�����޷��ݹ�ɾ��ָ���ڵ㣩
    //                version: �ڵ�汾��-1Ϊǿ��ɾ�������Ӱ汾��
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error remove(const std::string &path, int version);

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  exists
    //  Description:  ���ָ���ڵ��Ƿ����
    //   Parameters:  path: �ڵ�·��
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error exists(const std::string &path) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  exists
    //  Description:  ���ָ���ڵ��Ƿ����
    //   Parameters:  path: �ڵ�·��
    //                stat: ���Σ����ؽڵ�״̬��������ڵĻ���
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error exists(const std::string &path, Stat *stat) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  exists
    //  Description:  ���ָ���ڵ��Ƿ����
    //   Parameters:  path: �ڵ�·��
    //                watch: �����Ƿ�ע�ᵽĬ��Watcher���
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error exists(const std::string &path, bool watch) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  exists
    //  Description:  ���ָ���ڵ��Ƿ����
    //   Parameters:  path: �ڵ�·��
    //                watch: �����Ƿ�ע�ᵽĬ��Watcher���
    //                stat: ���Σ����ؽڵ�״̬��������ڵĻ���
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error exists(const std::string &path, bool watch, Stat *stat) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  exists
    //  Description:  ���ָ���ڵ��Ƿ����
    //   Parameters:  path: �ڵ�·��
    //                watcher: ע��һ���Զ����Watcher��ض���
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error exists(const std::string &path, Watcher *watcher) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  exists
    //  Description:  ���ָ���ڵ��Ƿ����
    //   Parameters:  path: �ڵ�·��
    //                watcher: ע��һ���Զ����Watcher��ض���
    //                stat: ���Σ����ؽڵ�״̬��������ڵĻ���
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error exists(const std::string &path, Watcher *watcher, Stat *stat) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  set_data
    //  Description:  ���ýڵ�����
    //   Parameters:  path: �ڵ�·��
    //                data: �ڵ�����
    //                version: �ڵ�汾�ţ�-1Ϊ���ӽڵ�汾��ǿ���޸ģ�
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error set_data(const std::string &path, const std::string &data, int version);

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  set_data
    //  Description:  ���ýڵ�����
    //   Parameters:  path: �ڵ�·��
    //                data: �ڵ�����
    //                version: �ڵ�汾�ţ�-1Ϊ���ӽڵ�汾��ǿ���޸ģ�
    //                stat: ���Σ����ؽڵ�״̬��������ڵĻ���
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error set_data(const std::string &path, const std::string &data, int version,
            Stat *stat);

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_data
    //  Description:  ��ȡ�ڵ�����
    //   Parameters:  path: �ڵ�·��
    //                data: ���Σ��ڵ�����
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error get_data(const std::string &path, std::string *data) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_data
    //  Description:  ��ȡ�ڵ�����
    //   Parameters:  path: �ڵ�·��
    //                data: ���Σ��ڵ�����
    //                stat: ���Σ����ؽڵ�״̬��������ڵĻ���
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error get_data(const std::string &path, std::string *data, Stat *stat) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_data
    //  Description:  ��ȡ�ڵ�����
    //   Parameters:  path: �ڵ�·��
    //                data: ���Σ��ڵ�����
    //                watch: �����Ƿ�ע�ᵽĬ��Watcher���
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error get_data(const std::string &path, std::string *data, bool watch) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_data
    //  Description:  ��ȡ�ڵ�����
    //   Parameters:  path: �ڵ�·��
    //                data: ���Σ��ڵ�����
    //                watch: �����Ƿ�ע�ᵽĬ��Watcher���
    //                stat: ���Σ����ؽڵ�״̬��������ڵĻ���
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error get_data(const std::string &path, std::string *data,
            bool watch, Stat *stat) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_data
    //  Description:  ��ȡ�ڵ�����
    //   Parameters:  path: �ڵ�·��
    //                data: ���Σ��ڵ�����
    //                watcher: ע��һ���Զ����Watcher��ض���
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error get_data(const std::string &path, std::string *data,
            Watcher *watcher) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_data
    //  Description:  ��ȡ�ڵ�����
    //   Parameters:  path: �ڵ�·��
    //                data: ���Σ��ڵ�����
    //                watcher: ע��һ���Զ����Watcher��ض���
    //                stat: ���Σ����ؽڵ�״̬��������ڵĻ���
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error get_data(const std::string &path, std::string *data,
            Watcher *watcher, Stat *stat) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_children
    //  Description:  ��ȡָ���ڵ���ӽڵ��б�
    //   Parameters:  path: �ڵ�·��
    //                children: �ӽڵ��б�
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error get_children(const std::string path, std::vector<std::string> *children) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_children
    //  Description:  ��ȡָ���ڵ���ӽڵ��б�
    //   Parameters:  path: �ڵ�·��
    //                children: �ӽڵ��б�
    //                stat: ���Σ����ؽڵ�״̬��������ڵĻ���
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error get_children(const std::string path, std::vector<std::string> *children,
            Stat *stat) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_children
    //  Description:  ��ȡָ���ڵ���ӽڵ��б�
    //   Parameters:  path: �ڵ�·��
    //                children: �ӽڵ��б�
    //                watch: �����Ƿ�ע�ᵽĬ��Watcher���
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error get_children(const std::string path, std::vector<std::string> *children,
            bool watch) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_children
    //  Description:  ��ȡָ���ڵ���ӽڵ��б�
    //   Parameters:  path: �ڵ�·��
    //                children: �ӽڵ��б�
    //                watcher: ע��һ���Զ����Watcher��ض���
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error get_children(const std::string path, std::vector<std::string> *children,
            Watcher *watcher) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_children
    //  Description:  ��ȡָ���ڵ���ӽڵ��б�
    //   Parameters:  path: �ڵ�·��
    //                children: �ӽڵ��б�
    //                watch: �����Ƿ�ע�ᵽĬ��Watcher���
    //                stat: ���Σ����ؽڵ�״̬��������ڵĻ���
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error get_children(const std::string path, std::vector<std::string> *children,
            bool watch, Stat *stat) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_children
    //  Description:  ��ȡָ���ڵ���ӽڵ��б�
    //   Parameters:  path: �ڵ�·��
    //                children: �ӽڵ��б�
    //                watcher: ע��һ���Զ����Watcher��ض���
    //                stat: ���Σ����ؽڵ�״̬��������ڵĻ���
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error get_children(const std::string path, std::vector<std::string> *children,
            Watcher *watcher, Stat *stat) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  add_auth_info
    //  Description:  Ϊ��ǰ��������Ȩ��
    //   Parameters:  scheme: Ȩ��ģʽ
    //                cert: ����Ȩ��
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error add_auth_info(const std::string &scheme, const std::string &cert);

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  set_acl
    //  Description:  ���ýڵ��ACLȨ��
    //   Parameters:  path: �ڵ�·��
    //                acl: �ڵ��ACLȨ���б�
    //                version: �ڵ�汾��-1Ϊǿ�����ã����Ӱ汾��
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error set_acl(const std::string path, std::vector<ZKACL> acl, int version);

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_acl
    //  Description:  ��ȡ�ڵ�ACLȨ��
    //   Parameters:  path: �ڵ�·��
    //                acl: ���Σ��ڵ��ACLȨ���б�
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error get_acl(const std::string path, std::vector<ZKACL> *acl) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_acl
    //  Description:  ��ȡ�ڵ�ACLȨ��
    //   Parameters:  path: �ڵ�·��
    //                acl: ���Σ��ڵ��ACLȨ���б�
    //                stat: ���Σ����ؽڵ�״̬��������ڵĻ���
    //  ReturnValue:  error class
    // =====================================================================================
    */
    ZooKeeper::Error get_acl(const std::string path, std::vector<ZKACL> *acl, Stat *stat) const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  register_watcher
    //  Description:  ע�ᣨ�滻��Ĭ�ϼ�����
    //   Parameters:  watcher: ����Ӧ����Watcher�ӿڵ�ʵ�����ָ�룬����ע��ZooKeeper�ļ�����
    //  ReturnValue:  void
    // =====================================================================================
    */
    void register_watcher(Watcher *watcher);

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_client_id
    //  Description:  ��ȡ��ǰ�Ự��clientid
    //   Parameters:  
    //  ReturnValue:  ��ǰ�Ự��clientid��ָ��
    // =====================================================================================
    */
    const clientid_t* get_client_id() const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_session_timeout
    //  Description:  ��ȡ��ǰ�Ự��timeout
    //   Parameters:  
    //  ReturnValue:  timeout
    // =====================================================================================
    */
    int get_session_timeout() const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  get_state
    //  Description:  ��ȡ��ǰZooKeeper������״̬
    //   Parameters:  
    //  ReturnValue:  State class
    // =====================================================================================
    */
    ZooKeeper::State get_state() const;

    /* 
    // ===  FUNCTION  ======================================================================
    //         Name:  recoverable
    //  Description:  ��鵱ǰzookeeper�����Ƿ��ǿɻָ���
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
