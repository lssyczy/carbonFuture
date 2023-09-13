#include "MasterHelper.hpp"

using namespace std;

int main() {
    MasterHelper masterhelper("CF_message", 1);
    string material = "";
    string com = "";
    if (masterhelper.operationProceed(material, com))
    {
        masterhelper.cementMessageSender(material,com);
        cout << "material: " << material << "; com: "<< com<< endl;
        cout << "Operation selection done" << endl;
    }
    else
    {
        cout << "Msg send/receive fail" << endl;
        return -1;
    }


}

