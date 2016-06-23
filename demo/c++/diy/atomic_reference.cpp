/*
// =====================================================================================
// 
//       Filename:  atomic_reference.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/23/2016 11:05:22 AM
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
#include <string>
#include <thread>
#include <mutex>

// =====================================================================================
//        Class:  AtomicReferencePtr
//  Description:  
// =====================================================================================

template <typename T>
class AtomicReferencePtr
{
public:
	// ====================  LIFECYCLE     =======================================
	AtomicReferencePtr() = default;

	AtomicReferencePtr(const AtomicReferencePtr &obj)
	{
		std::lock_guard<std::mutex> guard(_lock);
		_pptr = obj._pptr;
	}


	AtomicReferencePtr(T *ptr) : _pptr(new std::shared_ptr<T>(ptr))
	{
	}

	~AtomicReferencePtr()
	{
	}

	// ====================  INTERFACE     =======================================

	// ====================  OPERATORS     =======================================
	AtomicReferencePtr& operator=(const AtomicReferencePtr &obj)
	{
		std::lock_guard<std::mutex> guard(_lock);
		_pptr = obj._pptr;
		return *this;
	}

	AtomicReferencePtr& operator=(T *ptr)
	{
		std::lock_guard<std::mutex> guard(_lock);
		*_pptr.get() = std::shared_ptr<T>(ptr);
		return *this;
	}

	std::shared_ptr<T> operator->()
	{
		std::lock_guard<std::mutex> guard(_lock);
		std::shared_ptr<T> tmp = *_pptr;
		return tmp;
	}

//	std::shared_ptr<T> operator*() {return *_pptr;}

private:
public:
	// ==================== PRIVATE METHOD =======================================

	// ====================  DATA MEMBERS  =======================================
	std::shared_ptr<std::shared_ptr<T>> _pptr;
	std::mutex _lock;
};		// -----  end of template class AtomicReferencePtr  -----

/* 
// ===  FUNCTION  ======================================================================
//         Name:  main
//  Description:  
// =====================================================================================
*/
int main(int argc, char *argv[])
{
	std::shared_ptr<std::shared_ptr<int>> p(new std::shared_ptr<int>(new int(3)));

	std::cout << **p << std::endl;

	AtomicReferencePtr<std::string> s1(new std::string("abc"));
	AtomicReferencePtr<std::string> s2 = s1;

	std::cout << s1->c_str() << std::endl;
	std::cout << s2->c_str() << std::endl;

	s1 = new std::string("bcd");

	std::cout << s1->c_str() << std::endl;
	std::cout << s2->c_str() << std::endl;

	std::cout << "Hello World" << std::endl;
	return EXIT_SUCCESS;
}				// ----------  end of function main  ----------
