#pragma once

#include <map>
#include <cstring>


using cementOneshotFactor = std::pair<std::string,std::string>;
using cementOverallFactor = std::pair<long double,std::string>;

#define MAX_MESSAGE_SIZE 1024

struct Message {
    long mtype; 
    char mtext[MAX_MESSAGE_SIZE];
};


typedef enum CarbonFeatureMessage {
	Req = 0,
	Resp,
    Search,
    SearchResp,
    Material,
    MaterialResp,
    Com,
    ComResp,
    Quantity,
    QuantityResp,
    OpsOneshot,
    OpsOverall,
    OpsGeneral
}CarbonFeatureMessage;

typedef enum operationType {
    oneshot,
    overall
}operationType;

static std::map<CarbonFeatureMessage, std::string> cfMsgToStr =
    {{CarbonFeatureMessage::Req, "Req"},
     {CarbonFeatureMessage::Resp, "Resp"},
     {CarbonFeatureMessage::Search, "Search"},
     {CarbonFeatureMessage::SearchResp, "SearchResp"},
     {CarbonFeatureMessage::Material, "Material"},
     {CarbonFeatureMessage::MaterialResp, "MaterialResp"},
     {CarbonFeatureMessage::Com, "Com"},
     {CarbonFeatureMessage::ComResp, "ComResp"},
     {CarbonFeatureMessage::Quantity, "Quantity"},
     {CarbonFeatureMessage::QuantityResp, "QuantityResp"},
     {CarbonFeatureMessage::OpsOneshot, "OpsOneshot"},
     {CarbonFeatureMessage::OpsOverall, "OpsOverall"},
     {CarbonFeatureMessage::OpsGeneral, "OpsGeneral"}};

static std::map<operationType, std::string> operationStr =
    {{operationType::oneshot, "oneshot"},
     {operationType::overall, "overall"}};