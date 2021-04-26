//
// Created by godu on 2021/4/25.
//

#ifndef MAP_REUSED_MYDB_H
#define MAP_REUSED_MYDB_H

#include <string>
#include <mysql/mysql.h>
#include "MapInfoDto.h"
#include "boost/format.hpp"


using namespace std;

class MyDb {
public:
    MyDb();

    ~MyDb();

    /**
     * to connect mysql server
     * @param host
     * @param user
     * @param pwd
     * @param dbName
     * @param port
     * @return if it is connected
     */
    bool initDB(string host, string user, string pwd, string dbName, int port);

    /**
     * to execute a sql
     * @param sql
     * @return if it is executed
     */
    bool exeSQL(string sql);

private:
    /**
    * 连接mysql句柄指针
    */
    MYSQL *mysql;

    /**
     * 指向查询结果的指针
     */
    MYSQL_RES *result;

    /**
     * 按行返回的查询信息
     */
    MYSQL_ROW row;
};

#endif //MAP_REUSED_MYDB_H
