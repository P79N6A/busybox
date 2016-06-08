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
#include "watched_event_class.hpp"
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
		// ====================  INNER CLASS   =======================================

		// =====================================================================================
		//        Class:  Error
		//  Description:  
		// =====================================================================================
		class Error
		{
		public:
			// ====================  LIFECYCLE     =======================================
			Error() : m_error(ZOK)
			{
			}

			Error(int error) : m_error(error)
			{
			}

			~Error()
			{
			}

			// ====================  INTERFACE     =======================================
			int value()
			{
				return m_error;
			}

			const char* c_str()
			{
				/* Everything is OK */
				if (m_error == ZOK)
					return "ZOK";

				/* System and server-side errors */
				if (m_error == ZSYSTEMERROR)
					return "ZSYSTEMERROR";
				if (m_error == ZRUNTIMEINCONSISTENCY)
					return "ZRUNTIMEINCONSISTENCY";
				if (m_error == ZDATAINCONSISTENCY)
					return "ZDATAINCONSISTENCY";
				if (m_error == ZCONNECTIONLOSS)
					return "ZCONNECTIONLOSS";
				if (m_error == ZMARSHALLINGERROR)
					return "ZMARSHALLINGERROR";
				if (m_error == ZUNIMPLEMENTED)
					return "ZUNIMPLEMENTED";
				if (m_error == ZOPERATIONTIMEOUT)
					return "ZOPERATIONTIMEOUT";
				if (m_error == ZBADARGUMENTS)
					return "ZBADARGUMENTS";
				if (m_error == ZINVALIDSTATE)
					return "ZINVALIDSTATE";

				/* API errors */
				if (m_error == ZAPIERROR)
					return "ZAPIERROR";
				if (m_error == ZNONODE)
					return "ZNONODE";
				if (m_error == ZNOAUTH)
					return "ZNOAUTH";
				if (m_error == ZBADVERSION)
					return "ZBADVERSION";
				if (m_error == ZNOCHILDRENFOREPHEMERALS)
					return "ZNOCHILDRENFOREPHEMERALS";
				if (m_error == ZNODEEXISTS)
					return "ZNODEEXISTS";
				if (m_error == ZNOTEMPTY)
					return "ZNOTEMPTY";
				if (m_error == ZSESSIONEXPIRED)
					return "ZSESSIONEXPIRED";
				if (m_error == ZINVALIDCALLBACK)
					return "ZINVALIDCALLBACK";
				if (m_error == ZINVALIDACL)
					return "ZINVALIDACL";
				if (m_error == ZAUTHFAILED)
					return "ZAUTHFAILED";
				if (m_error == ZCLOSING)
					return "ZCLOSING";
				if (m_error == ZNOTHING)
					return "ZNOTHING";
				if (m_error == ZSESSIONMOVED)
					return "ZSESSIONMOVED";

				return "ZUNKNOWNERROR";
			}

			const char* desc()
			{
				/* Everything is OK */
				if (m_error == ZOK)
					return "Everything is OK";

				/* System and server-side errors */
				if (m_error == ZSYSTEMERROR)
					return "system error";
				if (m_error == ZRUNTIMEINCONSISTENCY)
					return "A runtime inconsistency was found";
				if (m_error == ZDATAINCONSISTENCY)
					return "A data inconsistency was found";
				if (m_error == ZCONNECTIONLOSS)
					return "Connection to the server has been lost";
				if (m_error == ZMARSHALLINGERROR)
					return "Error while marshalling or unmarshalling data";
				if (m_error == ZUNIMPLEMENTED)
					return "Operation is unimplemented";
				if (m_error == ZOPERATIONTIMEOUT)
					return "Operation timeout";
				if (m_error == ZBADARGUMENTS)
					return "Invalid arguments";
				if (m_error == ZINVALIDSTATE)
					return "Invliad zhandle state";

				/* API errors */
				if (m_error == ZAPIERROR)
					return "api error";
				if (m_error == ZNONODE)
					return "Node does not exist";
				if (m_error == ZNOAUTH)
					return "Not authenticated";
				if (m_error == ZBADVERSION)
					return "Version conflict";
				if (m_error == ZNOCHILDRENFOREPHEMERALS)
					return "Ephemeral nodes may not have children";
				if (m_error == ZNODEEXISTS)
					return "The node already exists";
				if (m_error == ZNOTEMPTY)
					return "The node has children";
				if (m_error == ZSESSIONEXPIRED)
					return "The session has been expired by the server";
				if (m_error == ZINVALIDCALLBACK)
					return "Invalid callback specified";
				if (m_error == ZINVALIDACL)
					return "Invalid ACL specified";
				if (m_error == ZAUTHFAILED)
					return "Client authentication failed";
				if (m_error == ZCLOSING)
					return "ZooKeeper is closing";
				if (m_error == ZNOTHING)
					return "(not error) no server responses to process";
				if (m_error == ZSESSIONMOVED)
					return "session moved to another server, so operation is ignored";

				return "unknown error";
			}

		private:
			// ==================== PRIVATE METHOD =======================================

			// ====================  DATA MEMBERS  =======================================
			int m_error;

		};		// -----  end of class Error  -----

		using State = Watcher::State;

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
		ZooKeeper(const string &connect_string, int session_timeout, Watcher *watcher, clientid_t *clientid);

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
		//         Name:  close
		//  Description:  Close this client object.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		ZooKeeper::Error close();

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  create
		//  Description:  Create a node with the given path.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		ZooKeeper::Error create(const string &path, const char data[], int data_size, vector<ACL> acl, int create_flag, string *new_path);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  remove
		//  Description:  Remove the node with the given path.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		ZooKeeper::Error remove(const string &path, int version);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  exists
		//  Description:  Return the stat of the node of the given path.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		ZooKeeper::Error exists(const string &path, bool watch, Stat *stat);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  exists
		//  Description:  Return the stat of the node of the given path.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		ZooKeeper::Error exists(const string &path, Watcher *watcher, Stat *stat);

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
		ZooKeeper::Error set_data(const string &path, const char data[], int data_size, int version);

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
		ZooKeeper::Error set_data(const string &path, const char data[], int data_size, int version, Stat *stat);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_data
		//  Description:  Return the data and the stat of the node of the given path.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		ZooKeeper::Error get_data(const string &path, char data[], int *data_size, bool watch, Stat *stat);

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  get_data
		//  Description:  Return the data and the stat of the node of the given path.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		ZooKeeper::Error get_data(const string &path, char data[], int *data_size, Watcher *watcher, Stat *stat);
		
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
		//         Name:  add_auth_info
		//  Description:  Add the specified scheme:auth information to this connection.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
//		ZooKeeper::Error add_auth_info(string scheme, char auth[]);

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
		//         Name:  get_acl
		//  Description:  Return the ACL and stat of the node of the given path.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
//		ZooKeeper::Error get_acl(string path, vector<ACL> *acl, Stat *stat);

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
		//         Name:  get_client_id
		//  Description:  The session id, session password for this ZooKeeper client instance.
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		const clientid_t* get_client_id();

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

	private:
		// ==================== PRIVATE METHOD =======================================

		/* 
		// ===  FUNCTION  ======================================================================
		//         Name:  vector_to_array
		//  Description:   
		//   Parameters:  
		//  ReturnValue:  
		// =====================================================================================
		*/
		template <class T>
		inline std::unique_ptr<T[]> vector_to_array(vector<T> vec)
		{
			std::unique_ptr<T[]> array(new T[vec.size()]);
			for (int i=0; i<vec.size(); ++i) {
				array[i] = vec[i];
			}
			return array;
		}		// -----  end of template function vector_to_array  -----

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
