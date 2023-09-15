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

    operationType getOperationType();
    //need to return pair string
    void getCementElement(operationType ops, string& materialStr, string& comStr, long double& quantity);
    void cementOneshotSender(const string materialStr, const string comStr);
    void cementOverallSender(const long double quantity, const string comStr);
    void operationSender(const CarbonFeatureMessage opsSend);
    void deleteMsgQueue();


private:
    int msqid_;
    std::string operation;
    std::string material;
    std::string com;
    bool isMaterialValid;
    bool iscomStrValid;
    bool isOpsValid;
    std::pair<string,string> pairMaterialCom;
};
