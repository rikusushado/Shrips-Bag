#include "config_reader.hpp"

#include <iostream>
#include <vector>

#include <glaze/glaze.hpp>

vector<TargetList> getTargets(string config_path) {
    string target_config_path = config_path + "diskreport/target.json";
    vector<TargetList> target_list;

    auto ec = glz::read_file_json(target_list, target_config_path, string{});

    if (ec) {
        cerr << "Failed to read target list." << endl;
    };

    return target_list;
}

string getLanaguagePath(string config_path) {
    string language_config_path = config_path + "language.json";

    LanguageData lang_data;

    auto ec = glz::read_file_json(language_config_path, config_path, string{});

    if (ec) {
        cerr << "Failed to read target list." << endl;
    };

    auto selected_lang = lang_data.selected_lang;

    for (auto language : lang_data.lang_list) {
        if (language[0] == selected_lang) {
            return language[1];
        }
    }

    return "NULL";
}

NotifierConfig getNotifierConfig(string config_path) {
    string notifier_config_path = config_path + "notifier.json";

    NotifierConfig notifier_config;

    auto ec = glz::read_file_json(notifier_config, config_path, string{});

    if (ec) {
        cerr << "Failed to read target list." << endl;
    };

    return notifier_config;
}
