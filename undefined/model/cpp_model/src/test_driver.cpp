/*
// =====================================================================================
// 
//       Filename:  test_driver.cpp
// 
//    Description:  ��������
// 
//        Version:  1.0
//        Created:  01/16/2013 12:59:28 PM
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

#include <cppunit/TestCase.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <log4cpp/Category.hh>
#include <log4cpp/PropertyConfigurator.hh>

#include "base.hpp"
#include "derived.hpp"

void log4cpp_demo()
{
	/* log4cpp����������ģʽ��1����������ģʽ��2���ļ�����ģʽ����������ģʽ���԰����������������ԭ�������������ǳ������㣬����һ�㶼ʹ���ļ�����ģʽ */
	/* log4cpp���ļ�����ģʽ */
	std::string initFileName = "log4cpp.properties";
	log4cpp::PropertyConfigurator::configure(initFileName);

	log4cpp::Category& root = log4cpp::Category::getRoot();

	log4cpp::Category& sub1 = log4cpp::Category::getInstance(std::string("sub1"));

	log4cpp::Category& sub2 = log4cpp::Category::getInstance(std::string("sub1.sub2"));

	root.warn("Storm is coming");

	sub1.debug("Received storm warning");
	sub1.info("Closing all hatches");

	sub2.debug("Hiding solar panels");
	sub2.error("Solar panels are blocked");
	sub2.debug("Applying protective shield");
	sub2.warn("Unfolding protective shield");
	sub2.info("Solar panels are shielded");

	sub1.info("All hatches closed");

	root.info("Ready for storm.");

	log4cpp::Category::shutdown();
}

// =====================================================================================
//        Class:  base_test
//  Description:  �����������ͨ�����õ����࣬һ����˵��������һ���������Ӧһ��������
// =====================================================================================
class base_test : public CppUnit::TestCase
{
public:
	void setUp()
	{
		std::cout << "base_test::setUp()" << std::endl;
	}

	void tearDown()
	{
		std::cout << "base_test::tearDown()" << std::endl;
	}

	void test_fun_1()
	{
		std::cout << "base_test::test_fun_1()" << std::endl;
		obj.base_fun_1();
	}

	void test_fun_2()
	{
		std::cout << "base_test::test_fun_2()" << std::endl;
		obj.base_fun_2();
	}

	void test_fun_3()
	{
		std::cout << "base_test::test_fun_3()" << std::endl;
		obj.base_fun_3();
	}

	CPPUNIT_TEST_SUITE(base_test);
	CPPUNIT_TEST(test_fun_1);
	CPPUNIT_TEST(test_fun_2);
	CPPUNIT_TEST(test_fun_3);
	CPPUNIT_TEST_SUITE_END();

private:
	Base obj;
};

// =====================================================================================
//        Class:  derived_test
//  Description:  �����һ���õ��ĺ��٣�ֻ���ڶ�������ʽ����ʱ�Ż��õ���derived_testһ��
//                ������дһЩ��base_test֮�ϵ���������
//                ע�⣺derived_test������˵����������в�����Ҫʹ������࣬ʵ���ϣ�����
//                �ι�����Ĳ��ԣ���������������ǻ��໹�������࣬��Ӧ��ʹ��base_testģ��
// =====================================================================================
class derived_test : public base_test
{
public:
	void setUp()
	{
		std::cout << "derived_test::setUp()" << std::endl;
	}

	void tearDown()
	{
		std::cout << "derived_test::tearDown()" << std::endl;
	}

	void test_fun_1()
	{
		std::cout << "derived_test::test_fun_1()" << std::endl;
		obj.base_fun_1();
	}

	void test_fun_2()
	{
		std::cout << "derived_test::test_fun_2()" << std::endl;
		obj.base_fun_2();
	}

	void test_fun_3()
	{
		std::cout << "derived_test::test_fun_3()" << std::endl;
		obj.base_fun_3();
	}

	CPPUNIT_TEST_SUB_SUITE(derived_test, base_test);
	CPPUNIT_TEST(test_fun_1);
	CPPUNIT_TEST(test_fun_2);
	CPPUNIT_TEST(test_fun_3);
	CPPUNIT_TEST_SUITE_END();

private:
	Derived obj;
};

CPPUNIT_TEST_SUITE_REGISTRATION(base_test);	// ���base_testģ�͵Ĳ��Լ���ע�ᣬһ��Զ����������в��ԣ������ע����base_test
CPPUNIT_TEST_SUITE_REGISTRATION(derived_test);	// ���derived_testģ�͵Ĳ��Լ��ϣ����ע��derived_test�Ͳ�����ע��base_test��cppunit���Զ���ִ�л����������
/* 
// ===  FUNCTION  ======================================================================
//         Name:  main
//  Description:  test driver
// =====================================================================================
*/
int main(int argc, char *argv[])
{
	/* �ⲿ�ִ���һ���ǹ̶��ģ����������Ķ�������CPPUNIT_TEST_SUITE_REGISTRATION������� */
	/* ͨ��ִ�д��룬���Է���base_test��3���������������������飬��Ҳ����Ϊʲô�����Ǵ���ʹ��derived_testģ�ͽ��в��Ե�ʱ�򣬾Ͳ�Ӧ����ע��base_testģ�͵�ԭ�� */
	CppUnit::Test *test = CppUnit::TestFactoryRegistry::getRegistry().makeTest();
	CppUnit::TextTestRunner runner;
	runner.addTest(test);
	runner.run();

	/* log4cpp�÷�ʵ�� */
	log4cpp_demo();

	return EXIT_SUCCESS;
}				// ----------  end of function main  ----------
