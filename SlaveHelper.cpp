#include "SlaveHelper.hpp"
#include "commonHelper.hpp"
#include "include/Messages.hpp"

#include <map>
#include <chrono>
#include <thread>

SlaveHelper::SlaveHelper(std::string msg, int msgId)
{
    commonHelper commonhelper(msg, msgId);
    msqid_ = commonhelper.getMsqid();
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

void SlaveHelper::cementMessageReceiver(std::string& materialStr, std::string& comStr)
{
    Message message;

    msgrcv(msqid_, &message, sizeof(message.mtext), CarbonFeatureMessage::Material, 0);
    materialStr = message.mtext;

    msgrcv(msqid_, &message, sizeof(message.mtext), CarbonFeatureMessage::Com, 0);
    comStr = message.mtext;

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
