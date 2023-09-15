#include "SlaveHelper.hpp"
#include <chrono>

using namespace std;

int main() {

    uint64_t startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    SlaveHelper slavehelper("CF_message", 1);

    std::string ops;
    slavehelper.operationReceiver(ops);
    //cout << "ops: " << ops << endl;

    if (ops == "OpsOneshot")
    {
        std::string materialStr = "";
        std::string comStr = "";

        slavehelper.cementOneshotReceiver(materialStr,comStr);
        cout << "OpsOneshot: materialStr: " <<materialStr<< "; comStr: "<< comStr << endl;
        cementOneshotFactor oneshotfactor;
        oneshotfactor.first = materialStr;
        oneshotfactor.second = comStr;
        vector<cementElemental> cementVec = DatabaseServer::getInstance()->getCementOneshotElementals(oneshotfactor);

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

        slavehelper.cementOverallReceiver(quantity, comStr);
        cout << "OpsOverall: quantity: " << quantity << " and comStr: " << comStr << endl;
        vector<cementElemental> cementVec = DatabaseServer::getInstance()->getCementOverallElementals(comStr);

        for (auto& cementvec: cementVec)
        {
            /*cout << "****************************************" << endl;
            cout<< "Index: "<< cementvec.Index << "\n"
            << "comStr: " << cementvec.comStr << "\n"
            << "Material: " <<cementvec.Material << "\n"
            << "Type: " << cementvec.Type << "\n"
            << "Quantity: " << cementvec.Quantity << "\n"
            << "CarbonEmission: " << cementvec.CarbonEmission << endl; 
            cout << "****************************************" << endl;*/
            singleMaterialEmssion = cementvec.Quantity * cementvec.CarbonEmission;
            carbonEmissionSum += singleMaterialEmssion;
        }
        cout << "****************************************" << endl;
        cout << "sum of "<< comStr << " carbon emission with quantity: " << quantity << " is: " << carbonEmissionSum*quantity << endl;
        cout << "****************************************" << endl;
    } else
    {
        cout << "Not a supported operation" << endl;
    }
    
    /*if (slavehelper.process())
    {
        vector<string> name = {"DummyData129999","DummyData129998","DummyData998","DummyData129995","DummyData129928","DummyData119998","DummyData998"};
        cout << "Msg resp done, setup the database" << endl;
        //slavehelper.generateDummyData(130000);
        
        vector<carbonElemental> ceVec = DatabaseServer::getInstance()->getElementals(name);
        for (auto& cevec: ceVec)
        {
            cout<< "Index: "<< cevec.Index 
            << "\t Name: " << cevec.Name
            << "\t Data: " <<cevec.Data
            << "\t Year: " << cevec.Year
            << "\t Region: " << cevec.Region
            << endl; 
            cout << "------------------------------------------------------------------------------------------"<<endl;
        }
        //ce.Name = "testCpp";
        //ce.Data = 1.234567890234567890234567890234567890;
        //bool res = DatabaseServer::getInstance()->insertElemental(ce);

        //ce.Name = "new3";
        //res = res & DatabaseServer::getInstance()->deleteElemental(ce);
    }*/
    uint64_t endTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    cout << "Program execution time: " << endTime - startTime <<"ms"<<endl;
    return 0;
}
