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

vector<carbonElemental> DatabaseServer::getElementals(vector<string> nameVec)
{
    char sql[1024];
    auto sqlCmd = buildSql(nameVec);

    sprintf(sql, "%s", sqlCmd.c_str());
    if (mysql_query(con,sql))
    {
        cout << "Failed to get data, Error: " << mysql_error(con) << endl;
        return {};
    }

    MYSQL_RES* res = mysql_store_result(con);
    MYSQL_ROW row;
    while((row = mysql_fetch_row(res)))
    {
        carbonElemental ce;
        ce.Index = atoi(row[0]);
        ce.Name = row[1];
        ce.Data = atof(row[2]);
        ce.Year = atoi(row[3]);
        ce.Region = row[4];
        ceVec.emplace_back(ce);
    }
    return ceVec;
}

vector<cementElemental> DatabaseServer::getCementElementals(cementFactor cement_factor)
{
    char sql[1024];
    auto sqlCmd = buildCementSql(cement_factor);

    sprintf(sql, "%s", sqlCmd.c_str());
    if (mysql_query(con,sql))
    {
        cout << "Failed to get data, Error: " << mysql_error(con) << endl;
        return {};
    }

    MYSQL_RES* res = mysql_store_result(con);
    MYSQL_ROW row;
    while((row = mysql_fetch_row(res)))
    {
        cementElemental ce;
        ce.Index = atoi(row[0]);
        ce.comStr = row[1];
        ce.Material = row[2];
        ce.Type = row[3];
        ce.Quantity = atof(row[4]);
        ce.CarbonEmission = atof(row[5]);
        cementVec.emplace_back(ce);
    }
    return cementVec;
}

string DatabaseServer::buildCementSql(cementFactor cement_factor)
{
    string sqlCmdTmp = "select * from cementTab where Material = '";
    string sqlCmd = "";
    
    sqlCmd += sqlCmdTmp + cement_factor.first.c_str() + "'" + " AND comStr = '" + cement_factor.second.c_str() + "';";
    cout << "sqlCmd: " << sqlCmd << endl;
    return sqlCmd;
}

string DatabaseServer::buildSql(vector<string> nameVec)
{
    string sqlCmdHeader = "select * from source where ";
    string sqlCmdTmp = "";
    string sqlCmd = "";
    auto iter = nameVec.begin();

    for (auto& name: nameVec)
    {
        sqlCmdTmp = sqlCmdHeader + "Name = '" + name.c_str() + "'";
        if(iter != nameVec.end() - 1)
            sqlCmd += sqlCmdTmp + " OR ";
        else
            sqlCmd += sqlCmdTmp + ";";
        sqlCmdTmp = "";
        sqlCmdHeader = "";
        iter++;
    }
    cout << "sqlCmd: " << sqlCmd << endl;
    return sqlCmd;
}