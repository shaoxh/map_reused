//
// Created by godu on 2021/4/26.
//

#ifndef MAP_REUSED_MYDBHELPER_H
#define MAP_REUSED_MYDBHELPER_H

#include "string"
#include "MapInfoDto.h"
#include "../include/MyDbHelper.h"
#include "../include/FeatureDto.h"
#include "../include/MappointDto.h"

using namespace std;

class MyDbHelper {

public:
    MyDbHelper();

    ~MyDbHelper();

    static string buildInsertMapInfo(MapInfoDto mapInfoDto);

    static string buildInsertFeature(FeatureDto featureDto);

    static string buildInsertMappoint(MappointDto mappointDt);


};


#endif //MAP_REUSED_MYDBHELPER_H
