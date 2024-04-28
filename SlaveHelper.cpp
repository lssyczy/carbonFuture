#include "SlaveHelper.hpp"
#include "commonHelper.hpp"
#include "include/Messages.hpp"

#include <map>
#include <chrono>
#include <thread>
#include <cerrno>

SlaveHelper::SlaveHelper(std::string msg, int msgId)
{
    commonHelper commonhelper(msg, msgId);
    msqid_ = commonhelper.getMsqid();
    isOpsReceived = false;
}

SlaveHelper::~SlaveHelper()
{
}

bool SlaveHelper::process()
{
    Message message;
    msgrcv(msqid_, &message, sizeof(message.mtext), 1, 0);

    //if (message.mtext == )

    std::cout << "SlaveProcessWorker: " << message.mtext << std::endl;

    message.mtype = 1;
    std::strcpy(message.mtext, cfMsgToStr[CarbonFeatureMessage::SearchResp].data());

    msgsnd(msqid_, &message, sizeof(message.mtext), 0);
    
    std::cout << "SlaveProcessWorker: " << message.mtext <<" sent"<< std::endl;

    msgctl(msqid_, IPC_RMID, NULL);

    return true;
}

void SlaveHelper::cementOneshotReceiver(std::string& materialStr, std::string& comStr)
{
    Message message;
    bool isMatRec = false;
    bool isComRec= false;
    cout << "cementOneshotReceiver: waiting for user select material and com" << endl;
    while(!isMatRec)
    {
        msgrcv(msqid_, &message, sizeof(message.mtext), CarbonFeatureMessage::Material, 0);
        if (message.mtext != '\0');
        {
            materialStr = message.mtext;
            isMatRec = true;
        }
    }
    while(!isComRec)
    {
        msgrcv(msqid_, &message, sizeof(message.mtext), CarbonFeatureMessage::Com, 0);
        if (message.mtext != '\0');
        {
            comStr = message.mtext;
            isComRec = true;
        }
    }
}

void SlaveHelper::cementOverallReceiver(long double& quantity, std::string& comStr)
{
    Message message;
    bool isQuantityRec = false;
    bool isComRec= false;
    cout << "cementOverallReceiver: waiting for user select quantity and com" << endl;
    while(!isQuantityRec)
    {
        msgrcv(msqid_, &message, sizeof(message.mtext), CarbonFeatureMessage::Quantity, 0);
        if (message.mtext != '\0');
        {
            quantity = atof(message.mtext);
            isQuantityRec = true;
        }
    }
    while(!isComRec)
    {
        msgrcv(msqid_, &message, sizeof(message.mtext), CarbonFeatureMessage::Com, 0);
        if (message.mtext != '\0');
        {
            comStr = message.mtext;
            isComRec = true;
        }
    }
}

void SlaveHelper::generateDummyData(unsigned int testLoop)
{
    /*Generate dummy data table*/
    carbonElemental ce;
    std::default_random_engine engine;
    for (unsigned int i = 0; i < testLoop ; i++)
    {
        stringstream stream;
        stream << i;
        string i_new;
        stream >> i_new;
        ce.Name = "DummyData" + i_new;
        rand();
        double randoxNumber = engine();
        ce.Data = randoxNumber;
        DatabaseServer::getInstance()->insertElemental(ce);
        cout<<"counter: "<<i<<endl;
        }
}

void SlaveHelper::operationReceiver(Message& message, std::string& opsRec)
{
    //cout << "operationReceiver: waiting for user select ops" << endl;
    int ret = msgrcv(msqid_, &message, MAX_MESSAGE_SIZE, CarbonFeatureMessage::OpsGeneral, 0);
    if (ret == -1)
        cout << "Error: " << strerror(errno) << std::endl;
    opsRec = message.mtext;
    //cout << "opsRec: " << opsRec << std::endl;
}
