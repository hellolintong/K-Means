//k-mean.h
#pragma once

#include <vector>
#include <map>
#include <string>
#include "node.h"

static double Kdistance(const OBJ &first, const OBJ &second);

class KMean
{
public:
	KMean(uint nClusterNum, const std::vector<OBJ> *pVector);
	void Start(double TermDistance);//start k-mean algorithm
private:
	/*class member define*/
	uint nClusterNum;//cluster number
	const std:: vector<OBJ> *pAllObj;//all object
	VEC_CLUSTER Cluster;//cluster 
	OBJ_MAP ClusterMap;//object map to cluster
	std::vector<OBJ> MeanObj;//mean object vector

	/*class function*/
	uint GetMinDis(uint i);//get the shortest distance between the given index and all mean objects
	void Init();//init function
	void AssignObj();//assign all object to cluster
	void GetMean(uint cluster_index, OBJ &AverNode);//get mean object
	void OutputData(const std::string fileName);//output data
};