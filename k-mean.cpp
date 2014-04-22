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
 *K-Means 构造函数
 */
KMean:: KMean(uint nClusterNum, const vector<OBJ> *pVector)
	:pAllObj(pVector), nClusterNum(nClusterNum)
{
		Cluster.resize(nClusterNum);//用resize扩充容量
		Init();
}

/*
 *从数据点中随机选取cluster_num个点，并初始化簇相关结构
 */
void KMean::Init()
{
	vector <uint> TempRand;
	for(uint i = 0; i < pAllObj->size(); ++i){
		TempRand.push_back(i);
	}
	random_shuffle(TempRand.begin(), TempRand.end());

	//TempRand里面去nclusterNum个
	//将TempRand放到初始化函数中，便于重新启动算法，并添加random值
	for(uint i = 0; i < nClusterNum; ++i){
		MeanObj.push_back(pAllObj->at(TempRand[i]));
	}

	//根据生成的mean_obj点，将所有的其他点归到各自的簇中
	//改成AssignObj
	AssignObj();
}

	//template <typename X>struct{};

/*
 *获取离某个点最近的中心点的下标。
 *参数：
 *i:点的ID。
 * 返回值：
 * 中心点的下标（在 mean_nodes中的下标)
 */
	//使用min_elem,仿函数构造比较函数。

template<typename T>
class MyCompare
{
private:
	OBJ mean;
public: 
	MyCompare(const OBJ &meanNode){
		mean = meanNode;
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
	vector <OBJ> :: iterator pos ;
	MyCompare < OBJ > myCompare( pAllObj->at(i) );

	pos = min_element(MeanObj.begin() , MeanObj.end(), myCompare);


	return pos - MeanObj.begin();
}

/*
  初始化簇的时候，将所有点放置于相应的簇中
 */
void KMean::AssignObj()
{
	//清空所有的clusters
	for(uint i = 0; i < Cluster.size(); ++i){
		Cluster[i].clear();
	}

	//不需要人为优化，编译器会帮忙优化
	for(uint i = 0 ; i < pAllObj->size(); ++i){
		uint index = GetMinDis(i);
		Cluster[index].push_back(i);
		ClusterMap[i] = index;
	}
}


/*
 *计算两个点之间的距离（采用欧拉距离计算)
 *参数：
 *first: Node点
 *second: Node点
 *返回值：
 *double 类型 距离
 */
double Kdistance(const OBJ &first, const OBJ &second)
{
	double distance = 0;

	for(uint i = 0; i < first.attrs.size(); ++i){
		//不用pow。直接相乘
		distance += (first.attrs[i] - second.attrs[i]) * (first.attrs[i] - second.attrs[i]);
	}
	distance = sqrt(distance);
	return distance;
}

/*
 *重新确定聚类的中心点（虚拟点）
 *参数：
 *cluster_index:类簇的下标
 */
//引用传参，不要返回自定义类型实体
void KMean::GetMean(uint cluster_index, OBJ &AverNode)
{	
	//初始化临时OBJ
	AverNode.attrs.resize(pAllObj->at(0).attrs.size());

	//维度
	for(uint i = 0; i < pAllObj->at(0).attrs.size(); ++i){
		DATA_TYPE sum = 0;
		//所有节点
		for( uint j = 0; j < Cluster[cluster_index].size(); ++j)
		{
			sum += pAllObj->at(Cluster[cluster_index][j]).attrs[i]; 
		}
		//求该维度下的平均数
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
		cout << "本次聚类距离缩小："<<sum<<endl;
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