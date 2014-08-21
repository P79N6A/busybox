/*
// =====================================================================================
// 
//       Filename:  demo.cpp
// 
//    Description:  ����auto_ptr��ʹ�÷���������ȱ��
//    		auto_ptr��ʹ�õļ�������RAII��������ջ�Զ����յ����Ի��յ�ַ�ռ�
//    		auto_ptr�ĳ��֣���Ҫ��Ϊ�˽�������쳣�׳�ʱ������Դй©��������
//    		�ο���http://www.cppblog.com/SmartPtr/archive/2007/07/05/27549.html
//    		auto_ptrԴ���룺http://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-api-4.5/a00745_source.html
// 
//        Version:  1.0
//        Created:  10/10/2012 05:26:11 PM
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
#include <memory>

/* 
// ===  FUNCTION  ======================================================================
//         Name:  main
//  Description:  test driver
// =====================================================================================
*/
int main(int argc, char *argv[])
{
	/* ��������һ��auto_ptr���÷� */
	int *pointer1 = new int(0);
	int *pointer2 = new int(1);
	std::auto_ptr<int> ap(pointer1);
	std::cout << *pointer1 << ',' << *ap << std::endl;
	std::cout << pointer1 << ',' << ap.get() << std::endl;
//	ap.release();	// release��ʹ��auto_ptr�ڲ�ָ����ΪNULL����ȴ�����ͷŵ�ַ�ռ䣬���������ע�͵���һ��������ڴ�й©
//	std::cout << pointer1 << ',' << ap.get() << std::endl;
	ap.reset(pointer2);	// reset�����ͷ�֮ǰ�ĵ�ַ�ռ䣨�����ΪNULL�����������µĵ�ַ�ռ䣬�����Ǹ�ֵ
	std::cout << pointer2 << ',' << ap.get() << std::endl;
	std::cout << *pointer2 << ',' << *ap << std::endl;
	/* 
	 * ���⣬auto_ptr��֧��'*'��'='��'->'���ֲ������京�����ָͨ������ 
	 * ����'*'��'->'������Լ򵥣�ûʲô��Ҫ�ر�ע��ĵط�
	 * ��'='������Ҫ�ر�ע�⣺��=����ʹ��release()������reset()��ʹ�ò�����������ڴ�й© 
	 */
	return EXIT_SUCCESS;	// ���򵽴˽���

	/* ����������auto_ptr���ڵ����� */

	/* ���ȣ�auto_ptrָ�벻��ָ��洢��heap����ı��� */
	int i = 10;
	std::auto_ptr<int> ap1(&i);	// auto_ptr�����ͷ�stack�ϵı���

	/* 
	 * �ڶ���Ҫע�⣬����auto_ptr��������ʱ��һ�����������ͷŵ�ַ�ռ�
	 * ���ԣ�����������auto_ptrָ��ͬһ����ַ������ᷢ���ظ��ͷŵ�����
	 */
	int *p = new int(0);
	std::auto_ptr<int> ap2(p);
	std::auto_ptr<int> ap3(p);

	/* ����������auto_ptr��������ʹ�õ���delete������delete[]�����Բ�����auto_ptr����������ָ�� */
	int *pa = new int[10];
	std::auto_ptr<int> ap4(pa);

	/* ����auto_ptr�Ĺ��캯��ʹ����explicit�ؼ��֣�����һ�С��㡱ָ����auto_ptr����ʽת����������ֹ */
	/* ��ΪC++��֤��ɾ��һ����ָ���ǰ�ȫ�ģ�����auto_ptr������ʱ��û�б�Ҫ�ж�ָ���Ƿ�ΪNULL */

	/* 
	 * auto_ptr�Ŀ������̣���ʵ���ƽ����̣�ԭ������ʧȥ��ָ��Ŀ��Ʊ�ΪNULL 
	 * ��һ������Σ���������ڲ������ݹ����У���Ϊ���ֿ���̫����������
	 */

	/* ����auto_ptrû��ֵ���壬���Բ��ܱ�����stl��׼������ */

	/* 
	 * �ܽ᣺
	 * ��Ȼ����������ܵĻ�����ȫ�棬����Ҳ�ܿ���auto_ptr��ʹ����Ҫ�ǳ��Ľ���
	 * ���ִ�����ֱ��ʹ����ָ�벻�����£�������һ���ʹ���У�auto_ptr���ٱ��õ�
	 * �������ʹ��boost(tr1)���е�shared_ptr 
	 */
	return EXIT_SUCCESS;
}				// ----------  end of function main  ----------
