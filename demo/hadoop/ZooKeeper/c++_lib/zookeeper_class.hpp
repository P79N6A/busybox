/*
// =====================================================================================
// 
//       Filename:  zookeeper_class.hpp
// 
//    Description:  zookeeper的对象化封装，模拟Java接口
//                  接口设计参照：https://zookeeper.apache.org/doc/r3.4.8/api/index.html
// 
//        Version:  1.0
//        Created:  06/03/2016 08:02:15 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Elwin.Gao (elwin), elwin.gao4444@gmail.com
//        Company:  
// 
// =====================================================================================
*/

#ifndef  _ZOOKEEPER_CLASS_HPP_
#define  _ZOOKEEPER_CLASS_HPP_

#include <string>
#include <vector>
#include <memory>
#include "zookeeper.h"

#include "watcher_class.hpp"
#include "async_callback_class.hpp"

using std::string;
using std::vector;

namespace zkclass
{
	// =====================================================================================
	//        Class:  ZooKeeper
	//  Description:  
	// =====================================================================================
	class ZooKeeper
	{
	public:
		enum State
		{
		};
		// ====================  LIFECYCLE     =======================================

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  ZooKeeper
		//  Description:  To create a ZooKeeper client object, the application needs to pass a
		//                connection string containing a comma separated list of host:port pairs,
		//                each corresponding to a ZooKeeper server.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		ZooKeeper(const string &connect_string, int session_timeout, Watcher *watcher);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  ZooKeeper
		//  Description:  To create a ZooKeeper client object, the application needs to pass a
		//                connection string containing a comma separated list of host:port pairs,
		//                each corresponding to a ZooKeeper server.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		ZooKeeper(const string &connect_string, int session_timeout, Watcher *watcher, long session_id, char session_passwd[]);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  ~ZooKeeper
		//  Description:   
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		~ZooKeeper();

		// ====================  INTERFACE     =======================================

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  add_auth_info
		//  Description:  Add the specified scheme:auth information to this connection.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		int add_auth_info(string scheme, char auth[]);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  close
		//  Description:  Close this client object.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		int close();

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  create
		//  Description:  Create a node with the given path.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		int create(const string &path, char data[], vector<ACL> acl, int create_flag, string *new_path);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  remove
		//  Description:  Remove the node with the given path.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		int remove(const string &path, int version);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  exists
		//  Description:  Return the stat of the node of the given path.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		int exists(string path, int watch, Stat *stat);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  exists
		//  Description:  Return the stat of the node of the given path.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		int exists(string path, Watcher *watcher, Stat *stat);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_acl
		//  Description:  Return the ACL and stat of the node of the given path.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		int get_acl(string path, vector<ACL> *acl, Stat *stat);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_children
		//  Description:  Return the list of the children of the node of the given path.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
//		*/
//		vector<string> get_children(string path, bool watch);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_children
		//  Description:  For the given znode path return the stat and children list.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
//		vector<string> get_children(string path, bool watch, Stat stat);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_children
		//  Description:  Return the list of the children of the node of the given path.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
//		vector<string> get_children(string path, Watcher watcher);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_children
		//  Description:  For the given znode path return the stat and children list.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
//		void get_children(string path, Watcher watcher, Stat stat);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_data
		//  Description:  Return the data and the stat of the node of the given path.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
//		char* get_data(string path, bool watch, Stat stat);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_data
		//  Description:  Return the data and the stat of the node of the given path.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
//		char* get_data(string path, Watcher watcher, Stat stat);
		
		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_session_id
		//  Description:  The session id for this ZooKeeper client instance.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
//		long get_session_id();

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_session_passwd
		//  Description:  The session password for this ZooKeeper client instance.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
//		char* get_session_passwd();

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_session_timeout
		//  Description:  The negotiated session timeout for this ZooKeeper client instance.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
//		int get_session_timeout();

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_state
		//  Description:   
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
//		ZooKeeper::State get_state();

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  register
		//  Description:  Specify the default watcher for the connection
		//                (overrides the one specified during construction).
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
//		void register_watcher(Watcher watcher);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  set_acl
		//  Description:  Set the ACL for the node of the given path if such a node exists
		//                and the given version matches the version of the node.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
//		Stat set_acl(string path, vector<ACL> acl, int version);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  set_data
		//  Description:  Set the data for the node of the given path if such a node exists
		//                and the given version matches the version of the node
		//                (if the given version is -1, it matches any node's versions).
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
//		Stat set_data(string path, char data[], int version);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  create
		//  Description:  The asynchronous version of create.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
//		void create(string path, char data[], vector<ACL> acl, int create_flag, AsyncCallback cb, void *ctx);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  remove
		//  Description:  The asynchronous version of remove.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
//		void remove(string path, int version, AsyncCallback cb, void *ctx);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  exists
		//  Description:  The asynchronous version of exists.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
//		void exists(string path, bool watch, AsyncCallback cb, void *ctx);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  exists
		//  Description:  The asynchronous version of exists.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
//		void exists(string path, Watcher watcher, AsyncCallback cb, void *ctx);
		
		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_acl
		//  Description:  The asynchronous version of get_acl.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
//		void get_acl(string path, Stat stat, AsyncCallback cb, void *ctx);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_children
		//  Description:  The asynchronous version of getChildren.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
//		void get_children(string path, bool watch, AsyncCallback cb, void *ctx);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_children
		//  Description:  The asynchronous version of getChildren.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
//		void get_children(string path, Watcher watcher, AsyncCallback cb, void *ctx);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_data
		//  Description:  The asynchronous version of getData.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
//		void get_data(string path, bool watch, AsyncCallback cb, void *ctx);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_data
		//  Description:  The asynchronous version of getData.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
//		void get_data(string path, Watcher watcher, AsyncCallback cb, void *ctx);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  set_acl
		//  Description:  The asynchronous version of setACL.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
//		void set_acl(string path, vector<ACL> acl, int version, AsyncCallback cb, void *ctx);
		
		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  set_data
		//  Description:  The asynchronous version of setData.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
//		void set_data(string path, char data[], int version, AsyncCallback cb, void *ctx);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  sync
		//  Description:  Asynchronous sync.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
//		void sync(string path, AsyncCallback cb, void *ctx);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  multi
		//  Description:   
		// =====================================================================================
		*/
//		void multi();

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  ok
		//  Description:   
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		inline bool ok()
		{
			return m_zhandler != nullptr;
		}		// -----  end of function ok  -----
		
	private:
		// ==================== PRIVATE METHOD =======================================

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  register_obj_class_by_watcher_fn
		//  Description:   
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		inline watcher_fn register_watcher_obj_by_watcher_fn(Watcher *obj)
		{
			watcher_fn fn = nullptr;
			if (obj != nullptr) {
				fn = this->watcher_callback;
			}
			return fn;
		}		// -----  end of function register_watcher_obj_by_watcher_fn  -----

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  vector_to_array
		//  Description:   
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		template <class T>
		inline void vector_to_array(vector<T> vec, std::unique_ptr<T[]> arr)
		{
			return;
		}		// -----  end of template function vector_to_array  -----

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  array_to_vector
		//  Description:   
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		template <class T>
		inline void array_to_vector(std::unique_ptr<T[]> arr, vector<T> vec)
		{
			return;
		}		// -----  end of template function array_to_vector  -----

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
		zhandle_t *m_zhandler;
		clientid_t m_clientid;

		const size_t LINESIZE = 1024;
	};		// -----  end of class ZooKeeper  -----

}	// ----- #namespace zkclass  -----

#endif	// ----- #ifndef _ZOOKEEPER_CLASS_HPP_  -----
