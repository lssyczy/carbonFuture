#include "SlaveHelper.hpp"
#include "database/DatabaseServer.hpp"

using namespace std;

int main() {
    SlaveHelper slavehelper("CF_message", 1);
    if (slavehelper.process(cfMsg::Resp))
    {
        cout << "Msg resp done, setup the database" << endl;

        if (DatabaseServer::getInstance()->insertElemental() && DatabaseServer::getInstance()->deleteElemental() && DatabaseServer::getInstance()->updateElemental())
            cout <<"test behavior done" << endl;
    }
    return 0;
}
