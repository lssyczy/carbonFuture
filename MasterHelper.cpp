#include "MasterHelper.hpp"
#include "commonHelper.hpp"
#include "include/TableStruct.hpp"

#include <map>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;


MasterHelper::MasterHelper(string msg, int msgId)
{
    commonHelper commonhelper(msg, msgId);
    msqid_ = commonhelper.getMsqid();
    isMaterialValid = false;
    isOpsValid  = false;
}

MasterHelper::~MasterHelper()
{

}

void MasterHelper::deleteMsgQueue()
{
    //msgctl(msqid_, IPC_RMID, NULL);
}

operationType MasterHelper::getOperationType()
{
    while (!isOpsValid)
    {
        cout << "Please input your request with below operation type: ";
        for (auto &m : operationStr)
        {
            cout << m.second << "/";
        }
        cout << endl;

        cin >> operation;

        auto inter = operationStr.begin(); 
        while (inter != operationStr.end())
        {
            if ( operation == inter->second)
            {
                return inter->first;
            }
            ++inter;
        }

        cout << "Non-valid operation type, please try again." << endl;
    }
    isOpsValid = false;
}

void MasterHelper::getCementElement(operationType ops, string& materialStr, string& comStr, long double& quantity)
{
    if (ops == operationType::oneshot)
    {
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
            cout << "Material available!" << endl;
            materialStr = material;
        }else
        {
            cout << "Material not available!" << endl;
            exit(-1);
        }
    } else
    {
        cout << "Please input the quantity of cement: ";
        cin >> quantity;
    }

    cout << "Please input comStr: ";
    for (auto& c: comStrVec)
        cout << c << "/";
    cout << endl;
    cin >> com;

    for (auto& c: comStrVec)
    {
        if (!c.compare(com))
        {
            iscomStrValid = true;
            break;
        }
    }

    if (iscomStrValid)
    {
        cout << "com available!" << endl;
        comStr = com;
    }else
    {
        cout << "com not available!" << endl;
        exit(-1);
    }
}

void MasterHelper::cementOneshotSender(const string materialStr, const string comStr)
{
   /**/ Message message;

    cementOneshotFactor oneshotfactor;
    oneshotfactor.first = materialStr;
    oneshotfactor.second = comStr;

    message.mtype = CarbonFeatureMessage::Material;
    strcpy(message.mtext, oneshotfactor.first.data());
    //cout << "message.mtext: " << message.mtext << endl;
    msgsnd(msqid_, &message, sizeof(message.mtext), IPC_NOWAIT);


    message.mtype = CarbonFeatureMessage::Com;
    strcpy(message.mtext, oneshotfactor.second.data());
    //cout << "message.mtext: " << message.mtext << endl;
    msgsnd(msqid_, &message, sizeof(message.mtext), IPC_NOWAIT);

    this_thread::sleep_for(chrono::seconds(1));
}

void MasterHelper::cementOverallSender(const long double quantity, const string comStr)
{
    Message message;

    cementOverallFactor overallfactor;
    overallfactor.first = quantity;
    overallfactor.second = comStr;

    message.mtype = CarbonFeatureMessage::Quantity;
    sprintf(message.mtext, "%.8lf",overallfactor.first);
    //cout << "message.mtext: " << message.mtext << endl;
    msgsnd(msqid_, &message, sizeof(message.mtext), IPC_NOWAIT);


    message.mtype = CarbonFeatureMessage::Com;
    strcpy(message.mtext, overallfactor.second.data());
    //cout << "message.mtext: " << message.mtext << endl;
    msgsnd(msqid_, &message, sizeof(message.mtext), IPC_NOWAIT);

    this_thread::sleep_for(chrono::seconds(1));
}

void MasterHelper::operationSender(const CarbonFeatureMessage opsSend)
{
    Message message;

    message.mtype = CarbonFeatureMessage::OpsGeneral;

    strcpy(message.mtext, cfMsgToStr[opsSend].data());
    //cout << "message.mtext: " << message.mtext << endl;
    msgsnd(msqid_, &message, sizeof(message.mtext), IPC_NOWAIT);

    //this_thread::sleep_for(chrono::seconds(1));
    memset(message.mtext, '\0', sizeof(message.mtext));
    //msgctl(msqid_, IPC_RMID, NULL);
    cout << "delete " << cfMsgToStr[opsSend] << " message queue"<< endl;
}