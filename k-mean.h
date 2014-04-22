//k-mean.h
#ifndef KMEAN_HEAD
#define KMEAN_HEAD

#include <vector>
#include <map>
#include <string>
#include "node.h"

double Kdistance(const OBJ &first, const OBJ &second);//��ȡ������֮��ľ���

class KMean
{
public:
    KMean(uint nClusterNum, const std::vector<OBJ> *pVector);
	void Start(double TermDistance);//����k��ֵ�㷨
private:
	/*�����ݳ�Ա����*/
	uint nClusterNum;//���ɵĴص�������
	const std:: vector<OBJ> *pAllObj;//���еĶ���
	VEC_CLUSTER Cluster;//��
	OBJ_MAP ClusterMap;//�غͶ���֮���ӳ��
	std::vector<OBJ> MeanObj;//��ֵ���������

	/*�෽������*/
	uint GetMinDis(uint i);//��ȡĳ�������Ǹ����ĵ��������
	void Init();//��ʼ�������������漴���ɴ���㣩
	void AssignObj();//�����е���䵽��ͬ�Ĵ���
	void GetMean(uint cluster_index, OBJ &AverNode);

	void OutputData(const std::string fileName);//���������

};
#endif // KMEAN_HEAD