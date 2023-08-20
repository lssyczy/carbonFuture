#pragma once

#include <cstring>
#include <vector>

using namespace std;

const vector<string> supportedAlgorithm = {"cement"};

const vector<string> comStrVec = {"32.5M", "32.5RM", "42.5M", "42.5RM", "52.5M", "52.5RM"};
const vector<string> MaterialVec = {"Limestone", "Flyash", "Gypsum", "IronPowderMineralMud", "QuartzSandMineralMud", "Slag", "Shale", "ConstructionWaste", "CoalGangue", "AcetyleneSludge", "Ammonia", "Water", "Electricity", "Coal", "CO2"};
const vector<string> TypeVec  = {"resourceCon", "energyCon", "exhaustEmi"};
typedef struct cementTab {
    unsigned int Index;
    string comStr;
    string Material;
    string Type;
    long double Quantity;
    long double CarbonEmission;
} cementTab;