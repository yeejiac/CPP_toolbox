#ifndef ODBC_H_
#define ODBC_H_

#include <iostream>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <stdlib.h>
#include <sal.h>

#include "../lib/logwriter.h"
#include "../lib/initParser.h"

class ODBC
{
public:
    ODBC();
    ~ODBC();
    Logwriter logwrite = Logwriter("DB");
    InitParser *ip = new InitParser("D:\\program_file\\CPP_toolbox\\doc\\settings.ini", "database");
private:
    std::string errMsg_ = "";
    bool stat_;
    SQLHENV env_;
    SQLHDBC dbc_;
    SQLHSTMT stmt_;
    SQLRETURN ret_; 
    
};

#endif