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
#include <sstream>
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

	// 1、protobuf类型的set get方法
	sample::BasicType basic_type;
	basic_type.set_b(true);
	basic_type.set_i32(32);
	basic_type.set_i64(64);
	basic_type.set_s("string");

	// 2、protobuf的基本读写方式
	//
	// PB读写文件的方式有很多，其中最最基本的方式有：
	//
	// Heavy I/O
	// bool	ParseFromIstream(istream * input) [message.h]
	// bool	SerializePartialToOstream(ostream * output) const [message.h]
	// bool	ParseFromFileDescriptor(int file_descriptor) [message.h]
	// bool	SerializeToFileDescriptor(int file_descriptor) const [message.h]
	// 详见：https://developers.google.com/protocol-buffers/docs/reference/cpp/google.protobuf.message
	//
	// Lite I/O
	// bool	ParseFromString(const string & data) [message_lite.h]
	// bool	SerializeToString(string * output) const [message_lite.h]
	// 详见：https://developers.google.com/protocol-buffers/docs/reference/cpp/google.protobuf.message_lite

	std::ofstream output("pb2sample.data");
	if (!basic_type.SerializeToOstream(&output)) {
		std::cout << "failed to serialize file." << std::endl;
		return EXIT_FAILURE;
	}
	output.flush();

	basic_type.Clear();	//Message的Clear方法用于清空这个Message下所有数据（注意Clear首字母C要大写）
	std::ifstream input("pb2sample.data");
	if (input) {
		if (!basic_type.ParseFromIstream(&input)) {
			std::cout << "failed to parse file." << std::endl;
			return EXIT_FAILURE;
		}
	} else {
		std::cout << "file not found." << std::endl;
		return EXIT_FAILURE;
	}
	assert(basic_type.b() == true);
	assert(basic_type.i32() == 32);
	assert(basic_type.i64() == 64);
	assert(basic_type.s() == "string");

	// protobuf和json的转换

	// Optional:  Delete all global objects allocated by libprotobuf.
	google::protobuf::ShutdownProtobufLibrary();

	return EXIT_SUCCESS;
}				// ----------  end of function main  ----------

