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

	//--------------------------------------------------------------------------------------
	//       Class:  ZooKeeper
	//      Method:  ZooKeeper
	// Description:  
	//--------------------------------------------------------------------------------------
	ZooKeeper::ZooKeeper(const string &connect_string, int session_timeout, Watcher *watcher)
		: m_zhandler(nullptr)
	{
		if (watcher == nullptr) {
			m_zhandler = zookeeper_init(connect_string.c_str(),
					nullptr, session_timeout, NULL, watcher, 0);
		} else {
			m_zhandler = zookeeper_init(connect_string.c_str(),
					watcher_callback, session_timeout, NULL, watcher, 0);
		}
	}		// -----  end of method ZooKeeper::ZooKeeper  -----

	//--------------------------------------------------------------------------------------
	//       Class:  ZooKeeper
	//      Method:  ZooKeeper
	// Description:  
	//--------------------------------------------------------------------------------------
	ZooKeeper::ZooKeeper(const string &connect_string, int session_timeout, Watcher *watcher, long session_id, char session_passwd[])
		: m_zhandler(nullptr)
	{
		clientid_t clientid;
		clientid.client_id = session_id;
		strncpy(clientid.passwd, session_passwd, 16);	// 我也没办法，zk头文件写的就是16
		if (watcher == nullptr) {
			m_zhandler = zookeeper_init(connect_string.c_str(),
					nullptr, session_timeout, &clientid, watcher, 0);
		} else {
			m_zhandler = zookeeper_init(connect_string.c_str(),
					watcher_callback, session_timeout, &clientid, watcher, 0);
		}
	}		// -----  end of method ZooKeeper::ZooKeeper  -----

	//--------------------------------------------------------------------------------------
	//       Class:  ZooKeeper
	//      Method:  ~ZooKeeper
	// Description:  
	//--------------------------------------------------------------------------------------
	ZooKeeper::~ZooKeeper()
	{
		if (m_zhandler) {
			close();
		}
	}		// -----  end of method ZooKeeper::~ZooKeeper  -----

	// ====================  INTERFACE     =======================================

	//--------------------------------------------------------------------------------------
	//       Class:  ZooKeeper
	//      Method:  add_auth_info
	// Description:  
	//--------------------------------------------------------------------------------------
	int ZooKeeper::add_auth_info(string scheme, char auth[])
	{
		return zoo_add_auth(m_zhandler, scheme.c_str(), auth, strlen(auth), NULL, NULL);
	}		// -----  end of method ZooKeeper::add_auth_info  -----

	//--------------------------------------------------------------------------------------
	//       Class:  ZooKeeper
	//      Method:  close
	// Description:  
	//--------------------------------------------------------------------------------------
	int ZooKeeper::close()
	{
		int ret = zookeeper_close(m_zhandler);
		if (ret == ZOK) {
			m_zhandler = nullptr;
		}
		return ret;
	}		// -----  end of method ZooKeeper::close  -----

	//--------------------------------------------------------------------------------------
	//       Class:  ZooKeeper
	//      Method:  create
	// Description:  
	//--------------------------------------------------------------------------------------
	int ZooKeeper::create(const string &path, char data[], vector<ACL> acl, int create_flag, string *new_path)
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

	//--------------------------------------------------------------------------------------
	//       Class:  ZooKeeper
	//      Method:  remove
	// Description:  
	//--------------------------------------------------------------------------------------
	int ZooKeeper::remove(const string &path, int version)
	{
		return zoo_delete(m_zhandler, path.c_str(), version);
	}		// -----  end of method ZooKeeper::remove  -----

	//--------------------------------------------------------------------------------------
	//       Class:  ZooKeeper
	//      Method:  exists
	// Description:  
	//--------------------------------------------------------------------------------------
	int ZooKeeper::exists(string path, int watch, Stat *stat)
	{
		return zoo_exists(m_zhandler, path.c_str(), watch, stat);
	}		// -----  end of method ZooKeeper::exists  -----

	//--------------------------------------------------------------------------------------
	//       Class:  ZooKeeper
	//      Method:  exists
	// Description:  
	//--------------------------------------------------------------------------------------
	int ZooKeeper::exists(string path, Watcher *watcher, Stat *stat)
	{
		watcher_fn fn = nullptr;
		if (watcher != nullptr) {
			fn = this->watcher_callback;
		}
		return zoo_wexists(m_zhandler, path.c_str(), fn, watcher, stat);
	}		// -----  end of method ZooKeeper::exists  -----

	//--------------------------------------------------------------------------------------
	//       Class:  ZooKeeper
	//      Method:  get_acl
	// Description:  
	//--------------------------------------------------------------------------------------
	int ZooKeeper::get_acl(string path, vector<ACL> *acl, Stat *stat)
	{
		return 0;
	}		// -----  end of method ZooKeeper::get_acl  -----


	// ==================== PRIVATE METHOD =======================================

	//--------------------------------------------------------------------------------------
	//       Class:  ZooKeeper
	//      Method:  watcher_callback
	// Description:  
	//--------------------------------------------------------------------------------------
	void ZooKeeper::watcher_callback(zhandle_t *zh, int type,
			int state, const char *path,void *watcherCtx)
	{
		Watcher *watcher = (Watcher*)watcherCtx;
		WatchedEvent event(path, type, state);
		watcher->process(event);
	}		// -----  end of method ZooKeeper::watcher_callback  -----

}	// ----- #namespace zkclass  -----

