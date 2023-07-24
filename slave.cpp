#include "SlaveHelper.hpp"
#include "database/DatabaseServer.hpp"

using namespace std;

int main() {
    SlaveHelper slavehelper("CF_message", 1);
    if (slavehelper.process(cfMsg::Resp))
    {
        cout << "Msg resp done, setup the database" << endl;
        carbonElemental ce;
        ce.Name = "testCpp";
        ce.Data = 1.234567890234567890234567890234567890;
        if (DatabaseServer::getInstance()->insertElemental(ce));
            cout <<"test behavior done" << endl;
    }
    return 0;
}
