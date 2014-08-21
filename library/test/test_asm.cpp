/*
// =====================================================================================
// 
//       Filename:  test_asm.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  12/30/2013 06:16:10 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Elwin.Gao (elwin), elwin.gao4444@gmail.com
//        Company:  
// 
// =====================================================================================
*/

#include "../elib_util.hpp"
#include "../elib_asm.hpp"

static void test_case_1()
{
	assert(bsf(0x8000000000000008) == 3);
	assert(bsr(0x8000000000000008) == 8*sizeof(ulong)-1);

	puts("test case 1: ok~");
}

void test_asm()
{
	test_case_1();

	puts("test asm is finished~");
}
