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
