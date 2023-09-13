#pragma once

#include "include/Messages.hpp"
#include "include/TableStruct.hpp"
#include "commonHelper.hpp"

#include <cstring>
#include <utility>

class MasterHelper
{
public:
    MasterHelper(std::string msg, int msgId);
    ~MasterHelper();

    bool operationProceed(string& materialStr, string& comStr);
    //need to return pair string
    void getCementElement(string& materialStr, string& comStr);
    void cementMessageSender(const string materialStr, const string comStr);

private:
    int msqid_;
    std::string operation;
    std::string material;
    std::string com;
    bool isMaterialValid;
    bool iscomStrValid;
    std::pair<string,string> pairMaterialCom;
};
