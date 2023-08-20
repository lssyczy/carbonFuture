#include "MasterHelper.hpp"

using namespace std;

int main() {
    MasterHelper masterhelper("CF_message", 1);
    if (masterhelper.operationProceed())
        cout << "Operation selection done" << endl;
    else
    {
        cout << "Msg send/receive fail" << endl;
        return -1;
    }

    masterhelper.cementImp();

}

