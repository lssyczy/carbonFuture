#include "MasterHelper.hpp"

using namespace std;

int main() {
    MasterHelper masterhelper("CF_message", 1);
    if (masterhelper.process(cfMsg::Req))
        cout << "Msg send/receive success" << endl;
    else
        cout << "Msg send/receive fail" << endl;

    return 0;
}

