/*
// =====================================================================================
// 
//       Filename:  k-way-merge.cpp
// 
//    Description:  ��Ŀ����20�����飬ÿ����������500��Ԫ�أ�ÿ��Ԫ��Ϊuint32_t����
//    		�����1W��Ԫ������С��100��
//    		�ⷨ�����͵Ķ�·�鲢�㷨��������ʹ�öѺͰ��������ַ������
//    		ע�⣺���ļ�����ʱ��Ҫʹ��c++0x��׼������Ĭ�ϵ�C++��׼ȱ�ٱ�Ҫ�Ŀ�
// 
//        Version:  1.0
//        Created:  09/28/2012 08:35:20 PM
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
#include <cstdint>
#include <algorithm>
#include <vector>
#include <cassert>

#undef UINT32_MAX
#define UINT32_MAX 100

/*
// =====================================================================================
//        Class:  KWayMerge
//  Description:  ʹ�öѺͰ��������ַ�ʽʵ�ֶ�·�鲢
// =====================================================================================
*/
class KWayMerge {
public:
	// ====================  LIFECYCLE     =======================================
	KWayMerge();				// default constructor
	KWayMerge(int, int, int);		// constructor

	// ====================  INTERFACE     =======================================

	/* 
	// ===  FUNCTION  ======================================================================
	//         Name:  merge_by_heap
	//  Description:  ʹ�öѽ��ж�·�鲢
	// =====================================================================================
	*/
	const std::vector<uint32_t>& merge_by_heap();

	/* 
	// ===  FUNCTION  ======================================================================
	//         Name:  merge_by_tree
	//  Description:  ʹ�ð��������ж�·�鲢
	// =====================================================================================
	*/
	const std::vector<uint32_t>& merge_by_tree();

	// ====================  ACCESSORS     =======================================

	// ====================  MUTATORS      =======================================

	// ====================  OPERATORS     =======================================
	friend std::ostream& operator<<(std::ostream&, const KWayMerge&);

protected:
	// ====================  DATA MEMBERS  =======================================

private:
	// ====================  DATA MEMBERS  =======================================

	/* 
	// ===  FUNCTION  ======================================================================
	//         Name:  build_heap
	//  Description:  ����һ��С���� ������Ӧ���ǳ�ʼ���ѣ����ǽ��ѣ�
	// =====================================================================================
	*/
	void build_heap();

	/* 
	// ===  FUNCTION  ======================================================================
	//         Name:  init_tree
	//  Description:  ��ʼ�������� 
	// =====================================================================================
	*/
	void init_tree();

	/* 
	// ===  FUNCTION  ======================================================================
	//         Name:  compete_once
	//  Description:  ������һ�αȽϣ�ѡ����Сֵ
	// =====================================================================================
	*/
	void compete_once();

	/* cmp��������Ϊ��Ա������������this�ᵼ�²���ƥ��ʧ�� */
	static bool cmp(uint32_t x, uint32_t y) { return x > y; }
	std::vector<uint32_t>::iterator& current(size_t index) { return m_heap[index]; }
	std::vector<uint32_t>::iterator& parent(size_t index) { return m_heap[index/2]; }
	std::vector<uint32_t>::iterator& left(size_t index) { return m_heap[index*2]; }
	std::vector<uint32_t>::iterator& right(size_t index) { return m_heap[index*2+1]; }

	/* ����ʹ������͵���������ڶ�m_tree���в��� */
	int& current(int index) { return m_tree[index]; }
	int& parent(int index) { return m_tree[index/2]; }
	int& left(int index) { return m_tree[index*2]; }
	int& right(int index) { return m_tree[index*2+1]; }

	const uint32_t UINT32_MIN;
	/* ����һ����ά���� */
	size_t m_num_of_array;
	size_t m_num_of_element;
	std::vector< std::vector<uint32_t> > m_source_list;	// ����(> >)�Ŀո��Ǳ���ģ������п��ܵ��±������
	/* ���ڶ�·�鲢�����ݽṹ�����۶ѻ��ǰ�����ʵ���϶�����ȫ�������ṹ */
	std::vector<std::vector<uint32_t>::iterator> m_heap;
	std::vector<int> m_tree;
	/* ����m_heap�б�����Сֵ��0���ĵ���������Ȼ���vector�߼�����const�ģ����ǲ��ܶ����const��������Ϊ��ᵼ�µ��������Ͳ�ƥ�� */
	std::vector<uint32_t> m_guard;	
	/* �洢top n */
	size_t m_num_of_top;
	std::vector<uint32_t> m_dest_list;

};	// -----  end of class KWayMerge  -----

KWayMerge::KWayMerge() : UINT32_MIN(0), m_num_of_array(20), m_num_of_element(500), m_guard(1, 0), m_num_of_top(1000)
{
	srand((unsigned)time(NULL));
	for (size_t i=0; i!=m_num_of_array; ++i) {	// �Ƽ���ѭ����ʹ��source_list.resize(num_of_array)һ����λ������ռ�
		m_source_list.push_back(std::vector<uint32_t>(0));
		for (size_t j=0; j!=m_num_of_element; ++j) {	// �Ƽ���ѭ����ʹ��source_list[i].resize(num_of_element)һ����λ������ռ�
			m_source_list[i].push_back((uint32_t)rand() % UINT32_MAX);	// ǿ������ת�����ȼ�����ģ����
		}
		m_source_list[i].push_back(UINT32_MIN);	// ��ÿ������������һ����Сֵ����Ϊ�ڱ�
		/* ��֤ÿ�������ڲ����� */
		std::sort(m_source_list[i].begin(), m_source_list[i].end(), cmp);
	}
}		// -----  end of function KWayMerge  -----

KWayMerge::KWayMerge(int num_of_array, int num_of_element, int num_of_top) : UINT32_MIN(0), m_guard(1, 0)
{
	m_num_of_array = num_of_array;
	m_num_of_element = num_of_element;
	m_num_of_top = num_of_top;

	srand((unsigned)time(NULL));
	for (size_t i=0; i!=m_num_of_array; ++i) {	// �Ƽ���ѭ����ʹ��source_list.resize(num_of_array)һ����λ������ռ�
		m_source_list.push_back(std::vector<uint32_t>(0));
		for (size_t j=0; j!=m_num_of_element; ++j) {	// �Ƽ���ѭ����ʹ��source_list[i].resize(num_of_element)һ����λ������ռ�
			m_source_list[i].push_back((uint32_t) rand() % UINT32_MAX);	// ǿ������ת�����ȼ�����ģ����
		}
		m_source_list[i].push_back(UINT32_MIN);	// ��ÿ������������һ����Сֵ����Ϊ�ڱ�
		/* ��֤ÿ�������ڲ����� */
		std::sort(m_source_list[i].begin(), m_source_list[i].end(), cmp);
	}
}		// -----  end of function KWayMerge  -----

const std::vector<uint32_t>& KWayMerge::merge_by_heap()
{
	/* 
	 * ˵����
	 * 	��Ȼ����������ʹ����һЩС���ɣ������ڱ�֮�࣬��Ŀ�Ľ�����Ϊ�˼򻯱�̣�û�и�����㷨����
	 * 	ʹ�öѽ��ж�·�鲢�ĺ���˼�����ʹ�öѿ�����logn�ĸ��Ӷ��ڣ��ҵ�������е����ֵ
	 * 	���ʹ�ã�ʹ�öѽ��ж�·�鲢�ĸ��Ӷ�Ϊk*logn��kΪ��ĿҪ���top������nΪ�鲢��·����2
	 *
	 * �ر�ע�⣺
	 * 	����n��nΪ��������Ҷ�ӽڵ����ȫ�������������ֽ�����һ��������Ҷ�ڵ�Ϊ��ڵ���������һ��
	 * 	������Ҷ�ڵ�Ϊ�ҽڵ�����������ʹ�õ��ǵڶ���������������ѽ���Ϊ�˷�����
	 */

	/* ��ʼ���ѣ�����Ҷ�ӽڵ㸳ֵ����Ҫע�⣬���д�ŵ��Ǹ���vector�ĵ����� */
	/* ���ǹ������ȫ����������Ҷ�ӽڵ���� = Ҷ�ӽڵ���� - 1 */
	m_heap.resize(m_num_of_array, m_guard.begin());	// indexΪ0��Ԫ�ؽ���ռλ������
	for (size_t i=0; i!=m_num_of_array; ++i) m_heap.push_back(m_source_list[i].begin());

	for (size_t i=0; i!=m_num_of_top; ++i) {
#ifdef DEBUG
		for (size_t i=0; i!=m_heap.size(); ++i)	std::cout << *m_heap[i] << ' '; std::cout << std::endl;
#endif
		build_heap();	// ʹ�öѵķ�����ѡ���ֵ
#ifdef DEBUG
		for (size_t i=0; i!=m_heap.size(); ++i)	std::cout << *m_heap[i] << ' '; std::cout << std::endl;
#endif
		m_dest_list.push_back(*m_heap[1]);	// ����ֵ�洢�����������
		if (*m_heap[1] != UINT32_MIN) ++m_heap[1];	// ����������ָ��ֵΪ��Сֵʱ�������������ƶ�����ֹԽ��
#ifdef DEBUG
		for (size_t i=0; i!=m_heap.size(); ++i)	std::cout << *m_heap[i] << ' '; std::cout << std::endl; std::cout << std::endl;
#endif
	}
	return m_dest_list;
	/* 
	 * �ٴ��Ķ���������ۣ�
	 * build_heapʵ����Ϊ��ʼ���ѵĹ��̣������ǽ��ѵĹ���
	 * ���ڳ�ʼ����һ��֮�󣬺���ѡ����ֵ�Ĺ���ֻҪ����һ��·�����ɣ������ע�����ڵ�
	 * ���Ըú�����Ȼ��ȷ�����ҿ���ȥ�����࣬��ʵ����Ч���Ƿǳ�����
	 */
}		// -----  end of function merge_by_heap  -----

const std::vector<uint32_t>& KWayMerge::merge_by_tree()
{
	/* 
	 * ˵����
	 * 	��������ʵ����ѵ�ʵ�ֹ���һ�����ݽṹ
	 * 	������������ȫ�������ķ�ʽ�ڶ���ȫһ�������߽ṹ����ȫһ�������Ǳ��������ȴ����ͬ
	 * 	��ÿ���ڵ����guard����ʵ�ʵ���ֵ�������������нڵ㱣��������ݵ��±꣬���������ݵ�ֵ
	 * 	���������ܱ�����ֵ��ԭ��Ϊ�ҵ����յ�ʤ��֮���޷�����ʤ�ߵ���ֵ�ҵ�ʤ�ߵ�λ�ã�������һ�β���
	 */

	/* 
	 * ע�⣺
	 * 	�����������ڶ԰�������ʵ�ֲ���������
	 * 	���Ե�ǰ�㷨����ʵ���ԣ�Ӳ���룬ֻ����8��Ҷ�ӽڵ�����
	 * 	�ο����ӣ�http://sandbox.mc.edu/~bennet/cs402/lec/llout/wrap000.html
	 */
	assert(m_source_list.size() == 8);
	m_tree.resize(m_num_of_array, 0);	// indexΪ0��Ԫ�ؽ���ռλ������
	for (size_t i=0; i!=m_num_of_array; ++i) m_tree.push_back((int)i);
#ifdef DEBUG
	for (size_t i=0; i!=m_tree.size(); ++i)	std::cout << m_tree[i] << ' '; std::cout << std::endl;
#endif
	init_tree();
#ifdef DEBUG
	for (size_t i=0; i!=m_tree.size(); ++i)	std::cout << m_tree[i] << ' '; std::cout << std::endl;
#endif
	for (int i=0; i<13; ++i) {
		compete_once();
		m_dest_list.push_back(m_source_list[m_tree[0]][0]);
		if (m_source_list[m_tree[0]].size() == 1) {
			m_source_list[m_tree[0]][0] = 1024;
		} else {
			m_source_list[m_tree[0]].erase(m_source_list[m_tree[0]].begin());
		}
	}

	return m_dest_list;
}		// -----  end of function merge_by_tree  -----

void KWayMerge::build_heap()
{
	/* 
	 * ˵����
	 * 	��Ԫ���ƶ�ʱ����������Ԫ�رȽϣ�һ��һ�ӣ���Ҳ��������Ԫ�رȽϣ�һ�����ӣ�
	 * 	��������Ԫ�رȽϣ�������Ч�ļ��ٲ���Ҫ��Ԫ���ƶ���������������ʹ������Ԫ�رȽϵķ���
	 * 	�ڽ��ѵĹ����У�����ʼ�ձ���jΪĳ�����������ӣ�j��Ϊż�����������ȽϷ������
	 */

	/* �����±�Ϊ0����Ԫ�ز����뽨�ѣ���Ч�±��1��ʼ */
	/* �����Һ��ӽڵ�͸��ڵ���ȡ���ֵ���ڸ��ڵ��ϣ���ʡ����Ҫ��Ԫ���ƶ� */
	size_t i=m_heap.size()/2+1;
	i += i % i;	// �����һ��Ҷ�ӽڵ�Ϊ�����ҽڵ�����
	/* �˴�iһ��Ϊ��ڵ㣨ż���������п��ܲ��ǵ�һ��Ҷ�ӽڵ㣬�������һ����Ҷ�ӽڵ� */
	for (; i<m_heap.size(); i+=2) {
		size_t j = i;
		while (j != 1) {	// �����ڵ��˳��ж�
			j -= j % 2;	// ��֤��ǰ�ڵ�һ������ڵ㣨ż����
			/* ���д洢��ֻ�ǵ���������Ҫ�����û��ֵ */
			size_t bigger = *current(j) > *current(j+1) ? j : j+1;
			if (*parent(bigger) < *current(bigger)) {	// �����ֵ�ƶ������ڵ�
				std::vector<uint32_t>::iterator tmp = parent(bigger);
				parent(bigger) = current(bigger);
				current(bigger) = tmp;
			}
			j /= 2;		// ����ǰ�ڵ��ƶ������ڵ�
		}
	}
	/* 
	 * �ٴ��Ķ�������ĵã�
	 * ����ָ��һ�����󣬸ú���Ӧ�ý���init_heap��������build_heap��ԭ����merge_by_heap����˵��
	 * ���⣬�������ֳ�ʼ���ѵķ�ʽ������ʵ����ʤ�������ʼ���ѣ��򽨶ѣ��Ĺ��̷ǳ�����
	 * Ψһ��������ǣ����ڱȽ�֮������swap��������ʤ������ֱ�����ӽڵ�����ڵ㸳ֵ
	 * �������⣬����Ĳ�������һ����
	 */
}		// -----  end of function build_heap  -----

void KWayMerge::init_tree()
{
	/* 
	 * ��������˼·��������⣬����ʹ�ð��������ѵ�֮һ������ι���һ��������������γ�ʼ�����еĽڵ㣬һ�����������
	 * �����Լ��ķ������ȹ���ʤ������Ȼ����ʤ�����Ļ���֮�ϣ��ٹ����������������ӵ���ɰ������Ĺ������
	 * ��������������Ŀǰ���߻�û�вο������˵Ĵ��룬�����ʲô���õķ��������߻���ע�͵���ʽ�ڴ������������������ԶԱ�
	 */
	m_source_list[0][0] = 87;	m_source_list[0][1] = 99;	m_source_list[0][2] = 104;	m_source_list[0][3] = 119;	m_source_list[0][4] = 1024;
	m_source_list[1][0] = 48;	m_source_list[1][1] = 56;	m_source_list[1][2] = 88;	m_source_list[1][3] = 97;       m_source_list[1][4] = 1024;
	m_source_list[2][0] = 98;	m_source_list[2][1] = 104;	m_source_list[2][2] = 128;	m_source_list[2][3] = 151;      m_source_list[2][4] = 1024;
	m_source_list[3][0] = 58;	m_source_list[3][1] = 70;	m_source_list[3][2] = 76;	m_source_list[3][3] = 100;      m_source_list[3][4] = 1024;
	m_source_list[4][0] = 33;	m_source_list[4][1] = 91;	m_source_list[4][2] = 156;	m_source_list[4][3] = 205;      m_source_list[4][4] = 1024;
	m_source_list[5][0] = 48;	m_source_list[5][1] = 55;	m_source_list[5][2] = 60;	m_source_list[5][3] = 68;       m_source_list[5][4] = 1024;
	m_source_list[6][0] = 44;	m_source_list[6][1] = 55;	m_source_list[6][2] = 66;	m_source_list[6][3] = 77;       m_source_list[6][4] = 1024;
	m_source_list[7][0] = 80;	m_source_list[7][1] = 96;	m_source_list[7][2] = 106;	m_source_list[7][3] = 113;      m_source_list[7][4] = 1024;

	/* ����ʤ���� */
	/* ע�⣺���������int���������غ����ĵ��û������ */
	for (int i=15; i>1; i-=2) {
		if (m_source_list[m_tree[i-1]][0] < m_source_list[m_tree[i]][0])
			parent(i) = m_tree[i-1];
		else
			parent(i) = m_tree[i];
	}

#ifdef DEBUG
	for (size_t i=0; i!=m_tree.size(); ++i)	std::cout << m_tree[i] << ' '; std::cout << std::endl;
#endif
	/* ��ʤ�����Ļ����ϣ����������� */
	m_tree[0] = m_tree[1];	// ������ʤ�߷ŵ���λ��
	for (int i=1; i<8; ++i) {
		if (m_source_list[left(i)][0] > m_source_list[right(i)][0])
			current(i) = left(i);
		else
			current(i) = right(i);
	}
#ifdef DEBUG
	for (size_t i=0; i!=m_tree.size(); ++i)	std::cout << m_tree[i] << ' '; std::cout << std::endl;
#endif

	return;
}		// -----  end of function init_tree  -----

void KWayMerge::compete_once()
{
	int condidate = 0; 	// ���ڼ�¼��ǰ�ȽϵĽڵ�
	int loser = 0;		// �ϴαȽϵİ��ߣ�������condidate���бȽ�

	/* ������Ҫʱ��ע��һ�㣺condidate��m_source_list���±꣬��loser��m_tree���±� */
	condidate = m_tree[0];		// ��λ��ʼ��Ҷ�ӽڵ�
	loser = (8 + m_tree[0]) / 2;	// ��λ��һ��loser

	while (loser > 0) {
		while (loser > 0 && m_source_list[condidate][0] < m_source_list[current(loser)][0]) 
			loser /= 2;
		if (loser > 0) {
			int temp = condidate;
			condidate = current(loser);
			current(loser) = temp;
			loser /= 2;
		}
	}
	m_tree[0] = condidate;

	return;
}		// -----  end of function compete_once  -----

std::ostream& operator<<(std::ostream &out, const KWayMerge &obj)
{
	out << "num_of_array: " << obj.m_num_of_array << "\t\t";
	out << "num_of_element: " << obj.m_num_of_element << "\t\t";
	out << "num_of_top: " << obj.m_num_of_top << std::endl;
	for (size_t i=0; i!=obj.m_source_list.size(); ++i) {
		for (size_t j=0; j!=obj.m_source_list[i].size(); ++j) {
			out << obj.m_source_list[i][j] << '\t';
		}
		out << std::endl;
	}
	return out;
}		// -----  end of function operator<<  -----

/* 
// ===  FUNCTION  ======================================================================
//         Name:  main
//  Description:  test driver
// =====================================================================================
*/
int main(int argc, char *argv[])
{
	KWayMerge obj1(8, 10, 10);
	KWayMerge obj2(8, 4, 10);
	std::vector<uint32_t> result;

#ifdef DEBUG
	std::cout << obj1;
	std::cout << "----------------------------------------------------------------" << std::endl;
	std::cout << obj2;
	std::cout << std::endl;
#endif

	//	result = obj1.merge_by_heap();
	//	std::cout << "result by heap:" << std::endl;
	//	for (size_t i=0; i!=result.size(); ++i)
	//		std::cout << result[i] << '\t';
	//	std::cout << std::endl;

	result = obj2.merge_by_tree();
	std::cout << "result by tree:" << std::endl;
	for (size_t i=0; i!=result.size(); ++i)
		std::cout << result[i] << '\t';
	std::cout << std::endl;
	return EXIT_SUCCESS;
}				// ----------  end of function main  ----------
