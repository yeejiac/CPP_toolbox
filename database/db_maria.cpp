#include "db_maria.h"

DB_Maria::DB_Maria(std::string configSelection)
{
    InitParser *ip = new InitParser("D:\\program_file\\CPP_toolbox\\doc\\settings.ini", configSelection);
    MY_HOSTNAME = ip->iniContainer["addr"].c_str();
    MY_DATABASE = ip->iniContainer["database"].c_str();
    MY_USERNAME = ip->iniContainer["root"].c_str();
    MY_PASSWORD = ip->iniContainer["password"].c_str();
    MY_SOCKET = NULL;
    // if(initConnection())
    //     logwrite.writeLog("debug", "(MariaDB) Init success");
}

bool DB_Maria::initConnection()
{
    try 
    {
        conn = mysql_init(NULL);
        // Establish a MySQL connection
        if (!mysql_real_connect(conn, MY_HOSTNAME, MY_USERNAME, MY_PASSWORD, MY_DATABASE, 3306, MY_SOCKET, 0)) 
        {
            // logwrite.writeLog("error", "(MariaDB) Establish a MySQL connection failed with error");
            return false;
        }
        // Try Execute a sql statement
        if (mysql_query(conn, "SHOW TABLES")) 
        {
            // logwrite.writeLog("error", "(MariaDB) Try Execute a sql statement failed with error");
            return false;
        }
        res = mysql_use_result(conn);

        // Release memories
        mysql_free_result(res);

        // Close a MySQL connection
        mysql_close(conn);
    } 
    catch (char *e) 
    {
        std::string str(e);
        // logwrite.writeLog("error", "(MariaDB) [EXCEPTION] " + str);
        return false;
    }
    return true;
}

int main()
{
    std::cout<<"HO"<<std::endl;
    DB_Maria *dbm = new DB_Maria("database");
    if(dbm->initConnection())
        std::cout<<"success"<<std::endl;;
    std::cout<<"HO"<<std::endl;
}

