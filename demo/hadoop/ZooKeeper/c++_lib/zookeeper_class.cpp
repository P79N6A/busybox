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

	ZooKeeper::ZooKeeper(const string &connect_string, int session_timeout, Watcher *watcher, clientid_t *clientid)
		: m_zhandler(nullptr)
	{
		if (watcher == nullptr) {
			m_zhandler = zookeeper_init(connect_string.c_str(),
					nullptr, session_timeout, clientid, watcher, 0);
		} else {
			m_zhandler = zookeeper_init(connect_string.c_str(),
					watcher_callback, session_timeout, clientid, watcher, 0);
		}
	}		// -----  end of method ZooKeeper::ZooKeeper  -----

	ZooKeeper::~ZooKeeper()
	{
		if (m_zhandler != nullptr) {
			close();
		}
	}		// -----  end of method ZooKeeper::~ZooKeeper  -----

	// ====================  INTERFACE     =======================================

	ZooKeeper::Error ZooKeeper::close()
	{
		ZooKeeper::Error error(zookeeper_close(m_zhandler));
		if (error.value() == ZOK) {
			m_zhandler = nullptr;
		}
		return error;
	}		// -----  end of method ZooKeeper::close  -----

	ZooKeeper::Error ZooKeeper::create(const string &path, const char data[], int data_size,
			vector<ACL> acl, int create_flag, string *new_path)
	{
		ZooKeeper::Error error;
		ACL_vector acl_vector = {0, NULL};
		std::unique_ptr<ACL[]> acl_array = vector_to_array<ACL>(acl);
		acl_vector.data = acl_array.get();
		acl_vector.count = acl.size();
		if (new_path) {
			char new_path_buf[LINESIZE];
			error = zoo_create(m_zhandler, path.c_str(), data, data_size, &acl_vector, create_flag, new_path_buf, LINESIZE);
			*new_path = new_path_buf;
		} else {
			error = zoo_create(m_zhandler, path.c_str(), data, data_size, &ZOO_OPEN_ACL_UNSAFE, create_flag, NULL, 0);
		}
		return error;
	}		// -----  end of method ZooKeeper::create  -----

	ZooKeeper::Error ZooKeeper::remove(const string &path, int version)
	{
		return ZooKeeper::Error(zoo_delete(m_zhandler, path.c_str(), version));
	}		// -----  end of method ZooKeeper::remove  -----

	ZooKeeper::Error ZooKeeper::exists(const string &path, bool watch, Stat *stat)
	{
		return ZooKeeper::Error(zoo_exists(m_zhandler, path.c_str(), watch?1:0, stat));
	}		// -----  end of method ZooKeeper::exists  -----

	ZooKeeper::Error ZooKeeper::exists(const string &path, Watcher *watcher, Stat *stat)
	{
		if (watcher == nullptr) {
			return ZooKeeper::Error(zoo_wexists(m_zhandler, path.c_str(), nullptr, watcher, stat));
		} else {
			return ZooKeeper::Error(zoo_wexists(m_zhandler, path.c_str(), watcher_callback, watcher, stat));
		}
	}		// -----  end of method ZooKeeper::exists  -----

	ZooKeeper::Error ZooKeeper::set_data(const string &path, const char data[], int data_size, int version)
	{
		return ZooKeeper::Error(zoo_set(m_zhandler, path.c_str(), data, data_size, version));
	}		// -----  end of method ZooKeeper::set_data  -----

	ZooKeeper::Error ZooKeeper::set_data(const string &path, const char data[], int data_size, int version, Stat *stat)
	{
		return ZooKeeper::Error(zoo_set2(m_zhandler, path.c_str(), data, data_size, version, stat));
	}		// -----  end of method ZooKeeper::set_data  -----

	ZooKeeper::Error ZooKeeper::get_data(const string &path, char data[], int *data_size, bool watch, Stat *stat)
	{
		return ZooKeeper::Error(zoo_get(m_zhandler, path.c_str(), watch?1:0, data, data_size, stat));
	}		// -----  end of method ZooKeeper::get_data  -----

	ZooKeeper::Error ZooKeeper::get_data(const string &path, char data[], int *data_size, Watcher *watcher, Stat *stat)
	{
		return ZooKeeper::Error(zoo_wget(m_zhandler, path.c_str(), watcher_callback, watcher, data, data_size, stat));
	}		// -----  end of method ZooKeeper::get_data  -----

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

	void ZooKeeper::watcher_callback(zhandle_t *zh, int type,
			int state, const char *path,void *watcherCtx)
	{
		Watcher *watcher = (Watcher*)watcherCtx;
		WatchedEvent event(path, type, state);
		watcher->process(event);
	}		// -----  end of method ZooKeeper::watcher_callback  -----

}	// ----- #namespace zkclass  -----

