//
// Created by godu on 2021/4/26.
//

#include "../include/MappointDto.h"
#include <utility>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/format.hpp>
#include "iostream"

using namespace std;

MappointDto::MappointDto() {

}

MappointDto::~MappointDto() {

}

string MappointDto::createMappoint() {
    boost::uuids::uuid aUUID = boost::uuids::random_generator()();
    string uuidStr = boost::uuids::to_string(aUUID);
    this->id = uuidStr;
    return id;
}

string MappointDto::createMappoint(long name, string mapId) {
    if (id.empty()){
        this->createMappoint();
    }
    this->name = name;
    this->mapId = std::move(mapId);
}

string MappointDto::makeSqlValue() {
    boost::format fmt("('%s', %d, '%s', %f, %f, %f)");
    fmt % id % name % mapId % x % y % mapId % z ;
    cout << fmt.str() << endl;
    return fmt.str();
}
