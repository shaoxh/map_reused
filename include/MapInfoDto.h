//
// Created by godu on 2021/4/25.
//

#ifndef MAP_REUSED_MAPINFODTO_H
#define MAP_REUSED_MAPINFODTO_H

#include "string"
#include <ctime>

using namespace std;

class MapInfoDto {
public:
    string id;
    int createTime;
    int sliceNum;
    double sliceParam;
    string comment;

public:
    MapInfoDto();
    ~MapInfoDto();
    /**
     * create a map instance
     * @param sliceNum
     * @param sliceParam
     * @return map instance uuid
     */
    string createMap(int sliceNum, double sliceParam);


};


#endif //MAP_REUSED_MAPINFODTO_H
