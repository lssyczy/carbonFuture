#include "commonHelper.hpp"

commonHelper::commonHelper(std::string msg, int msgId)
{
    key_t key = ftok(msg.data(), msgId);
    msqid_ = msgget(key, 0666|IPC_CREAT);
}

commonHelper::~commonHelper()
{
}

int commonHelper::getMsqid()
{
    return msqid_;
}
