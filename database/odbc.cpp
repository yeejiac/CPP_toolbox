#include "odbc.h"

ODBC::ODBC()
{
    ip->readLine();
	std::string addr = ip->iniContainer["addr"].c_str();
	std::string database = ip->iniContainer["database"].c_str();
    std::string port = ip->iniContainer["port"].c_str();
    std::string user = ip->iniContainer["user"].c_str();
    std::string password = ip->iniContainer["password"].c_str();


    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env_);
    SQLSetEnvAttr(env_, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0);
    SQLAllocHandle(SQL_HANDLE_DBC, env_, &dbc_);

    std::string command = "DRIVER={MySQL ODBC 3.51 Driver};"+"Server="+addr+";Port="+port+";Database="+database+";Uid="+user+";Pwd="+password+";";
    //command looks like this now:
    //"DRIVER={MySQL ODBC 3.51 Driver};SERVER=localhost;DATABASE=test;"

    int ret = SQLDriverConnect(dbc_, NULL, (SQLWCHAR *)command.c_str(), SQL_NTS, NULL, 0, NULL, SQL_DRIVER_COMPLETE);

    if (!SQL_SUCCEEDED(ret)) 
    {
        // errMsg_ += CONNECT_DATABASE*DATABASE_UNREACHABLE;
        stat_ = false;
        return;
    }
    else 
    {
        stat_ = true;
    }

    SQLAllocHandle(SQL_HANDLE_STMT, dbc_, &stmt_);

    // command = sysToStd(DBINIT);

    SQLPrepare(stmt_, (SQLWCHAR *)command.c_str(), SQL_NTS);
    ret = SQLExecute(stmt_);
}