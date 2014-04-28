#pragma  once
#include "pam.h"

const uint MAX = 1000000;

void MySwap(uint &a, uint &b);

class CLARANS:public PAM{
public:
	CLARANS(uint nClusterNum, const std::vector<OBJ> *pVector, uint numLocal, uint maxNeighbor);	
	void Start();
private:
	uint *randomArrayPoint;
	uint numLocal;
	uint maxNeighbor;
	void ClaransProcess();
	void GetNeighbor(const std::vector<OBJITER> &current, std::vector<OBJITER> &neighobor);
	double CalNodeCost(const std::vector<OBJITER> &node);
	void getRandomNode(std::vector<OBJITER> &randomNode);
};