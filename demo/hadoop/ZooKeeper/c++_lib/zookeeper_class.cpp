/*
// =====================================================================================
// 
//       Filename:  zookeeper_class.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/06/2016 03:56:59 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Elwin.Gao (elwin), elwin.gao4444@gmail.com
//        Company:  
// 
// =====================================================================================
*/

#include "zookeeper_class.hpp"

using std::string;
using std::vector;

namespace zkclass
{

    // ====================  LIFECYCLE     =======================================

    ZooKeeper::ZooKeeper(const string &connect_string, int session_timeout, Watcher *watcher)
        : _zhandler(nullptr)
    {
        init(connect_string, session_timeout, watcher, nullptr);
    }        // -----  end of method ZooKeeper::ZooKeeper  -----

    ZooKeeper::ZooKeeper(const string &connect_string, int session_timeout, Watcher *watcher,
            clientid_t *clientid)
        : _zhandler(nullptr)
    {
        init(connect_string, session_timeout, watcher, clientid);
    }        // -----  end of method ZooKeeper::ZooKeeper  -----

    ZooKeeper::~ZooKeeper()
    {
        if (_zhandler != nullptr) {
            close();
        }
    }        // -----  end of method ZooKeeper::~ZooKeeper  -----

    // ====================  INTERFACE     =======================================

    ZooKeeper::Error ZooKeeper::close()
    {
        ZooKeeper::Error error(zookeeper_close(_zhandler));
        if (error == ZOK) {
            _zhandler = nullptr;
        }
        return error;
    }        // -----  end of method ZooKeeper::close  -----

    ZooKeeper::Error ZooKeeper::create(const string &path, const string &data,
            const vector<ACL> &acl)
    {
        return ZooKeeper::Error(create(path, data, acl, 0, nullptr));
    }        // -----  end of method ZooKeeper::create  -----

    ZooKeeper::Error ZooKeeper::create(const string &path, const string &data,
            const vector<ACL> &acl, int create_flag)
    {
        return ZooKeeper::Error(create(path, data, acl, create_flag, nullptr));
    }        // -----  end of method ZooKeeper::create  -----

    ZooKeeper::Error ZooKeeper::create(const string &path, const string &data,
            const vector<ACL> &acl, int create_flag, string *new_path)
    {
        ZooKeeper::Error error;
        ACL_vector acl_vector = {0, NULL};
        std::unique_ptr<ACL[]> acl_array = vector_to_array<ACL>(acl);
        acl_vector.data = acl_array.get();
        acl_vector.count = acl.size();
        if (new_path) {
            char new_path_buf[BUFSIZ];
            error = zoo_create(_zhandler, path.c_str(), data.c_str(), data.size(),
                    &acl_vector, create_flag, new_path_buf, BUFSIZ);
            *new_path = new_path_buf;
        } else {
            error = zoo_create(_zhandler, path.c_str(), data.c_str(), data.size(),
                    &acl_vector, create_flag, NULL, 0);
        }
        return error;
    }        // -----  end of method ZooKeeper::create  -----

    ZooKeeper::Error ZooKeeper::remove(const string &path, int version)
    {
        return ZooKeeper::Error(zoo_delete(_zhandler, path.c_str(), version));
    }        // -----  end of method ZooKeeper::remove  -----

    ZooKeeper::Error ZooKeeper::exists(const string &path) const
    {
        return ZooKeeper::Error(exists(path, false, nullptr));
    }        // -----  end of method ZooKeeper::exists  -----

    ZooKeeper::Error ZooKeeper::exists(const string &path, Stat *stat) const
    {
        return ZooKeeper::Error(exists(path, false, stat));
    }        // -----  end of method ZooKeeper::exists  -----

    ZooKeeper::Error ZooKeeper::exists(const string &path, bool watch) const
    {
        return ZooKeeper::Error(exists(path, watch, nullptr));
    }        // -----  end of method ZooKeeper::exists  -----

    ZooKeeper::Error ZooKeeper::exists(const string &path, bool watch, Stat *stat) const
    {
        return ZooKeeper::Error(zoo_exists(_zhandler, path.c_str(), watch?1:0, stat));
    }        // -----  end of method ZooKeeper::exists  -----

    ZooKeeper::Error ZooKeeper::exists(const string &path, Watcher *watcher) const
    {
        return ZooKeeper::Error(exists(path, watcher, nullptr));
    }        // -----  end of method ZooKeeper::exists  -----

    ZooKeeper::Error ZooKeeper::exists(const string &path, Watcher *watcher, Stat *stat) const
    {
        if (watcher == nullptr) {
            return ZooKeeper::Error(zoo_wexists(_zhandler, path.c_str(),
                        nullptr, watcher, stat));
        } else {
            return ZooKeeper::Error(zoo_wexists(_zhandler, path.c_str(),
                        watcher_callback, watcher, stat));
        }
    }        // -----  end of method ZooKeeper::exists  -----

    ZooKeeper::Error ZooKeeper::set_data(const string &path, const string &data, int version)
    {
        return ZooKeeper::Error(zoo_set(_zhandler, path.c_str(), data.c_str(), data.size(),
                    version));
    }        // -----  end of method ZooKeeper::set_data  -----

    ZooKeeper::Error ZooKeeper::set_data(const string &path, const string &data,
            int version, Stat *stat)
    {
        return ZooKeeper::Error(zoo_set2(_zhandler, path.c_str(), data.c_str(), data.size(),
                    version, stat));
    }        // -----  end of method ZooKeeper::set_data  -----

    ZooKeeper::Error ZooKeeper::get_data(const string &path, string *data) const
    {
        return ZooKeeper::Error(get_data(path, data, false, nullptr));
    }        // -----  end of method ZooKeeper::get_data  -----

    ZooKeeper::Error ZooKeeper::get_data(const string &path, string *data, Stat *stat) const
    {
        return ZooKeeper::Error(get_data(path, data, false, stat));
    }        // -----  end of method ZooKeeper::get_data  -----

    ZooKeeper::Error ZooKeeper::get_data(const string &path, string *data, bool watch) const
    {
        return ZooKeeper::Error(get_data(path, data, watch, nullptr));
    }        // -----  end of method ZooKeeper::get_data  -----

    ZooKeeper::Error ZooKeeper::get_data(const string &path, string *data, bool watch,
            Stat *stat) const
    {
        char buf[1048576];    // 1024*1024
        int len = 1048576;    // len is in-param and out-param
        ZooKeeper::Error error(zoo_get(_zhandler, path.c_str(), watch?1:0, buf, &len, stat));
        if (error == ZOK) {
            data->string::~string();    // 重复placement new会导致内存泄漏
            new(data) string(buf, len);
        } else {
            data = nullptr;
        }
        return error;
    }        // -----  end of method ZooKeeper::get_data  -----

    ZooKeeper::Error ZooKeeper::get_data(const string &path, string *data, Watcher *watcher) const
    {
        return ZooKeeper::Error(get_data(path, data, watcher, nullptr));
    }        // -----  end of method ZooKeeper::get_data  -----

    ZooKeeper::Error ZooKeeper::get_data(const string &path, string *data,
            Watcher *watcher, Stat *stat) const
    {
        char buf[1048576];    // 1024*1024
        int len = 1048576;    // len is in-param and out-param
        ZooKeeper::Error error(zoo_wget(_zhandler, path.c_str(),
                    watcher_callback, watcher, buf, &len, stat));
        if (error == ZOK) {
            data->string::~string();    // 重复placement new会导致内存泄漏
            new(data) string(buf, len);
        } else {
            data = nullptr;
        }
        return error;
    }        // -----  end of method ZooKeeper::get_data  -----

    ZooKeeper::Error ZooKeeper::get_children(const string path, vector<string> *children) const
    {
        return ZooKeeper::Error(get_children(path, children, false));
    }        // -----  end of method ZooKeeper::get_children  -----

    ZooKeeper::Error ZooKeeper::get_children(const string path, vector<string> *children,
            Stat *stat) const
    {
        return ZooKeeper::Error(get_children(path, children, false, stat));
    }        // -----  end of method ZooKeeper::get_children  -----

    ZooKeeper::Error ZooKeeper::get_children(const string path, vector<string> *children,
            bool watch) const
    {
        struct String_vector str_vector;
        ZooKeeper::Error error(zoo_get_children(_zhandler, path.c_str(), watch, &str_vector));
        for (int i = 0; i < str_vector.count; ++i) {
            children->emplace_back(string(str_vector.data[i]));
        }
        return error;
    }        // -----  end of method ZooKeeper::get_children  -----

    ZooKeeper::Error ZooKeeper::get_children(const string path, vector<string> *children,
            Watcher *watcher) const
    {
        struct String_vector str_vector;
        ZooKeeper::Error error(zoo_wget_children(_zhandler, path.c_str(),
                    watcher_callback, watcher, &str_vector));
        for (int i = 0; i < str_vector.count; ++i) {
            children->emplace_back(string(str_vector.data[i]));
        }
        return error;
    }        // -----  end of method ZooKeeper::get_children  -----

    ZooKeeper::Error ZooKeeper::get_children(const string path, vector<string> *children,
            bool watch, Stat *stat) const
    {
        struct String_vector str_vector;
        ZooKeeper::Error error(zoo_get_children2(_zhandler, path.c_str(),
                    watch, &str_vector, stat));
        for (int i = 0; i < str_vector.count; ++i) {
            children->emplace_back(string(str_vector.data[i]));
        }
        return error;
    }        // -----  end of method ZooKeeper::get_children  -----

    ZooKeeper::Error ZooKeeper::get_children(const string path, vector<string> *children,
            Watcher *watcher, Stat *stat) const
    {
        struct String_vector str_vector;
        ZooKeeper::Error error(zoo_wget_children2(_zhandler, path.c_str(),
                    watcher_callback, watcher, &str_vector, stat));
        for (int i = 0; i < str_vector.count; ++i) {
            children->emplace_back(string(str_vector.data[i]));
        }
        return error;
    }        // -----  end of method ZooKeeper::get_children  -----

    ZooKeeper::Error ZooKeeper::add_auth_info(const string &scheme, const string &cert)
    {
        return ZooKeeper::Error(zoo_add_auth(_zhandler, scheme.c_str(),
                    cert.c_str(), cert.size(), nullptr, nullptr));
    }        // -----  end of method ZooKeeper::add_auth_info  -----

    ZooKeeper::Error ZooKeeper::set_acl(const string path, vector<ACL> acl, int version)
    {
        ACL_vector acl_vector = {0, NULL};
        std::unique_ptr<ACL[]> acl_array = vector_to_array<ACL>(acl);
        acl_vector.data = acl_array.get();
        acl_vector.count = acl.size();
        return ZooKeeper::Error(zoo_set_acl(_zhandler, path.c_str(), version, &acl_vector));
    }        // -----  end of method ZooKeeper::set_acl  -----

    ZooKeeper::Error ZooKeeper::get_acl(const string path, vector<ACL> *acl) const
    {
        return ZooKeeper::Error(get_acl(path, acl, nullptr));
    }        // -----  end of method ZooKeeper::get_acl  -----

    ZooKeeper::Error ZooKeeper::get_acl(const string path, vector<ACL> *acl, Stat *stat) const
    {
        ACL_vector acl_vector;
        ZooKeeper::Error error(zoo_get_acl(_zhandler, path.c_str(), &acl_vector, stat));
        if (error == ZOK) {
            for (int i = 0; i < acl_vector.count; ++i) {
                acl->push_back(acl_vector.data[i]);
            }
        }
        return error;
    }        // -----  end of method ZooKeeper::get_acl  -----

    void ZooKeeper::register_watcher(Watcher *watcher)
    {
        zoo_set_context(_zhandler, watcher);
    }        // -----  end of method ZooKeeper::register_watcher  -----

    const clientid_t* ZooKeeper::get_client_id() const
    {
        return zoo_client_id(_zhandler);
    }        // -----  end of method ZooKeeper::get_client_id  -----

    int ZooKeeper::get_session_timeout() const
    {
        return zoo_recv_timeout(_zhandler);
    }        // -----  end of method ZooKeeper::get_session_timeout  -----

    ZooKeeper::State ZooKeeper::get_state() const
    {
        return ZooKeeper::State(zoo_state(_zhandler));
    }        // -----  end of method ZooKeeper::get_state  -----

    bool ZooKeeper::recoverable() const
    {
        return is_unrecoverable(_zhandler) == ZINVALIDSTATE ? false : true;
    }        // -----  end of method ZooKeeper::recoverable  -----

    // ==================== PRIVATE METHOD =======================================

    void ZooKeeper::init(const string &connect_string, int session_timeout,
            Watcher *watcher, clientid_t *clientid)
    {
        if (watcher == nullptr) {
            _zhandler = zookeeper_init(connect_string.c_str(),
                    nullptr, session_timeout, clientid, watcher, 0);
        } else {
            _zhandler = zookeeper_init(connect_string.c_str(),
                    watcher_callback, session_timeout, clientid, watcher, 0);
        }
    }        // -----  end of method ZooKeeper::init  -----

    void ZooKeeper::watcher_callback(zhandle_t *zh, int type,
            int state, const char *path, void *watcherCtx)
    {
        Watcher *watcher = (Watcher*)watcherCtx;
        WatchedEvent event(path, type, state);
        watcher->process(event);
    }        // -----  end of method ZooKeeper::watcher_callback  -----

}    // ----- #namespace zkclass  -----

