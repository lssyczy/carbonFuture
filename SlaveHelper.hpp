#pragma once

#include "include/Messages.hpp"
#include "commonHelper.hpp"

class SlaveHelper
{
public:
	SlaveHelper(std::string msg, int msgId);
	~SlaveHelper();

	bool process(cfMsg cfmsg);
private:
	int msqid_;

};
