#pragma once

#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>

class commonHelper
{
public:
	commonHelper(std::string msg, int msgId);
	~commonHelper();
	int getMsqid();

private:
	int msqid_;
};
