#include "elib_util.hpp"

void test_util();

void test_queue();
void test_stack();

void test_mm_seg();
void test_mm_block();
void test_mm_fixed();

void test_time();
void test_hash();
void test_log();
void test_asm();
void test_bitmap();

void test_communication_tcp();

/* 
// ===  FUNCTION  ======================================================================
//         Name:  main
//  Description:  
// =====================================================================================
*/
int main(/* int argc, char *argv[] */)
{
	test_util();

	test_queue();
	test_stack();

	test_mm_seg();
	test_mm_block();
	test_mm_fixed();

	test_time();
	test_hash();
	test_log();
	test_asm();
	test_bitmap();
	test_communication_tcp();

	puts("all test is finished~");

	return EXIT_SUCCESS;
}				// ----------  end of function main  ----------

