#include "SlaveHelper.hpp"
#include <chrono>

using namespace std;

int main() {

    uint64_t startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    SlaveHelper slavehelper("CF_message", 1);
    
    if (slavehelper.process(cfMsg::Resp))
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
    }
    uint64_t endTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    cout << "Program execution time: " << endTime - startTime <<"ms"<<endl;
    return 0;
}
