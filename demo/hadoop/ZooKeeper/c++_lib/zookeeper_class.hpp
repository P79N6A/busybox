/*
// =====================================================================================
// 
//       Filename:  zookeeper_class.hpp
// 
//    Description:  zookeeper的对象化封装，模拟Java接口
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
#include "zookeeper.h"

#include "watcher_class.hpp"
#include "acl_class.hpp"
#include "create_mode_class.hpp"
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
		using byte = unsigned char;

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
		ZooKeeper(string connect_string, int session_timeout, Watcher watcher);

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
		ZooKeeper(string connect_string, int session_timeout, Watcher watcher, bool can_be_readonly);

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
		ZooKeeper(string connect_string, int session_timeout, Watcher watcher, long session_id, byte session_passwd[]);

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
		ZooKeeper(string connect_string, int session_timeout, Watcher watcher, long session_id, byte session_passwd[], bool can_be_readonly);

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
		//         Name:  addAuthInfo
		//  Description:  Add the specified scheme:auth information to this connection.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		void add_auth_info(string scheme, byte auth[]);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  close
		//  Description:  Close this client object.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		void close();

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  create
		//  Description:  Create a node with the given path.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		string create(string path, byte data[], vector<ACL> acl, CreateMode createMode);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  create
		//  Description:  The asynchronous version of create.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		void create(string path, byte data[], vector<ACL> acl, CreateMode createMode, AsyncCallback cb, void *ctx);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  remove
		//  Description:  Remove the node with the given path.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		void remove(string path, int version);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  remove
		//  Description:  The asynchronous version of remove.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		void remove(string path, int version, AsyncCallback cb, void *ctx);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  exists
		//  Description:  Return the stat of the node of the given path.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		Stat exists(string path, bool watch);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  exists
		//  Description:  The asynchronous version of exists.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		void exists(string path, bool watch, AsyncCallback cb, void *ctx);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  exists
		//  Description:  Return the stat of the node of the given path.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		Stat exists(string path, Watcher watcher);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  exists
		//  Description:  The asynchronous version of exists.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		void exists(string path, Watcher watcher, AsyncCallback cb, void *ctx);
		
		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_acl
		//  Description:  Return the ACL and stat of the node of the given path.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		vector<ACL> get_acl(string path, Stat stat);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_acl
		//  Description:  The asynchronous version of get_acl.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		void get_acl(string path, Stat stat, AsyncCallback cb, void *ctx);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_children
		//  Description:  Return the list of the children of the node of the given path.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		vector<string> get_children(string path, bool watch);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_children
		//  Description:  The asynchronous version of getChildren.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		void get_children(string path, bool watch, AsyncCallback cb, void *ctx);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_children
		//  Description:  For the given znode path return the stat and children list.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		vector<string> get_children(string path, bool watch, Stat stat);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_children
		//  Description:  Return the list of the children of the node of the given path.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		vector<string> get_children(string path, Watcher watcher);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_children
		//  Description:  The asynchronous version of getChildren.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		void get_children(string path, Watcher watcher, AsyncCallback cb, void *ctx);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_children
		//  Description:  For the given znode path return the stat and children list.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		void get_children(string path, Watcher watcher, Stat stat);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_data
		//  Description:  The asynchronous version of getData.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		void get_data(string path, bool watch, AsyncCallback cb, void *ctx);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_data
		//  Description:  Return the data and the stat of the node of the given path.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		byte* get_data(string path, bool watch, Stat stat);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_data
		//  Description:  The asynchronous version of getData.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		void get_data(string path, Watcher watcher, AsyncCallback cb, void *ctx);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_data
		//  Description:  Return the data and the stat of the node of the given path.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		byte* get_data(string path, Watcher watcher, Stat stat);
		
		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_session_id
		//  Description:  The session id for this ZooKeeper client instance.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		long get_session_id();

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_session_passwd
		//  Description:  The session password for this ZooKeeper client instance.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		byte* get_session_passwd();

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_session_timeout
		//  Description:  The negotiated session timeout for this ZooKeeper client instance.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		int get_session_timeout();

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_state
		//  Description:   
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		ZooKeeper::State get_state();

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  register
		//  Description:  Specify the default watcher for the connection
		//                (overrides the one specified during construction).
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		void register_watcher(Watcher watcher);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  set_acl
		//  Description:  Set the ACL for the node of the given path if such a node exists
		//                and the given version matches the version of the node.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		Stat set_acl(string path, vector<ACL> acl, int version);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  set_acl
		//  Description:  The asynchronous version of setACL.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		void set_acl(string path, vector<ACL> acl, int version, AsyncCallback cb, void *ctx);
		
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
		Stat set_data(string path, byte data[], int version);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  set_data
		//  Description:  The asynchronous version of setData.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		void set_data(string path, byte data[], int version, AsyncCallback cb, void *ctx);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  sync
		//  Description:  Asynchronous sync.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		void sync(string path, AsyncCallback cb, void *ctx);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_sasl_client
		//  Description:   
		// =====================================================================================
		*/
		void get_sasl_client();

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  multi
		//  Description:   
		// =====================================================================================
		*/
		void multi();

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  transaction
		//  Description:   
		// =====================================================================================
		*/
		void transaction();

		// ====================  ACCESSORS     =======================================

		// ====================  MUTATORS      =======================================

		// ====================  OPERATORS     =======================================

	protected:
		// ====================  DATA MEMBERS  =======================================

	private:
		// ==================== PRIVATE METHOD =======================================

		// ====================  DATA MEMBERS  =======================================

	};		// -----  end of class ZooKeeper  -----

}	// ----- #namespace zkclass  -----

#endif	// ----- #ifndef _ZOOKEEPER_CLASS_HPP_  -----
