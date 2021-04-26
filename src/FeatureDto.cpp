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

}

FeatureDto::~FeatureDto() {

}

string FeatureDto::makeSqlValue() {
    boost::format fmt("('%s', %d, '%s', '%s', %d, '%s', %f, %f, %d, %f, %d, %d)");
    fmt % id % name % imgId % orbvec % mappointName % mapId % ptX % ptY % size % angle % response % octave;
    cout << fmt.str() << endl;
    return fmt.str();
}

string FeatureDto::createFeature() {
    boost::uuids::uuid aUUID = boost::uuids::random_generator()();
    string uuidStr = boost::uuids::to_string(aUUID);
    this->id = uuidStr;
    return id;
}

string
FeatureDto::createFeature(long name, string imgId, string orbvec, long mappointName, string mapId, float pyX, float ptY,
                          int size, float angle, int response, int octave) {
    if (id.empty()) {
        this->createFeature();
    }
    this->name = name;
    this->imgId = std::move(imgId);
    this->orbvec = orbvec;
    this->mappointName = mappointName;
    this->size = size;
    this->angle = angle;
    this->response = response;
    this->octave = octave;
}

string FeatureDto::createFeature(long name, string imgId, string mapId) {
    if (id.empty()) {
        this->createFeature();
    }
    this->name = name;
    this->imgId = std::move(imgId);
    this->mapId = std::move(mapId);
}
