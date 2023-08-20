#pragma once

#include "include/Messages.hpp"
#include "include/TableStruct.hpp"
#include "commonHelper.hpp"

#include <cstring>

class MasterHelper
{
public:
    MasterHelper(std::string msg, int msgId);
    ~MasterHelper();

    bool operationProceed();
    //need to return pair string
    void cementImp();

private:
    int msqid_;
    std::string operation;
    std::string material;
    std::string comStr;
    bool isMaterialValid;
};
