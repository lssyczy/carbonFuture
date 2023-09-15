#include "../include/Messages.hpp"

#include <vector>
#include <cstring>
#include <mysql/mysql.h>
#include <iostream>
//test purpose files
#include <sstream>
#include<stdlib.h> 
#include<time.h> 
#include <random>

using namespace std;

//placeholder: this part should be clarified later
typedef struct cementElemental {
    unsigned int Index;
    string comStr;
    string Material;
    string Type;
    long double Quantity;
    long double CarbonEmission;
} cementElemental;

typedef struct carbonElemental {
    unsigned int Index;
    string Name;
    long double Data;
    unsigned int Year;
    string Region;
} carbonElemental;

class DatabaseServer
{
public:
    DatabaseServer();
    ~DatabaseServer();

    static DatabaseServer* getInstance()
    {
        static DatabaseServer DatabaseServer;
        return &DatabaseServer;
    }

    bool insertElemental(const carbonElemental ce);
    bool deleteElemental(const carbonElemental ce);
    bool updateElemental(/*const carbonElemental ce*/);
    vector<carbonElemental> getElementals(vector<string> nameVec);
    vector<cementElemental> getCementOneshotElementals(cementOneshotFactor cement_factor);
    vector<cementElemental> getCementOverallElementals(string comStr);

private:
    string buildSql(vector<string> nameVec);
    string buildCementOneshotSql(cementOneshotFactor cement_factor);
    string buildCementOverallSql(string comStr);
    const char* host = "192.168.50.85";
    const char* user = "visitor";
    const char* passwd = "12345678";
    const char* database = "CarbonFuture";
    const int port = 3306;
    MYSQL* con;
    vector<carbonElemental> ceVec;
    vector<cementElemental> cementVec;
    vector<string> nameVec;
};
