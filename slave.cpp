#include "SlaveHelper.hpp"
#include <chrono>
#include <thread>
#include <string.h>

using namespace std;

typedef void (*printData)(std::string ops, void *arg);
typedef struct {
    printData cb;
    SlaveHelper *_slavehelp;
}callBackFunc;

void *parseMessageThread (void *arg)
{
    callBackFunc *myCb = (callBackFunc *)arg;
    std::string ops;
    Message message;

    while(1)
    {
        myCb->_slavehelp->operationReceiver(message, ops);
        myCb->cb(ops, myCb->_slavehelp);
        memset(&message, 0, sizeof(message));
        ops.clear();
    }
}

void *readDataCb(std::string ops, void *arg)
{
    SlaveHelper *slavehelper = (SlaveHelper *) arg;
    vector<cementElemental> cementVec;
    if(ops == "OpsOneshot")
    {
        std::string materialStr = "";
        std::string comStr = "";

        slavehelper->cementOneshotReceiver(materialStr,comStr);
        cout << "OpsOneshot: materialStr: " <<materialStr<< "; comStr: "<< comStr << endl;
        cementOneshotFactor oneshotfactor;
        oneshotfactor.first = materialStr;
        oneshotfactor.second = comStr;
        cementVec = DatabaseServer::getInstance()->getCementOneshotElementals(oneshotfactor);

        for (auto& cementvec: cementVec)
        {
            cout << "****************************************" << endl;
            cout<< "Index: "<< cementvec.Index << "\n"
            << "comStr: " << cementvec.comStr << "\n"
            << "Material: " <<cementvec.Material << "\n"
            << "Type: " << cementvec.Type << "\n"
            << "Quantity: " << cementvec.Quantity << "\n"
            << "CarbonEmission: " << cementvec.CarbonEmission << endl; 
            cout << "****************************************" << endl;
        }
    } else if (ops == "OpsOverall") 
    {
        long double quantity = 0;
        long double carbonEmissionSum = 0;
        long double singleMaterialEmssion = 0;
        std::string comStr = "";

        slavehelper->cementOverallReceiver(quantity, comStr);
        cout << "OpsOverall: quantity: " << quantity << " and comStr: " << comStr << endl;
        cementVec = DatabaseServer::getInstance()->getCementOverallElementals(comStr);

        for (auto& cementvec: cementVec)
        {
            singleMaterialEmssion = cementvec.Quantity * cementvec.CarbonEmission;
            carbonEmissionSum += singleMaterialEmssion;
        }
        cout << "****************************************" << endl;
        cout << "sum of "<< comStr << " carbon emission with quantity: " << quantity << " is: " << carbonEmissionSum*quantity << endl;
        cout << "****************************************" << endl;
    }
    cementVec.clear();
}

int main() {

    SlaveHelper slavehelper("CF_message", 1);
    pthread_t t1;

    callBackFunc DataCb = {(printData)readDataCb, &slavehelper};

    pthread_create(&t1, NULL, parseMessageThread, &DataCb);

    while(1)
    {
        cout << "slave thread running...slave main thread hold on" << endl;
        this_thread::sleep_for(chrono::seconds(5));
    }

    return 0;
}
