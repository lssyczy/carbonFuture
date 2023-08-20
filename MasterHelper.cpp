#include "MasterHelper.hpp"
#include "commonHelper.hpp"
#include "include/TableStruct.hpp"

#include <map>
#include <vector>

using namespace std;


MasterHelper::MasterHelper(string msg, int msgId)
{
    commonHelper commonhelper(msg, msgId);
    msqid_ = commonhelper.getMsqid();
    isMaterialValid = false;
}

MasterHelper::~MasterHelper()
{
}

bool MasterHelper::operationProceed()
{
    cout << "Please input your request with below operation type: ";
    for (auto &m : cfMsgToStr)
    {
        cout << m.second << "/";
    }
    cout << endl;

    cin >> operation;

    try
    {
        bool isOpsValid = false;
        auto inter = cfMsgToStr.begin(); 
        while (inter != cfMsgToStr.end())
        {
            if (operation == inter->second)
            {
                isOpsValid = true;
                break;
            }
            ++inter;
        }
        if (!isOpsValid)
            throw "Not a valid operation type, exiting...";
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(-1);
    }

    Message message;
    message.mtype = 1;
    strcpy(message.mtext, operation.data());

    msgsnd(msqid_, &message, sizeof(message.mtext), 0);
    cout << "MasterProcessWoker: " << message.mtext << " sent, prepare to receiving..." << endl;

    msgrcv(msqid_, &message, sizeof(message.mtext), 1, 0);
    cout << "MasterProcessWoker: " << message.mtext << " received, done." << endl;

    msgctl(msqid_, IPC_RMID, NULL);

    return true;
}

void MasterHelper::cementImp()
{
    pair<string,string> ret;
    cout << "Please input Material: ";
    for (auto& m: MaterialVec)
        cout << m << "/";
    cout << endl;
    cin >> material;

    for (auto& m: MaterialVec)
    {
        if (!m.compare(material))
        {
            isMaterialValid = true;
            break;
        }
    }

    if (isMaterialValid)
    {
        cout << "cement element available!" << endl;
    }else
    {
        cout << "cement element not available!" << endl;
        exit(-1);
    }


    //return {};
}