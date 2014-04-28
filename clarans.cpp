#include <stdlib.h>
#include <algorithm>
//#include <windows.h>
#include "clarans.h"

using namespace std;

void MySwap(uint &a, uint &b){
	uint temp = a;
	a = b;
	b = temp;
}

CLARANS::CLARANS(uint nClusterNum, const std::vector<OBJ> *pVector, uint myNumLocal, uint myMaxNeighbor):PAM(nClusterNum, pVector){
	numLocal = myNumLocal;
	maxNeighbor = myMaxNeighbor;
	cost = MAX;
	randomArrayPoint = (uint *)malloc(sizeof(uint) * pAllObj->size());
	if(!randomArrayPoint){
		exit(-1);
	}
	for(uint i = 0; i < pAllObj->size(); ++i){
		randomArrayPoint[i] = i;
	}
}
void CLARANS::ClaransProcess(){
	for(uint i = 1; i < numLocal; ){
		vector<OBJITER> current;
		getRandomNode(current);
		double costCurrent = CalNodeCost(current);

		for(uint j = 1; j <= maxNeighbor;){
			vector<OBJITER> S;
			GetNeighbor(current, S);
			double costS = CalNodeCost(S);
			if (costS < costCurrent){
				current = S;
				costCurrent = costS;
				j = 1;
			}
			else{
				++j;
			}
		}

		if(costCurrent < cost){
			cost = costCurrent;
			midObjIter = current;
			AssignObj();
		}
		++i;
	}

}

void CLARANS :: GetNeighbor(const std::vector<OBJITER> &current, std::vector<OBJITER> &neighobor){
	uint changePos = rand() % current.size();
	neighobor = current;
	uint randomIndex = rand() % (pAllObj->size() - midObjIter.size());
	neighobor[changePos] = pAllObj->begin() + randomArrayPoint[randomIndex];
	MySwap(randomArrayPoint[randomIndex], randomArrayPoint[pAllObj->size() - midObjIter.size() - 1 + changePos]);
}

double CLARANS :: CalNodeCost(const std::vector<OBJITER> &node){
	double tempCost = 0.0;
	vector<OBJITER> tempMidOj = midObjIter;
	midObjIter = node;
	for(uint i = 0 ; i < pAllObj->size(); ++i){
		uint index = GetMinDis(i);
		tempCost += objDisRecord[i][index];
	}
	midObjIter = tempMidOj;
	return tempCost;
}

void CLARANS :: getRandomNode(std::vector<OBJITER> &randomNode){
	for(uint i = 0; i < midObjIter.size(); i++){
		uint randomIndex = rand() % (pAllObj->size() - i);
		randomNode.push_back(pAllObj->begin() + randomIndex);
		MySwap(randomArrayPoint[randomIndex], randomArrayPoint[pAllObj->size() - i - 1]);
	}
}

void CLARANS :: Start(){
	ClaransProcess();

	return ;
}