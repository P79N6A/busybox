/*
// =====================================================================================
// 
//       Filename:  ring-list.cpp
// 
//       Description:  �����������⣺
//       1������ж�һ�������Ƿ��л�·����Ҫ����0��6���������
//       2������������������жϻ��ĳ��ȣ�
//       3������������������жϱ��ĳ��ȣ�
//       Reference:
//       http://www.360doc.com/content/12/0402/23/9568648_200376434.shtml
//
//       Reference:
//       http://www.360doc.com/content/12/0402/23/9568648_200376434.shtml
// 
//        Version:  1.0
//        Created:  09/27/2012 11:22:26 AM
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
#include <cassert>

struct node
{
	int data;
	struct node *next;
};				// ----------  end of struct node  ----------

/*
// =====================================================================================
//        Class:  List
//  Description:  ��List���������������Ϊ����������ͷ�ڵ㣩������ֻ���𴴽�����������
//  �����Լ���������л�·���жϺ���ؼ��㣬�������⣬��ʵ���κ�����������
// =====================================================================================
*/
class List {
public:
	// ====================  LIFECYCLE     =======================================
	List () :
		m_handle_size(0), 
		m_ring_size(0),
		m_list_head(NULL) {}		// constructor

	// �ͷ����������ڴ�й©
	~List();

	// ====================  INTERFACE     =======================================
	
	/* 
	// ===  FUNCTION  ======================================================================
	//         Name:  CreateList
	//  Description:  ���ݱ��ĳ��Ⱥͻ��ĳ��ȣ���������Ҫ�������
	//   Parameters:  ���ĳ��ȣ�0��ʾ����һ��ѭ������;
	//   		���ĳ��ȣ�0��ʾ����һ���޻�������;
	//  ReturnValue:  �����ɹ�����0�����򷵻�-1
	// =====================================================================================
	*/
	int CreateList(int handle_size, int ring_size);

	/* 
	// ===  FUNCTION  ======================================================================
	//         Name:  CheckRing
	//  Description:  ���ڼ�������Ƿ���ڻ�·
	//   Parameters:  null
	//  ReturnValue:  ����ֵΪNULL��ʾ�޻�·�������ʾ�л�·������ֵ��ֵ��ʾ��������ָ�����
	//  �ϵ�ַ����һ���ǻ�·��㣩�����ֵ�������ں����������⣬û����������
	// =====================================================================================
	*/
	struct node* CheckRing();

	/* 
	// ===  FUNCTION  ======================================================================
	//         Name:  CalculateRingSize
	//  Description:  ���������л��ĳ���
	//   Parameters:  CheckRing()�������ص�ָ�룬ʵ���Ͼ��ǻ���ĳһ��node�ĵ�ַ�����ĸ�node��
	//   ��ַ�㷨������ν���ؼ��������ַ�����ڻ���
	//  ReturnValue:  ���ػ��ĳ��ȣ��������Ӧ����CreateList()�еڶ����������
	// =====================================================================================
	*/
	int CalculateRingSize(struct node *p);


	/* 
	// ===  FUNCTION  ======================================================================
	//         Name:  CalculateHandleSize
	//  Description:  ���������б��ĳ��� 
	//   Parameters:  ChechRing()�������ص�ָ�룬ʵ���Ͼ��ǻ���ĳһ��node�ĵ�ַ�����node��λ
	//   		�ú���Ҫ������������һ����ַ����Ϊ��Ҫ��head����һ���Ĵ�����ϵ�������޷�
	//   		��ȷ����
	//  ReturnValue:  ���ر��ĳ��ȣ��������Ӧ����CreateList()�е�һ��������һ��ȣ���ͷ�ڵ㣩
	// =====================================================================================
	*/
	int CalculateHandleSize(struct node *p);

	// ====================  ACCESSORS     =======================================

	// ====================  MUTATORS      =======================================

	// ====================  OPERATORS     =======================================

protected:
	// ====================  DATA MEMBERS  =======================================

private:
	// ====================  INTERFACE     =======================================
	
	// ====================  DATA MEMBERS  =======================================

	/* 
	// ===  FUNCTION  ======================================================================
	//         Name:  m_CreateList
	//  Description:  ����һ����ѭ������������ͷ�ڵ�ָ��
	//   Parameters:  null
	//  ReturnValue:  �����ɹ�����0�����򷵻�-1
	// =====================================================================================
	*/
	int m_CreateList();

	/* 
	// ===  FUNCTION  ======================================================================
	//         Name:  m_AddNode
	//  Description:  �����������һ���µ�node 
	//   Parameters:  ��Ҫд�����ֵ
	//  ReturnValue:  ��ӳɹ�����0�����򷵻�-1
	// =====================================================================================
	*/
	int m_AddNode(int n);

	int m_handle_size;
	int m_ring_size;
	struct node *m_list_head;

}; // -----  end of class List  -----

List::~List()
{
	struct node *p = m_list_head;
	int n = m_handle_size + m_ring_size + 1;	// ����һ�������ͷ�ڵ�
	// ��������л�����һ��������ͷŷ��������¶δ���
	for (int i=0; i<n; ++i) {
		struct node *tmp = p->next;
		free(p);
		p = tmp;
	}
}

int List::CreateList(int handle_size, int ring_size)
{
	struct node *head = NULL;
	m_handle_size = handle_size;
	m_ring_size = ring_size;

	srand((unsigned)time(0));
	try {
		/* �������� */
		if (m_CreateList() == -1) return -1;
		/* ���컷· */
		for (int i=0; i<ring_size; ++i)
			if (m_AddNode(rand()%100) == -1) return -1;
		struct node *p = m_list_head;
		while (p->next != NULL) p = p->next;
		p->next = m_list_head->next;

		/* ����� */
		for (int i=0; i<handle_size; ++i)
			if (m_AddNode(rand()%100) == -1) return -1;
	} catch (std::bad_alloc &e) {
		std::cout << e.what();
		return -1;
	} catch (std::exception &e) {
		std::cout << e.what();
		return -1;
	}


	return 0;
}		// -----  end of function CreateList  -----

struct node* List::CheckRing()
{
	struct node *slow = m_list_head;
	struct node *fast = m_list_head;

	for ( ; ; ) {
		if (fast == NULL || fast->next == NULL) return NULL;
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast) return slow;
	}

	return NULL;
}		// -----  end of function CheckRing  -----

int List::CalculateRingSize(struct node *p)
{
	if (p == NULL) return 0;

	struct node *slow = p;
	struct node *fast = p;
	int n = 0;
	do {
		/* ���ﲻ���ܳ���fast->NULL����� */
		assert(fast != NULL);
		assert(fast->next != NULL);
		slow = slow->next;
		fast = fast->next->next;
		++n;
	} while (slow != fast);

	return n;
}		// -----  end of function CalculateRingSize  -----

int List::CalculateHandleSize(struct node *p)
{
	if (p == NULL) {
		struct node *p = m_list_head;
		int n = 0;
		while (p != NULL) {
			p = p->next;
			++n;
		}
		return n;
	}

	struct node *slow = p;
	struct node *node = m_list_head;
	int n = 0;
	while (node != slow) {
		/* ���ﲻ���ܳ���node==NULL��slow==NULL����� */
		assert(node != NULL);
		assert(slow != NULL);
		node = node->next;
		slow = slow->next;
		++n;
	}

	return n;
}		// -----  end of function CalculateHandleSize  -----

int List::m_CreateList()
{
	// ͷ�ڵ��data�������ڱ��������нڵ�ĸ���
	m_list_head = (struct node*) malloc(sizeof(struct node));
	if (m_list_head == NULL) throw std::bad_alloc();
	m_list_head->data = 0;
	m_list_head->next = NULL;
	return 0;
}		// -----  end of function m_CreateList  -----

int List::m_AddNode(int n)
{
	if (m_list_head == NULL) return -1;
	struct node *p = (struct node*) malloc(sizeof(struct node));
	if (p == NULL) throw std::bad_alloc();
	p->next = m_list_head->next;
	p->data = n;
	m_list_head->next = p;
	++m_list_head->data;
	return 0;
}		// -----  end of function m_AddNode  -----

/* 
// ===  FUNCTION  ======================================================================
//         Name:  main
//  Description:  test driver
// =====================================================================================
*/

int main(int argc, char *argv[])
{
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " handle-size ring-size" << std::endl;
		exit(EXIT_FAILURE);
	}

	int handle_size = atoi(argv[1]);
	int ring_size = atoi(argv[2]);

	List l;
	l.CreateList(handle_size, ring_size);
	struct node *p = l.CheckRing();
	std::cout << "has ring?\t"<< (p ? "true" : "false") << std::endl;
	std::cout << "handle size: " << l.CalculateHandleSize(p) << std::endl;
	std::cout << "ring size: " << l.CalculateRingSize(p) << std::endl;
	return EXIT_SUCCESS;
}				// ----------  end of function main  ----------
