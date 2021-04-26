//
// Created by godu on 2021/4/26.
//

#include <boost/format.hpp>
#include "../include/MyDbHelper.h"
#include "iostream"

//static const string MAP_INFO_TABLE = "tbl_map_info";
//static const string MAP_INFO_COLUMNS = " (id, sliceNum, sliceParam) ";

using namespace std;

static const string MAP_INFO_TABLE = "tbl_map_info";
static const string MAP_INFO_COLUMNS = " (id, sliceNum, sliceParam) ";

string MyDbHelper::buildInsertMapInfo(MapInfoDto mapInfo) {
    boost::format fmt("insert into " + MAP_INFO_TABLE + MAP_INFO_COLUMNS + "values('%s', %d, %d);");
    fmt % mapInfo.id % mapInfo.sliceNum % mapInfo.sliceParam;
    string sql = fmt.str();
    return sql;
}

MyDbHelper::MyDbHelper() {

}

MyDbHelper::~MyDbHelper() {

}
