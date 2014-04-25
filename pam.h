#pragma once
#include <vector>
#include "node.h"

//distance between nodes
typedef std::vector< double > VECNODE;
typedef std::vector< VECNODE >  DISTRECORD;
typedef std :: vector<OBJ> :: const_iterator OBJITER;

//get the distance between two nodes
static double Kdistance(const OBJ &first, const OBJ &second);


class PAM{
public:
		PAM(uint nClusterNum, const std::vector<OBJ> *pVector);
		void Start();//start the PAM algorithm
		
private:
	uint nClusterNum;//cluster numbers
	double cost;
	const std:: vector<OBJ> *pAllObj;//all the objects
	VEC_CLUSTER cluster;//cluster
	OBJ_MAP clusterMap;//object map to cluster
	//std::vector<uint> midObjIndex;//cluster map to middle object id in the all object vector
	std::vector<OBJITER> midObjIter;//all middle objects 
	DISTRECORD objDisRecord;//record the distance between objects
	std::vector< uint > randomVec;//random number vector

	void Init();	//fill data vector
	void AssignObj();//assign objects to different cluster
	void ClusterProcess();//cluster process
	double CalCost(uint i, uint j);//calculate the exchange object cost, return the least cost object id
	bool PAM::ISMidObj(uint i);
	uint  GetMinDis(uint i);//get the shortest distance between one object and all the mid-node
};