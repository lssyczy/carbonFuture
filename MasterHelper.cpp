#include "MasterHelper.hpp"
#include "commonHelper.hpp"

#include <map>


std::map <cfMsg, std::string> cfMsgToStr = 
{{CarbonFeatureMessage::Req, "Message::Req"},
{CarbonFeatureMessage::Resp, "Message::Resp"}};

MasterHelper::MasterHelper(std::string msg, int msgId)
{
    commonHelper commonhelper(msg, msgId);
    msqid_ = commonhelper.getMsqid();
}

MasterHelper::~MasterHelper()
{
}

bool MasterHelper::process(cfMsg cfmsg)
{
    Message message;
    message.mtype = 1;
    std::strcpy(message.mtext, cfMsgToStr[cfmsg].data());

    msgsnd(msqid_, &message, sizeof(message.mtext), 0);
    std::cout << "MasterProcessWoker: " << message.mtext <<" sent, prepare to receiving..."<< std::endl;

    msgrcv(msqid_, &message, sizeof(message.mtext), 1, 0);
    std::cout << "MasterProcessWoker: " << message.mtext << " received, done."<< std::endl;

    msgctl(msqid_, IPC_RMID, NULL);

    return true;
}
