#include "SlaveHelper.hpp"

using namespace std;

int main() {
    SlaveHelper slavehelper("CF_message", 1);
    
    if (slavehelper.process(cfMsg::Resp))
    {
        carbonElemental ce;
        ce.Name = "DummyData12780";
        cout << "Msg resp done, setup the database" << endl;
        //slavehelper.generateDummyData(130000);
        
        ce = DatabaseServer::getInstance()->getElementals(ce);
        cout<< "Data: " << ce.Data<<endl;
        
        //ce.Name = "testCpp";
        //ce.Data = 1.234567890234567890234567890234567890;
        //bool res = DatabaseServer::getInstance()->insertElemental(ce);



        //ce.Name = "new3";
        //res = res & DatabaseServer::getInstance()->deleteElemental(ce);
    }
    return 0;
}
