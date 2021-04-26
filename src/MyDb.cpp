//
// Created by godu on 2021/4/25.
//

#include "../include/MyDb.h"
#include <iostream>

using namespace std;


MyDb::MyDb() {

    mysql = mysql_init(nullptr);
    if (!mysql) {
        cout << "Error:" << mysql_error(mysql);
    }

}

MyDb::~MyDb() {

    if (mysql) {
        mysql_close(mysql);
    }
}

bool MyDb::initDB(string host, string user, string pwd, string dbName, int port) {
    port = 3306;

    mysql = mysql_real_connect(mysql, host.c_str(), user.c_str(), pwd.c_str(), dbName.c_str(), port, NULL, 0);
    if (!mysql) {
        cout << "Error: " << mysql_error(mysql);
        exit(1);
    }
    return true;
}

bool MyDb::exeSQL(string sql) {
    //mysql_query()执行成功返回0,执行失败返回非0值。
    if (mysql_query(mysql, sql.c_str())) {
        cout << "Query Error: " << mysql_error(mysql);
        return false;
    }

    result = mysql_store_result(mysql);

    if (result) {
        //获取结果集中总共的字段数，即列数
        int numFields = mysql_num_fields(result);
        unsigned long long numRows = mysql_num_rows(result);

        for (int i = 0; i < numRows; i++) {
            row = mysql_fetch_row(result);
            if (!row) {
                break;
            }
            for (int j = 0; j < numFields; j++) {
                if (row[j] != nullptr) {
                    string outstr = string(row[j]);
                    cout << outstr << "\t\t";
                } else{
                    cout<<"NULL"<<"\t\t";
                }
            }
            cout << endl;
        }
    } else {
        //代表执行的是update,insert,delete类的非查询语句
        if (mysql_field_count(mysql) == 0) {
            // 返回update,insert,delete影响的行数
            unsigned long long num_rows = mysql_affected_rows(mysql);

            return num_rows;
        } else {
            cout << "Get result error: " << mysql_error(mysql);
            return false;
        }
    }
    return false;
}
