#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ios>
#include <ctime>
#include "dmatfile.h"
#include "k-mean.h"
#include "node.h"
#include "pam.h"
#include "clarans.h"

using namespace std;

bool GetData(const string fileName, vector<OBJ> &objData){
	DMATFILE fileHandler;
	if(DMAT_OK != OpenDMat(fileName.c_str(), fileHandler )){
		return false;
	};

	vector<double> binData(fileHandler.hdr.nRowCnt * fileHandler.hdr.nAttrCnt);
	LoadDMat(fileHandler, binData.data());

	objData.resize(fileHandler.hdr.nRowCnt);
	vector<OBJ> ::iterator pos = objData.begin();
	for(; pos != objData.end() ; ++pos){
		pos->attrs.resize(fileHandler.hdr.nAttrCnt);
		LoadDMatRow(fileHandler, pos - objData.begin(), pos->attrs.data());
	}

	CloseDMat(fileHandler);
	return true;
}

int main()
{
	srand(uint(time(0)));
	uint  nClusterNum = 0;
	float fTermNum = 0.0;
	cout << "�������������"<<endl;
	cin >> nClusterNum;
	cout << "��������ֹ��Χ"<<endl;
	cin >> fTermNum;
	vector<OBJ> objData;

	if(! GetData("iris.dmat", objData) ){
		return -1;
	}
	//PAM pam(nClusterNum, &objData);
	//pam.Start();
	//KMean kmean(nClusterNum, &objData);
	//kmean.Start(fTermNum);
	
	uint numLocal;
	uint maxNeighbor;
	cout << "���� numLocalֵ:"<< endl;
	cin >> numLocal;
	cout << "���� maxNeighborֵ:"<<endl;
	cin >> maxNeighbor;

	CLARANS clarans(nClusterNum, &objData, numLocal, maxNeighbor);
	clarans.Start();
	
	return 0;
}