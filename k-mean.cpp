#include <vector>
#include <map>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <ios>
#include "k-mean.h"
#include "node.h"
using namespace std;

KMean:: KMean(uint nClusterNum, const vector<OBJ> *pVector)
	:pAllObj(pVector), nClusterNum(nClusterNum)
{
		Cluster.resize(nClusterNum);
		Init();
}

void KMean::Init()
{
	vector <uint> TempRand;
	for(uint i = 0; i < pAllObj->size(); ++i){
		TempRand.push_back(i);
	}
	random_shuffle(TempRand.begin(), TempRand.end());

	for(uint i = 0; i < nClusterNum; ++i){
		MeanObj.push_back(pAllObj->at(TempRand[i]));
	}
	AssignObj();
}

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
	MyCompare < OBJ > myCompare( pAllObj->at(i) );
	vector <OBJ> :: iterator pos = min_element(MeanObj.begin() , MeanObj.end(), myCompare);
	return pos - MeanObj.begin();
}

void KMean::AssignObj()
{
	for(uint i = 0; i < Cluster.size(); ++i){
		Cluster[i].clear();
	}

	for(uint i = 0 ; i < pAllObj->size(); ++i){
		uint index = GetMinDis(i);
		Cluster[index].push_back(i);
		ClusterMap[i] = index;
	}
}

double Kdistance(const OBJ &first, const OBJ &second)
{
	double distance = 0;

	for(uint i = 0; i < first.attrs.size(); ++i){
		distance += (first.attrs[i] - second.attrs[i]) * (first.attrs[i] - second.attrs[i]);
	}
	return distance;
}

void KMean::GetMean(uint cluster_index, OBJ &AverNode)
{	
	AverNode.attrs.resize(pAllObj->at(0).attrs.size());

	for(uint i = 0; i < pAllObj->at(0).attrs.size(); ++i){
		DATA_TYPE sum = 0;
		for( uint j = 0; j < Cluster[cluster_index].size(); ++j)
		{
			sum += pAllObj->at(Cluster[cluster_index][j]).attrs[i]; 
		}
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
		cout << "this cluster process narrow distance:"<<sum<<endl;
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