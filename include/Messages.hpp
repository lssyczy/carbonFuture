#pragma once

struct Message {
    long mtype; 
    char mtext[1024];
};

enum CarbonFeatureMessage {
	Req = 0,
	Resp
};

typedef CarbonFeatureMessage cfMsg;