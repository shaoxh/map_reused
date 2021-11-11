//
// Created by godu on 2021/4/26.
//


#include "../include/FeatureDto.h"
#include "iostream"
#include <utility>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/format.hpp>

using namespace std;

FeatureDto::FeatureDto() {
    this->ptX= Constant::DEFAULT_FLOAT;
    this->ptY= Constant::DEFAULT_FLOAT;

}

FeatureDto::~FeatureDto() {

}

string FeatureDto::makeSqlValue() {
    boost::format fmt("('%s', %d, '%.6lf', '%s', %d, '%s', %f, %f, %d, %f, %d, %d)");
    fmt % id % kfId % imgTimestamp % orbvec % mappointName % mapId % ptX % ptY % size % angle % response % octave;
//    cout << fmt.str() << endl;
    return fmt.str();
}

string FeatureDto::createFeature() {
    boost::uuids::uuid aUUID = boost::uuids::random_generator()();
    string uuidStr = boost::uuids::to_string(aUUID);
    this->id = uuidStr;
    return id;
}

string
FeatureDto::createFeature(long name, double imgId, string orbvec, long mappointName, string mapId, float pyX, float ptY,
                          int size, float angle, int response, int octave) {
    if (id.empty()) {
        this->createFeature();
    }
    this->kfId = name;
    this->imgTimestamp = imgId;
    this->orbvec = orbvec;
    this->mappointName = mappointName;
    this->size = size;
    this->angle = angle;
    this->response = response;
    this->octave = octave;
}

string FeatureDto::createFeature(long name, double imgId, string mapId) {
    if (id.empty()) {
        this->createFeature();
    }
    this->kfId = name;
    this->imgTimestamp = imgId;
    this->mapId = std::move(mapId);
}
