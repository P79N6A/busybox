/*
// =====================================================================================
// 
//       Filename:  main.cpp
// 
//    Description:  protobuf用法
//                  官方文档：https://developers.google.com/protocol-buffers/docs/proto
// 
//        Version:  1.0
//        Created:  08/23/2015 11:16:26 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Elwin.Gao (elwin), elwin.gao4444@gmail.com
//        Company:  
// 
// =====================================================================================
*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include "pb2sample.pb.h"

/* 
// ===  FUNCTION  ======================================================================
//         Name:  main
//  Description:  
// =====================================================================================
*/
int main(int argc, char *argv[])
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	// protobuf的基本读写方式
	sample::BasicType basic_type;
	
	// protobuf各种类型的set get方法

	// protobuf和json的转换

	// Optional:  Delete all global objects allocated by libprotobuf.
	google::protobuf::ShutdownProtobufLibrary();

	return EXIT_SUCCESS;
}				// ----------  end of function main  ----------

