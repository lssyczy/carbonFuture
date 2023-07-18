#include "DatabaseServer.hpp"

using namespace std;

DatabaseServer::DatabaseServer()
{
    con = mysql_init(NULL);
    mysql_options(con, MYSQL_SET_CHARSET_NAME, "GBK");
    
    if (!mysql_real_connect(con, host, user, passwd, database, port, NULL, 0))
    {
        cout<<"mysql server connection failed: " << mysql_error(con)<<endl;
        exit(1);
    }
    else
        cout<<"mysql server connected successfully!"<<endl;
}

DatabaseServer::~DatabaseServer()
{
    mysql_close(con);
}

bool DatabaseServer::insertElemental(/*const carbonElemental ce*/)
{
    //TO BE IMPLEMENTATION
    return 1;
}

bool DatabaseServer::deleteElemental(/*const carbonElemental ce*/)
{
    //TO BE IMPLEMENTATION
    return 1;
}

bool DatabaseServer::updateElemental(/*const carbonElemental ce*/)
{
    //TO BE IMPLEMENTATION
    return 1;
}

vector<carbonElemental> getElementals(const carbonElemental ce)
{
    //TO BE IMPLEMENTATION
    return {};
}