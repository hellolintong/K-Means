#ifndef NODE_HEAD
#define NODE_HEAD
#include <vector>
#include <map>

//OBJECT���������
typedef double DATA_TYPE ;
typedef unsigned int uint;


//����node
typedef struct OBJ{
	std::vector<DATA_TYPE> attrs;
}OBJ;

//һ���ذ���object���±�
typedef std::vector<uint> CLUSTER;

//����Ľṹ��
typedef std::vector<CLUSTER>  VEC_CLUSTER;;

//object��cluster��ӳ��
//keyΪobject�±ꡣvalueΪcluster�±�
typedef std::map<uint, uint> OBJ_MAP;

//node �ȽϺ�����first == second ���� 0, first > second.����1�� first < second.����-1
// �����֮��ıȽϣ����������ϵĴ��ۣ�
//int MyCompare(const Node &first, const Node &second);

#endif