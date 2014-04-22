//k-mean.h
#ifndef KMEAN_HEAD
#define KMEAN_HEAD

#include <vector>
#include <map>
#include <string>
#include "node.h"

double Kdistance(const OBJ &first, const OBJ &second);//求取两个点之间的距离

class KMean
{
public:
    KMean(uint nClusterNum, const std::vector<OBJ> *pVector);
	void Start(double TermDistance);//启动k均值算法
private:
	/*类数据成员定义*/
	uint nClusterNum;//生成的簇的数量。
	const std:: vector<OBJ> *pAllObj;//所有的对象
	VEC_CLUSTER Cluster;//簇
	OBJ_MAP ClusterMap;//簇和对象之间的映射
	std::vector<OBJ> MeanObj;//均值点对象容器

	/*类方法定义*/
	uint GetMinDis(uint i);//获取某个点离那个中心点最近距离
	void Init();//初始化函数（首先随即生成代表点）
	void AssignObj();//将所有点分配到不同的簇中
	void GetMean(uint cluster_index, OBJ &AverNode);

	void OutputData(const std::string fileName);//将数据输出

};
#endif // KMEAN_HEAD