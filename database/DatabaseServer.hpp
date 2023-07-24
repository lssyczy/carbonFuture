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
typedef struct carbonElemental {
    string Name;
    long double Data;
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
    carbonElemental getElementals(carbonElemental& ce);

private:
    const char* host = "192.168.50.85";
    const char* user = "visitor";
    const char* passwd = "12345678";
    const char* database = "CarbonFuture";
    const int port = 3306;
    MYSQL* con;
};
