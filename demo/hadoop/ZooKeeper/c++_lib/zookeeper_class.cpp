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

#include <string.h>

#include "zookeeper_class.hpp"

namespace zkclass
{

	// ====================  LIFECYCLE     =======================================

	ZooKeeper::ZooKeeper(const string &connect_string, int session_timeout, Watcher *watcher)
		: m_zhandler(nullptr)
	{
		init(connect_string, session_timeout, watcher, nullptr);
	}		// -----  end of method ZooKeeper::ZooKeeper  -----

	ZooKeeper::ZooKeeper(const string &connect_string, int session_timeout, Watcher *watcher, clientid_t *clientid)
		: m_zhandler(nullptr)
	{
		init(connect_string, session_timeout, watcher, clientid);
	}		// -----  end of method ZooKeeper::ZooKeeper  -----

	ZooKeeper::~ZooKeeper()
	{
	}		// -----  end of method ZooKeeper::~ZooKeeper  -----

	// ====================  INTERFACE     =======================================

	ZooKeeper::Error ZooKeeper::add_auth_info(string scheme, char auth[])
	{
		return ZooKeeper::Error(zoo_add_auth(m_zhandler, scheme.c_str(), auth, strlen(auth), NULL, NULL));
	}		// -----  end of method ZooKeeper::add_auth_info  -----

	ZooKeeper::Error ZooKeeper::close()
	{
		return ZooKeeper::Error(zookeeper_close(m_zhandler));
	}		// -----  end of method ZooKeeper::close  -----

	ZooKeeper::Error ZooKeeper::create(const string &path, char data[], vector<ACL> acl, int create_flag, string *new_path)
	{
		ACL_vector acl_vector;
		std::unique_ptr<ACL[]> acl_array = vector_to_array<ACL>(acl);
		acl_vector.data = acl_array.get();
		acl_vector.count = acl.size();
		char the_new_path[LINESIZE];
		int ret = zoo_create(m_zhandler, path.c_str(), data, strlen(data), &acl_vector, create_flag, the_new_path, LINESIZE);
		*new_path = the_new_path;
		return ret;
	}		// -----  end of method ZooKeeper::create  -----

	ZooKeeper::Error ZooKeeper::remove(const string &path, int version)
	{
		return zoo_delete(m_zhandler, path.c_str(), version);
	}		// -----  end of method ZooKeeper::remove  -----

	ZooKeeper::Error ZooKeeper::exists(string path, int watch, Stat *stat)
	{
		return zoo_exists(m_zhandler, path.c_str(), watch, stat);
	}		// -----  end of method ZooKeeper::exists  -----

	ZooKeeper::Error ZooKeeper::exists(string path, Watcher *watcher, Stat *stat)
	{
		watcher_fn fn = nullptr;
		if (watcher != nullptr) {
			fn = this->watcher_callback;
		}
		return zoo_wexists(m_zhandler, path.c_str(), fn, watcher, stat);
	}		// -----  end of method ZooKeeper::exists  -----

	ZooKeeper::Error ZooKeeper::get_acl(string path, vector<ACL> *acl, Stat *stat)
	{
		return 0;
	}		// -----  end of method ZooKeeper::get_acl  -----

	const clientid_t* ZooKeeper::get_client_id()
	{
		return zoo_client_id(m_zhandler);
	}		// -----  end of method ZooKeeper::get_client_id  -----
	
	int ZooKeeper::get_session_timeout()
	{
		return zoo_recv_timeout(m_zhandler);
	}		// -----  end of method ZooKeeper::get_session_timeout  -----
	
	ZooKeeper::State ZooKeeper::get_state()
	{
		return ZooKeeper::State(zoo_state(m_zhandler));
	}		// -----  end of method ZooKeeper::get_state  -----


	// ==================== PRIVATE METHOD =======================================

	void ZooKeeper::init(const string &connect_string, int session_timeout, Watcher *watcher, clientid_t *clientid)
	{
		if (watcher == nullptr) {
			m_zhandler = zookeeper_init(connect_string.c_str(),
					nullptr, session_timeout, clientid, watcher, 0);
		} else {
			m_zhandler = zookeeper_init(connect_string.c_str(),
					watcher_callback, session_timeout, clientid, watcher, 0);
		}
	}		// -----  end of method ZooKeeper::init  -----

	void ZooKeeper::watcher_callback(zhandle_t *zh, int type,
			int state, const char *path,void *watcherCtx)
	{
		Watcher *watcher = (Watcher*)watcherCtx;
		WatchedEvent event(path, type, state);
		watcher->process(event);
	}		// -----  end of method ZooKeeper::watcher_callback  -----

}	// ----- #namespace zkclass  -----

