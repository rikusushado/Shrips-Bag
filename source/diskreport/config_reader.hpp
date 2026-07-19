#pragma once

#include <cstdint>
#include <string>
#include <vector>

using namespace std;

struct TargetList {
    string name{"Unknown"};
    uint8_t warning_treshold;
    string address{"Unknown"};
    uint16_t port{22};
    string user{"Unknown"};
    string key_path{"Unknown"};
};

vector<TargetList> getTargets(string config_path);

using Language = string[2];

struct LanguageData {
    char selected_lang[3];
    vector<Language> lang_list;
};

string getLanaguagePath(string config_path);

struct NotifierConfig {
    string tool_name{"Unknown"};
    vector<string> tool_options{"Unknown"};
};

NotifierConfig getNotifierConfig(string config_path);
