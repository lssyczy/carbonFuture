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

bool DatabaseServer::insertElemental(const carbonElemental ce)
{
    auto name = ce.Name;
    auto data = ce.Data;

    char sql[1024];
    sprintf(sql, "INSERT INTO source VALUES (null,\'%s\',%.15lf,2023,\'EU\')", name.c_str(), data);

    if (mysql_query(con,sql))
    {
        cout << "Failed to insert data, Error: " << mysql_error(con) << endl;
        return false;
    }
    return true;
}

bool DatabaseServer::deleteElemental(const carbonElemental ce)
{
    auto name = ce.Name;

    char sql[1024];
    sprintf(sql, "DELETE FROM source WHERE Name = \'%s\';", name.c_str());

    if (mysql_query(con,sql))
    {
        cout << "Failed to delete data, Error: " << mysql_error(con) << endl;
        return false;
    }
    return true;
}

bool DatabaseServer::updateElemental(/*const carbonElemental ce*/)
{
    //TO BE IMPLEMENTATION
    return 1;
}

carbonElemental DatabaseServer::getElementals(carbonElemental& ce)
{
    auto name = ce.Name;

    char sql[1024];
    sprintf(sql, "select Data from source where Name = \'%s\';", name.c_str());

    if (mysql_query(con,sql))
    {
        cout << "Failed to get data, Error: " << mysql_error(con) << endl;
        return {};
    }

    MYSQL_RES* res = mysql_store_result(con);
    MYSQL_ROW row;
    while(row == mysql_fetch_row(res))
    {
        ce.Data = atoi(row[0]);
    }
    return ce;
}