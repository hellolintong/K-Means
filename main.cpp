#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ios>
#include "dmatfile.h"
#include "k-mean.h"
#include "node.h"
#include "pam.h"

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
	uint  nClusterNum = 0;
	float fTermNum = 0.0;
	cout << "请输入类的数量"<<endl;
	cin >> nClusterNum;
	cout << "请输入终止范围"<<endl;
	cin >> fTermNum;
	vector<OBJ> objData;

	if(! GetData("wine.dmat", objData) ){
		return -1;
	}
	PAM pam(nClusterNum, &objData);
	pam.Start();
	//KMean kmean(nClusterNum, &objData);
	//kmean.Start(fTermNum);
	return 0;
}