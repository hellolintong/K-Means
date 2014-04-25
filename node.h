#pragma  once
#include <vector>
#include <map>
 
typedef double DATA_TYPE ;//define data type
typedef unsigned int uint;

//user define object struct
typedef struct OBJ{
	std::vector<DATA_TYPE> attrs;
}OBJ;


typedef std::vector<uint> CLUSTER;//a cluster include the index of object vector


typedef std::vector<CLUSTER>  VEC_CLUSTER;//cluster structure

//object map to cluster
// key is the object index, value is the cluster index
typedef std::map<uint, uint> OBJ_MAP;