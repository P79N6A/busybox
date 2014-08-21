/*
// =====================================================================================
// 
//       Filename:  has_ptr.cpp
// 
//    Description:  ʹ�����ü����ķ�ʽʵ������ָ�룬����ָ�������ֶ�����
// 
//        Version:  1.0
//        Created:  10/10/2012 10:10:45 AM
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
//        Class:  U_Ptr
//  Description:  
// =====================================================================================
*/
class U_Ptr {
public:
	// ====================  LIFECYCLE     =======================================
	U_Ptr(int *p) : ip(p), use(1) {}	// constructor
	~U_Ptr() { delete ip; }

private:
	// ====================  DATA MEMBERS  =======================================
	friend class Has_Ptr;	// ��Ԫ����Ҫ��ǰ����������ֱ��ʹ������
	int *ip;
	size_t use;

};	// -----  end of class U_Ptr  -----

/*
// =====================================================================================
//        Class:  Has_Ptr
//  Description:  ͨ��U_Ptr��ĸ�����ʵ������ָ��
// =====================================================================================
*/
class Has_Ptr {
public:
	// ====================  LIFECYCLE     =======================================
	Has_Ptr(int *p, int i) : ptr(new U_Ptr(p)), val(i) {}	// constructor
	Has_Ptr(const Has_Ptr &orig) : 
		ptr(orig.ptr), val(orig.val) { ++ptr->use; }
	~Has_Ptr() { if (--ptr->use == 0) delete ptr; }

	// ====================  ACCESSORS     =======================================
	int *get_ptr() const { return ptr->ip; }
	int get_int() const { return val; }

	void set_ptr(int *p) { ptr->ip = p; }
	void set_int(int i) { val = i; }

	int get_ptr_val() const { return *ptr->ip; }
	void set_ptr_val(int i) { *ptr->ip = i; }
	
	size_t get_use() { return ptr->use; };	// �鿴���ü�����

	// ====================  OPERATORS     =======================================
	Has_Ptr& operator=(const Has_Ptr&);

private:
	// ====================  DATA MEMBERS  =======================================
	U_Ptr *ptr;
	int val;

};	// -----  end of class Has_Ptr  -----

Has_Ptr& Has_Ptr::operator=(const Has_Ptr &rhs)
{
	++rhs.ptr->use;
	if (--ptr->use == 0) delete ptr;	// ��ֵ��Ҫ�����ͷ�
	ptr = rhs.ptr;
	val = rhs.val;
	return *this;
}		// -----  end of function operator=  -----

/* 
// ===  FUNCTION  ======================================================================
//         Name:  main
//  Description:  test driver
// =====================================================================================
*/
int main(int argc, char *argv[])
{
	int *p = new int(42);
	Has_Ptr obj(p, 10);	// obj�Լ���valΪ10��ָ��ָ��Ŀռ�Ϊ42
	std::cout << obj.get_int() << ',' << obj.get_ptr_val() << ',' << obj.get_use() << std::endl;
	std::cout << std::endl;

	Has_Ptr obj2(obj);	// obj2����obj
	std::cout << obj.get_int() << ',' << obj.get_ptr_val() << ',' << obj.get_use() << std::endl;
	std::cout << obj2.get_int() << ',' << obj2.get_ptr_val() << ',' << obj2.get_use() << std::endl;
	std::cout << std::endl;

	Has_Ptr obj3 = obj;	// obj3����obj
	std::cout << obj.get_int() << ',' << obj.get_ptr_val() << ',' << obj.get_use() << std::endl;
	std::cout << obj2.get_int() << ',' << obj2.get_ptr_val() << ',' << obj2.get_use() << std::endl;
	std::cout << obj3.get_int() << ',' << obj3.get_ptr_val() << ',' << obj3.get_use() << std::endl;
	std::cout << std::endl;

	/* ������δ��뽫����p��ָ��ĵ�ַ�ظ��ͷ� */
	Has_Ptr obj4(p, 4);	// obj�Լ���valΪ10��ָ��ָ��Ŀռ�Ϊ42
	std::cout << obj4.get_int() << ',' << obj4.get_ptr_val() << ',' << obj4.get_use() << std::endl;
	std::cout << std::endl;

	return EXIT_SUCCESS;
}				// ----------  end of function main  ----------

