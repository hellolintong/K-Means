#pragma  once
#include <vector>
#include <map>

//define data type
typedef double DATA_TYPE ;
typedef unsigned int uint;

//定义聚类点的类型
typedef struct OBJ{
	std::vector<DATA_TYPE> attrs;
}OBJ;

//一个簇包括了点的下标
typedef std::vector<uint> CLUSTER;

//多个簇构成的容器
typedef std::vector<CLUSTER>  VEC_CLUSTER;

//实现点到簇的映射，key为点的下标，value为簇的下标
typedef std::map<uint, uint> OBJ_MAP;
