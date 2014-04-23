#include "k-mean.h"
#include "node.h"
#include <vector>
#include <map>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <cassert>
#include <fstream>
#include <ios>
using namespace std;


/*
 *K-Means ���캯��
 */
KMean:: KMean(uint nClusterNum, const vector<OBJ> *pVector)
	:pAllObj(pVector), nClusterNum(nClusterNum)
{
		Cluster.resize(nClusterNum);//��resize��������
		Init();
}

/*
 *�����ݵ������ѡȡcluster_num���㣬����ʼ������ؽṹ
 */
void KMean::Init()
{
	vector <uint> TempRand;
	for(uint i = 0; i < pAllObj->size(); ++i){
		TempRand.push_back(i);
	}
	random_shuffle(TempRand.begin(), TempRand.end());

	//TempRand����ȥnclusterNum��
	//��TempRand�ŵ���ʼ�������У��������������㷨�������randomֵ
	for(uint i = 0; i < nClusterNum; ++i){
		MeanObj.push_back(pAllObj->at(TempRand[i]));
	}

	//�������ɵ�mean_obj�㣬�����е�������鵽���ԵĴ���
	//�ĳ�AssignObj
	AssignObj();
}

	//template <typename X>struct{};

/*
 *��ȡ��ĳ������������ĵ���±ꡣ
 *������
 *i:���ID��
 * ����ֵ��
 * ���ĵ���±꣨�� mean_nodes�е��±�)
 */
	//ʹ��min_elem,�º�������ȽϺ�����

template<typename T>
class MyCompare
{
private:
	const OBJ &mean;
public: 
	MyCompare(const OBJ &meanNode) : mean(meanNode) 
	{
	}

	bool operator()(const T &x, const T &y){
		if(Kdistance(x , mean) < Kdistance(y , mean)){
			return true;
		}
		else{
			return false;
		}
	}
};


uint  KMean::GetMinDis(uint i){
	/*
	double min_kdistance = -1;
	uint index = 0 ;
	
	for(uint  j = 0; j < MeanObj.size();  ++j)
	{
		double dis = Kdistance(pAllObj->at(i), MeanObj.at(j));
		if(min_kdistance == -1 || dis< min_kdistance)
		{
			min_kdistance = dis;
			index = j;
		}
	}
	}*/
	MyCompare < OBJ > myCompare( pAllObj->at(i) );

	vector <OBJ> :: iterator pos = min_element(MeanObj.begin() , MeanObj.end(), myCompare);


	return pos - MeanObj.begin();
}

/*
  ��ʼ���ص�ʱ�򣬽����е��������Ӧ�Ĵ���
 */
void KMean::AssignObj()
{
	//������е�clusters
	for(uint i = 0; i < Cluster.size(); ++i){
		Cluster[i].clear();
	}

	//����Ҫ��Ϊ�Ż������������æ�Ż�
	for(uint i = 0 ; i < pAllObj->size(); ++i){
		uint index = GetMinDis(i);
		Cluster[index].push_back(i);
		ClusterMap[i] = index;
	}
}


/*
 *����������֮��ľ��루����ŷ���������)
 *������
 *first: Node��
 *second: Node��
 *����ֵ��
 *double ���� ����
 */
double Kdistance(const OBJ &first, const OBJ &second)
{
	double distance = 0;

	for(uint i = 0; i < first.attrs.size(); ++i){
		//����pow��ֱ�����
		distance += (first.attrs[i] - second.attrs[i]) * (first.attrs[i] - second.attrs[i]);
	}
	//distance = sqrt(distance);
	return distance;
}

/*
 *����ȷ����������ĵ㣨����㣩
 *������
 *cluster_index:��ص��±�
 */
//���ô��Σ���Ҫ�����Զ�������ʵ��
void KMean::GetMean(uint cluster_index, OBJ &AverNode)
{	
	//��ʼ����ʱOBJ
	AverNode.attrs.resize(pAllObj->at(0).attrs.size());

	//ά��
	for(uint i = 0; i < pAllObj->at(0).attrs.size(); ++i){
		DATA_TYPE sum = 0;
		//���нڵ�
		for( uint j = 0; j < Cluster[cluster_index].size(); ++j)
		{
			sum += pAllObj->at(Cluster[cluster_index][j]).attrs[i]; 
		}
		//���ά���µ�ƽ����
		AverNode.attrs[i] = (DATA_TYPE)sum / (DATA_TYPE)Cluster[cluster_index].size();
	}
}


void KMean::Start(double TermDistance)
{
	while(true){
		double sum = 0;
		for(uint i = 0; i < Cluster.size(); ++i)
		{
			OBJ NewObj;
			GetMean(i, NewObj);
			sum += Kdistance(NewObj, MeanObj[i]);
			MeanObj[i] = NewObj;
		}
		cout << "���ξ��������С��"<<sum<<endl;
		if(sum <= TermDistance){
			string fileName("out.txt");
			OutputData(fileName);
			return;
		}
		AssignObj();
	}
}

void KMean::OutputData(const std::string fileName){
	ofstream out(fileName.c_str());
	if(!out.is_open()){
		exit(-1);
	}
	for(uint i = 0 ; i < Cluster.size(); ++i){
		out <<"cluster"<< i << endl;
		for(uint j = 0; j < Cluster[i].size(); ++j){
			for(uint k = 0; k < pAllObj->at(0).attrs.size(); ++k){
				out << pAllObj->at(Cluster[i][j]).attrs[k] << "  ";
			}
			out << endl;
		}
	}
	out.close();
}