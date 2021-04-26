//
// Created by godu on 2021/4/25.
//

#include "../include/MapInfoDto.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>


string MapInfoDto::createMap(int sliceNum, double sliceParam) {
    this->sliceNum = sliceNum;
    this->sliceParam = sliceParam;

    this->createTime = time(nullptr);
    boost::uuids::uuid aUUID = boost::uuids::random_generator()();
    string uuidStr = boost::uuids::to_string(aUUID);
    this->id=uuidStr;
    return id;
}

MapInfoDto::MapInfoDto() {

}

MapInfoDto::~MapInfoDto() {

}
