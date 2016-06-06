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
	{
		m_watcher = watcher;
		watcher_fn fn = nullptr;
		if (watcher != nullptr) {
			fn = this->global_watcher_fn;
		}
		m_zhandler = zookeeper_init(connect_string.c_str(), fn,
				session_timeout, NULL, this, 0);
		return;
	}		// -----  end of method ZooKeeper::ZooKeeper  -----

	//--------------------------------------------------------------------------------------
	//       Class:  ZooKeeper
	//      Method:  ZooKeeper
	// Description:  
	//--------------------------------------------------------------------------------------
	ZooKeeper::ZooKeeper(const string &connect_string, int session_timeout, Watcher *watcher, long session_id, char session_passwd[])
	{
		m_watcher = watcher;
		watcher_fn fn = nullptr;
		clientid_t clientid;
		if (watcher != nullptr) {
			fn = this->global_watcher_fn;
		}
		clientid.client_id = session_id;
		strncpy(clientid.passwd, session_passwd, 16);	// 我也没办法，zk头文件写的就是16
		m_zhandler = zookeeper_init(connect_string.c_str(), fn,
				session_timeout, &clientid, this, 0);
		return;
	}		// -----  end of method ZooKeeper::ZooKeeper  -----

	//--------------------------------------------------------------------------------------
	//       Class:  ZooKeeper
	//      Method:  ~ZooKeeper
	// Description:  
	//--------------------------------------------------------------------------------------
	ZooKeeper::~ZooKeeper()
	{
	}		// -----  end of method ZooKeeper::~ZooKeeper  -----

	// ====================  INTERFACE     =======================================

	// ==================== PRIVATE METHOD =======================================

	//--------------------------------------------------------------------------------------
	//       Class:  ZooKeeper
	//      Method:  global_watcher_fn
	// Description:  
	//--------------------------------------------------------------------------------------
	void ZooKeeper::global_watcher_fn(zhandle_t *zh, int type,
			int state, const char *path,void *watcherCtx)
	{
		ZooKeeper *obj = (ZooKeeper*)watcherCtx;
		return;
	}		// -----  end of method ZooKeeper::global_watcher_fn  -----

}	// ----- #namespace zkclass  -----

