#include "MasterHelper.hpp"

using namespace std;

int main() {
    MasterHelper masterhelper("CF_message", 1);

    auto ops = masterhelper.getOperationType();
    string material = "";
    string com = "";
    long double quantity = 0;
    if (ops == operationType::oneshot)
    { 
        masterhelper.operationSender(CarbonFeatureMessage::OpsOneshot);
        masterhelper.getCementElement(ops,material,com,quantity);
        masterhelper.cementOneshotSender(material,com);
    }
    else if (ops == operationType::overall)
    {
        masterhelper.operationSender(CarbonFeatureMessage::OpsOverall);
        masterhelper.getCementElement(ops,material,com,quantity);
        masterhelper.cementOverallSender(quantity,com);
    }
    else
    {
        return -1;
    }

    masterhelper.deleteMsgQueue();
    cout << "delete message queue"<< endl;

    return 0;
}

