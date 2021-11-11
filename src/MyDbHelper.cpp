//
// Created by godu on 2021/4/26.
//

#include <boost/format.hpp>
#include "../include/MyDbHelper.h"
#include "iostream"

//static const string TBL_MAP_INFO = "tbl_map_info";
//static const string MAP_INFO_COLUMNS = " (id, sliceNum, sliceParam) ";

using namespace std;

static const string TBL_MAP_INFO = "tbl_map_info";
static const string MAP_INFO_COLUMNS = " (id, sliceNum, sliceParam, comment) ";

static const string TBL_FEATURE = "tbl_feature";
static const string FEATURE_COLUMNS = " (id, kfId, imgTimestamp, orbvec, mappointName, "
                                      "mapId, ptX, ptY, size, angle, response, octave)";

static const string TBL_MAPPOINT = "tbl_mappoint";
static const string MAPPOINT_COLUMNS = " (id, name, mapId, x, y, z) ";

MyDbHelper::MyDbHelper() {

}

MyDbHelper::~MyDbHelper() {

}

string MyDbHelper::buildInsertMapInfo(MapInfoDto mapInfo) {
    boost::format fmt("insert into " + TBL_MAP_INFO + MAP_INFO_COLUMNS + "values('%s', %d, %d, '%s');");
    fmt % mapInfo.id % mapInfo.sliceNum % mapInfo.sliceParam % mapInfo.comment;
    string sql = fmt.str();
    return sql;
}

string MyDbHelper::buildInsertFeature(FeatureDto featureDto) {
    boost::format fmt("insert into " + TBL_FEATURE + FEATURE_COLUMNS + " values %s;");
    fmt % featureDto.makeSqlValue();
    return fmt.str();
}

string MyDbHelper::buildInsertMappoint(MappointDto mappointDt) {
    boost::format fmt("insert into " + TBL_MAPPOINT + MAPPOINT_COLUMNS + " values %s;");
    fmt % mappointDt.makeSqlValue();
    return fmt.str();
}
