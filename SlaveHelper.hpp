#pragma once

#include "include/Messages.hpp"
#include "commonHelper.hpp"
#include "database/DatabaseServer.hpp"

class SlaveHelper
{
public:
    SlaveHelper(std::string msg, int msgId);
    ~SlaveHelper();

    bool process();
    void cementOneshotReceiver(std::string& materialStr, std::string& comStr);
    void cementOverallReceiver(long double& quantity, std::string& comStr);
    void generateDummyData(unsigned int testLoop);
    void operationReceiver(Message& message, std::string& opsRec);
private:
    int msqid_;
    bool isOpsReceived;


};
