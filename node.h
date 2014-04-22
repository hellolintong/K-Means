#ifndef NODE_HEAD
#define NODE_HEAD
#include <vector>
#include <map>

//OBJECT里面的类型
typedef double DATA_TYPE ;
typedef unsigned int uint;


//定义node
typedef struct OBJ{
	std::vector<DATA_TYPE> attrs;
}OBJ;

//一个簇包含object的下标
typedef std::vector<uint> CLUSTER;

//聚类的结构。
typedef std::vector<CLUSTER>  VEC_CLUSTER;;

//object到cluster的映射
//key为object下标。value为cluster下标
typedef std::map<uint, uint> OBJ_MAP;

//node 比较函数，first == second 返回 0, first > second.返回1。 first < second.返回-1
// 避免点之间的比较（会有性能上的代价）
//int MyCompare(const Node &first, const Node &second);

#endif