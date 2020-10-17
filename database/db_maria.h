#ifndef DB_MARIA_H_
#define DB_MARIA_H_

#include <iostream>
#include <windows.h>
#include <mysql/mysql.h>

// #include "../lib/logwriter.h"
#include "../lib/initParser.h"

class DB_Maria
{
public:
    DB_Maria(std::string configSelection);
    ~DB_Maria();
    bool initConnection();
    void showTable(std::string sqlString);
    // Logwriter logwrite = Logwriter("DB");

    const char* MY_HOSTNAME;
    const char* MY_DATABASE;
    const char* MY_USERNAME;
    const char* MY_PASSWORD;
    const char* MY_SOCKET;

    MYSQL     *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

private:

};
#endif