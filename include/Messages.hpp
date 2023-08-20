#pragma once

#include <map>
#include <cstring>

struct Message {
    long mtype; 
    char mtext[1024];
};

typedef enum CarbonFeatureMessage {
	Req = 0,
	Resp,
    Search,
    SearchResp
}CarbonFeatureMessage;

static std::map<CarbonFeatureMessage, std::string> cfMsgToStr =
    {{CarbonFeatureMessage::Req, "Req"},
     {CarbonFeatureMessage::Resp, "Resp"},
     {CarbonFeatureMessage::Search, "Search"},
     {CarbonFeatureMessage::SearchResp, "SearchResp"}};