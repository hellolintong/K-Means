#include <math.h>
#include <algorithm>
#include "pam.h"
using namespace std;
const uint MAX = 100000;

PAM::PAM(uint nMyClusterNum, const std::vector<OBJ> *pVector):pAllObj(pVector){
	nClusterNum = nMyClusterNum;
	Init();
}

void  PAM::Init(){
	//random index
	for(uint i = 0 ; i < pAllObj->size() ; ++i ){
		randomVec.push_back(i);
	}
	random_shuffle(randomVec.begin(), randomVec.end());

	//random select nClusterNum middle nodes
	for(uint i = 0 ; i < nClusterNum ; ++i){
		midObjIter.push_back(pAllObj->begin() + randomVec[i]);
	}
	//record all nodes distance
	objDisRecord.resize(pAllObj->size());
	 for(uint i = 0 ; i < pAllObj->size() ; ++i){
		 for(uint j = 0; j < pAllObj->size() ; ++j){
				 objDisRecord[i].push_back( Kdistance( pAllObj->at(i), pAllObj->at(j) ));
		}
	}
	 cluster.resize(nClusterNum);
	AssignObj();
	cost = 0;
	for(uint i = 0; i < pAllObj->size(); ++i){
		cost += objDisRecord[i][clusterMap[i]];
	}
}

// user defined compare function
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
		if(Kdistance(*x , mean) < Kdistance(*y , mean)){
			return true;
		}
		else{
			return false;
		}
	}
};

uint  PAM::GetMinDis(uint i){
	MyCompare < OBJITER > myCompare( pAllObj->at(i) );
	vector< OBJITER > :: iterator pos = min_element(midObjIter.begin() , midObjIter.end(), myCompare);
	return pos - midObjIter.begin();
}


void PAM::AssignObj(){
	//clear all cluster vector
	for(uint i = 0 ; i < cluster.size(); ++i){
		cluster[i].clear();
	}
	for(uint i = 0 ; i < pAllObj->size(); ++i){
		//get the shortest distance.
		uint index = GetMinDis(i);
		cluster[index].push_back(i);
		clusterMap[i] = index;
	}
}

bool PAM::ISMidObj(uint index){
	for(uint i = 0; i < midObjIter.size(); ++i){
		if(index + pAllObj->begin() == midObjIter[i] ){
			return true;
		}
	}
	return false;
}

double PAM::CalCost(uint midObjIndex, uint clusterObjIndex){
	OBJITER tempObj = midObjIter[midObjIndex];
	midObjIter[midObjIndex] = pAllObj->begin() + clusterObjIndex; 
	double tempCost = 0.0;
	for(uint i = 0 ; i < pAllObj->size(); ++i){
		uint index = GetMinDis(i);
		tempCost += objDisRecord[i][index];
	}
	midObjIter[midObjIndex] = tempObj;
	return tempCost;
}

void PAM::ClusterProcess(){
	uint clusterIndex = -1;
	uint objIndex = -1;
	while(true){
		double tempCost = MAX;
		//all cluster
		for(uint i = 0 ; i < midObjIter.size(); ++i){
			//all non-middle nodes in the cluster[i]
			for(uint j = 0 ; j < cluster[i].size(); ++j){
				if(ISMidObj(j) == false){
					double temp = CalCost(i,j);
					if(tempCost > temp){
						tempCost = temp;
						clusterIndex = i;
						objIndex = j;
					}
				}
			}
		}
		if(tempCost < cost){
			midObjIter[clusterIndex] = pAllObj->begin()+objIndex;
			clusterMap[objIndex] = clusterIndex;
			AssignObj();
			cost = tempCost;
		}
		else if(tempCost >= cost){
			break;
		}
	}
}

void PAM::Start(){
	ClusterProcess();
	return;
}

static double Kdistance(const OBJ &first, const OBJ &second){
	double distance = 0;
	for(uint i = 0; i < first.attrs.size(); ++i){
		distance += (first.attrs[i] - second.attrs[i]) * (first.attrs[i] - second.attrs[i]);
	}
	return distance;
}