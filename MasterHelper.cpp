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
}

MasterHelper::~MasterHelper()
{
}

bool MasterHelper::operationProceed(string& materialStr, string& comStr)
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

    //TODO: Need to check if cement is a supported algorithm.
    getCementElement(materialStr,comStr);

    //cementMessageSender(matcom.first,matcom.second);
    //cementMessageSender("Limestone","32.5RM");

    return true;
}

void MasterHelper::getCementElement(string& materialStr, string& comStr)
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
        cout << "Material available!" << endl;
        materialStr = material;
    }else
    {
        cout << "Material not available!" << endl;
        exit(-1);
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

void MasterHelper::cementMessageSender(const string materialStr, const string comStr)
{
    Message message;

    cementFactor cementfactor;
    cementfactor.first = materialStr;
    cementfactor.second = comStr;

    message.mtype = CarbonFeatureMessage::Material;
    strcpy(message.mtext, cementfactor.first.data());
    cout << "message.mtext: " << message.mtext << endl;
    msgsnd(msqid_, &message, sizeof(message.mtext), IPC_NOWAIT);


    message.mtype = CarbonFeatureMessage::Com;
    strcpy(message.mtext, cementfactor.second.data());
    cout << "message.mtext: " << message.mtext << endl;
    msgsnd(msqid_, &message, sizeof(message.mtext), IPC_NOWAIT);

    this_thread::sleep_for(chrono::seconds(1));
    msgctl(msqid_, IPC_RMID, NULL);
    cout << "delete message queue"<< endl;
    /*msgrcv(msqid_, &message, sizeof(message.mtext), CarbonFeatureMessage::MaterialResp, 0);
    auto matResp = message.mtext;
    msgrcv(msqid_, &message, sizeof(message.mtext), CarbonFeatureMessage::ComResp, 0);
    auto comResp = message.mtext;
    cout << "matResp: "<< matResp << "; comResp: " << comResp << endl;
    if (matResp == "MaterialResp" && comResp == "ComResp")
    {
        msgctl(msqid_, IPC_RMID, NULL);
        cout << "delete message queue"<< endl;
    }*/


}