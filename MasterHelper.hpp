#pragma once

#include "include/Messages.hpp"
#include "commonHelper.hpp"

class MasterHelper
{
public:
	MasterHelper(std::string msg, int msgId);
	~MasterHelper();

	bool process(cfMsg cfmsg);
private:
	int msqid_;

};
