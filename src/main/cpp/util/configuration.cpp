#include "util/configuration.h"

std::string getVersion() { return VERSION; }

std::string getName() { return CONFIG_NAME; }

uint16_t getTeamNum() { return std::stoi(CONFIG_TEAMNUM); }