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
    void cementMessageReceiver(std::string& materialStr, std::string& comStr);
    void generateDummyData(unsigned int testLoop);
private:
    int msqid_;


};
