#pragma once

#include <cstdint>
#include <string>
#include <vector>

struct TargetList {
    std::string name{"Unknown"};
    uint8_t warning_treshold;
    std::string address{"Unknown"};
    uint16_t port{22};
    std::string user{"Unknown"};
    std::string key_path{"Unknown"};
};

std::vector<TargetList> getTargets(std::string config_path);

using Language = std::string[2];

struct LanguageData {
    char selected_lang[3];
    std::vector<Language> lang_list;
};

std::string getLanaguagePath(std::string config_path);
