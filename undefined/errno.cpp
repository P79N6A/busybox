/*
// =====================================================================================
// 
//       Filename:  errno.cpp
// 
//    Description:  errno & errmsg define
// 
//        Version:  1.0
//        Created:  10/26/2015 10:20:29 PM
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
#include <map>

#define TOKENPASTE(x, y) x ## y
#define TOKENPASTE2(x, y) TOKENPASTE(x, y)

class Error_Wrapper
{
public:
	Error_Wrapper(int num, std::string msg)
	{
		error_map[num] = msg;
	}

	static std::string& errmsg(int num)
	{
		return error_map[num];
	}

private:
	static std::map<int, std::string> error_map;
};
std::map<int, std::string> Error_Wrapper::error_map;
static std::string& errmsg(int num)
{
	return Error_Wrapper::errmsg(num);
}

static std::string errmsg(int num, std::string prefix)
{
	return "[" + prefix + "]" + Error_Wrapper::errmsg(num);
}

#define REGISTER_ERROR(name, num, msg) enum {name = num}; Error_Wrapper TOKENPASTE2(Unique_, __LINE__)(num, msg);

REGISTER_ERROR(SUCCESS, 0, "success msg");
REGISTER_ERROR(FAILURE, -1, "failure msg");

/* 
// ===  FUNCTION  ======================================================================
//         Name:  main
//  Description:  
// =====================================================================================
*/
int main(int argc, char *argv[])
{
	std::cout << SUCCESS << ": " << errmsg(SUCCESS) << std::endl;
	std::cout << FAILURE << ": " << errmsg(FAILURE) << std::endl;

	std::cout << SUCCESS << ": " << errmsg(SUCCESS, "diy prefix") << std::endl;
	std::cout << FAILURE << ": " << errmsg(FAILURE, "diy prefix") << std::endl;

	return EXIT_SUCCESS;
}				// ----------  end of function main  ----------
