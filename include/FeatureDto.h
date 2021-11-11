//
// Created by godu on 2021/4/26.
//

#ifndef MAP_REUSED_FEATUREDTO_H
#define MAP_REUSED_FEATUREDTO_H

#include "string"
#include "Constant.h"

using namespace std;
class FeatureDto {
public:
    string id;
    long kfId;
    double imgTimestamp;
    string orbvec;
    unsigned long mappointName;
    string mapId;
    int createTime;
    float ptX;
    float ptY;
    int size;
    float angle;
    int response;
    int octave;

    FeatureDto * featureDto;

    FeatureDto();
    ~FeatureDto();

    string createFeature();
    string createFeature(long name, double imgId, string mapId);
    string createFeature(long name, double imgId, string orbvec, long mappointName,
                         string mapId, float pyX, float ptY, int size,
                         float angle, int response, int octave);
    string makeSqlValue();

};


#endif //MAP_REUSED_FEATUREDTO_H
