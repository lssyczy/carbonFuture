#pragma once

#include <map>
#include <cstring>


using cementFactor = std::pair<std::string,std::string>;

struct Message {
    long mtype; 
    char mtext[1024];
};


typedef enum CarbonFeatureMessage {
	Req = 0,
	Resp,
    Search,
    SearchResp,
    Material,
    MaterialResp,
    Com,
    ComResp
}CarbonFeatureMessage;

static std::map<CarbonFeatureMessage, std::string> cfMsgToStr =
    {{CarbonFeatureMessage::Req, "Req"},
     {CarbonFeatureMessage::Resp, "Resp"},
     {CarbonFeatureMessage::Search, "Search"},
     {CarbonFeatureMessage::SearchResp, "SearchResp"},
     {CarbonFeatureMessage::Material, "Material"},
     {CarbonFeatureMessage::MaterialResp, "MaterialResp"},
     {CarbonFeatureMessage::Com, "Com"},
     {CarbonFeatureMessage::ComResp, "ComResp"},};