/*
// =====================================================================================
// 
//       Filename:  has_ptr.cpp
// 
//    Description:  �������漰�κ�����ָ���������������Ϊ��˵����ָͨ����ڵ�����
// 
//        Version:  1.0
//        Created:  10/09/2012 11:25:30 AM
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

/*
// =====================================================================================
//        Class:  Has_Ptr
//  Description:  һ���򵥵��࣬����չʾ��ָͨ����ڵ�����
// =====================================================================================
*/
class Has_Ptr {
public:
	// ====================  LIFECYCLE     =======================================
	Has_Ptr(int *p, int i) : ptr(p), val(i) {}	// constructor

	// ====================  ACCESSORS     =======================================
	int* get_ptr() const { return ptr; }
	int get_int() const { return val; }

	void set_ptr(int *p) { ptr = p; }
	void set_int(int i) { val = i; }

	int get_ptr_val() const { return *ptr; }
	void set_ptr_val(int val) const { *ptr = val;}	// ������Ȼ��const������������Ȼ�������޸�ָ����ָ���ֵ

private:
	// ====================  DATA MEMBERS  =======================================
	int *ptr;
	int val;

};	// -----  end of class Has_Ptr  -----


/* 
// ===  FUNCTION  ======================================================================
//         Name:  main
//  Description:  test driver
// =====================================================================================
*/
int main(int argc, char *argv[])
{
	int obj = 0;
	Has_Ptr ptr1(&obj, 42);
	Has_Ptr ptr2(ptr1);	// �������Զ�����һ��Ĭ�Ͽ������캯����ǳ������
	/* ����֮��ptr1��ptr2�е�ָ��ָ��ͬһ�����������������intֵ��ͬ
	 * ��������ǳ������ԭ�����������intֵ�Ƕ����ģ���ָ���������һ��*/

	/* ����ָ���Ա��ʹ��Ĭ�Ͽ������캯�����࣬���в�ָͬ�������ȱ��
	 * �����ǣ��౾���޷���������ָ��*/

	/* -------------------------------------------------------------- */

	ptr1.set_int(4);
	std::cout << ptr1.get_int() << std::endl;
	std::cout << ptr2.get_int() << std::endl;

	ptr1.set_ptr_val(5);
	std::cout << ptr1.get_ptr_val() << std::endl;
	std::cout << ptr2.get_ptr_val() << std::endl;
	/* ����ֵ�޸ģ������������໥������
	 * ���ǣ���ͼʹ��ָ���޸�ֵ�����ᵼ�´���һ��ָ��ĸ�ֵ������������һ�������ֵҲ���Ÿı�*/

	/* -------------------------------------------------------------- */
	int *ip = new int(42);
	Has_Ptr ptr(ip, 10);
	delete ip;
	ptr.set_ptr_val(0);	// ��ʱָ����ָ��ĵ�ַ�Ѿ������٣���ʹ���ܲ���������������ʱ����
	std::cout << ptr.get_ptr_val() << std::endl;
	/* ��������ʱ��ptr�����е�ָ����ipָ��ͬһ����ַ�ռ䣬���ǵ�ip�ͷ�ʱ��ptr�޷���֪��ַ�Ѿ�ʧЧ���������ָ������� */

	return EXIT_SUCCESS;
}				// ----------  end of function main  ----------
