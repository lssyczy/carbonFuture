#include "SlaveHelper.hpp"

using namespace std;

int main() {
    SlaveHelper slavehelper("CF_message", 1);
    if (slavehelper.process(cfMsg::Resp))
        cout << "Msg resp done." << endl;

    return 0;
}
