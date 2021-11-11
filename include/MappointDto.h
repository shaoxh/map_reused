//
// Created by godu on 2021/4/26.
//

#ifndef MAP_REUSED_MAPPOINTDTO_H
#define MAP_REUSED_MAPPOINTDTO_H

#include "string"
#include "opencv/highgui.h"

using namespace std;
class MappointDto {
public:
    string id;
    long name;
    string mapId;
    float x;
    float y;
    float z;
    long createTime;

    MappointDto();
    ~MappointDto();

    string createMappoint();
    string createMappoint(long name, string mapId);
    void makeMappointLocation(cv::Mat position);
    string makeSqlValue();


};


#endif //MAP_REUSED_MAPPOINTDTO_H
