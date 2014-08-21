/*
 * =====================================================================================
 *
 *       Filename:  test_driver.c
 *
 *    Description:  ��������
 *
 *        Version:  1.0
 *        Created:  01/10/2013 01:13:45 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Elwin.Gao (elwin), elwin.gao4444@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdio.h>

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
/* #include <CUnit/Automated.h> */

#include <log4c.h>

#include "demo.h"
#include "demo_test.h"

/* ����log4c���÷� */
static void log4c_demo()
{
	log4c_category_t* runlog = NULL;

	if (log4c_init()){
		printf("log4c_init() failed");
		return;
	}

	runlog = log4c_category_get("runlog");
	log4c_category_log(runlog, LOG4C_PRIORITY_ERROR, "Hello World!");

	/*  Explicitly call the log4c cleanup routine */
	if ( log4c_fini()){                                                                                                                           
		printf("log4c_fini() failed");
		return;
	}   
}

enum BOOL { FALSE=0, TRUE=1 };

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  test_driver
 * =====================================================================================
 */
int main(int argc, char *argv[])
{
	CU_TestInfo cases_a[] = {	/* ������Լ���A�������������� */
		{"ģ��A-��������1", test_a_1},
		{"ģ��A-��������2", test_a_2},
		{"ģ��A-��������3", test_a_3},
		CU_TEST_INFO_NULL
	};

	CU_TestInfo cases_b[] = {	/* ������Լ���B�������������� */
		{"ģ��B-��������1", test_b_1},
		{"ģ��B-��������2", test_b_2},
		{"ģ��B-��������3", test_b_3},
		CU_TEST_INFO_NULL
	};

	CU_TestInfo cases_c[] = {	/* ������Լ���C�������������� */
		{"ģ��C-��������1", test_c_1},
		{"ģ��C-��������2", test_c_2},
		{"ģ��C-��������3", test_c_3},
		CU_TEST_INFO_NULL
	};

	/* ˵�����˴���û�г���CU_pSuite������������Ϊcunit���ԡ���������Ϊ������������Լ��ϵ�Ψһ��ʶ�����Ǳ��� */
	CU_SuiteInfo suites[] = {	/* �����������Լ��� */
		{"���Լ���A", test_a_init, test_a_destroy, cases_a},
		{"���Լ���B", test_b_init, test_b_destroy, cases_b},
		{"���Լ���C", test_c_init, test_c_destroy, cases_c},
		CU_SUITE_INFO_NULL
	};

	/* ��ʼ��cunit */
	if (CU_initialize_registry() == CUE_NOMEMORY) {
		fprintf(stderr, "CU_initialize_registry fault!\n");
		exit(EXIT_FAILURE);
	}

	/* ��cunitע����Լ��� */
	if (CU_register_suites(suites) != CUE_SUCCESS) {
		fprintf(stderr, "CU_register_suites fault!\n");
	}

	/* ���ò��Լ��ϵļ����־ */
	CU_set_suite_active(CU_get_suite("���Լ���A"), TRUE);	/* ������Լ���A */
	CU_set_suite_active(CU_get_suite("���Լ���B"), FALSE);	/* ��������Լ���B */
	CU_set_suite_active(CU_get_suite("���Լ���C"), TRUE);	/* ������Լ���C */

	/* ���ò��������ļ����־ */
	CU_set_test_active(CU_get_test(CU_get_suite("���Լ���A"), "ģ��A-��������1"), TRUE);
	CU_set_test_active(CU_get_test(CU_get_suite("���Լ���A"), "ģ��A-��������2"), TRUE);
	CU_set_test_active(CU_get_test(CU_get_suite("���Լ���A"), "ģ��A-��������3"), TRUE);
	CU_set_test_active(CU_get_test(CU_get_suite("���Լ���B"), "ģ��B-��������1"), TRUE);	/* ���ڲ��Լ���Bδ�������ģ��B�Ĳ�����������ִ�� */
	CU_set_test_active(CU_get_test(CU_get_suite("���Լ���B"), "ģ��B-��������2"), TRUE);	/* ���ڲ��Լ���Bδ�������ģ��B�Ĳ�����������ִ�� */
	CU_set_test_active(CU_get_test(CU_get_suite("���Լ���B"), "ģ��B-��������3"), TRUE);	/* ���ڲ��Լ���Bδ�������ģ��B�Ĳ�����������ִ�� */
	CU_set_test_active(CU_get_test(CU_get_suite("���Լ���C"), "ģ��C-��������1"), TRUE);
	CU_set_test_active(CU_get_test(CU_get_suite("���Լ���C"), "ģ��C-��������2"), FALSE);	/* ������"ģ��C-��������2" */
	CU_set_test_active(CU_get_test(CU_get_suite("���Լ���C"), "ģ��C-��������3"), TRUE);

	/* ִ�в��� */
	CU_basic_run_tests();	/* �������ִ�з�ʽ���ǽ����������Խ���������Ļ */
	/* xml��ʽ�������Խ���������ǰĿ¼�£���������xml�ļ�����Ҫ��Ͽ��ļ���6��xml�������ļ����鿴���Խ�� */
	/*
	CU_set_output_filename("test");
	CU_list_tests_to_file();
	CU_automated_run_tests();
	*/

	/* ����cunitע��������ֹ�ڴ�й© */
	CU_cleanup_registry();

	log4c_demo();	/* ����log4c���÷� */

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
