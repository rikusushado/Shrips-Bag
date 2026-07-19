#include <iostream>
#include <vector>

#include <glaze/glaze.hpp>

#include "config_reader.hpp"

std::vector<TargetList> getTargets(std::string config_path) {

    std::vector<TargetList> target_list;

    auto ec = glz::read_file_json(target_list, config_path, std::string{});

    if (ec) {
        std::cerr << "Failed to read target list." << std::endl;
    };

    std::vector<std::string> name_list;

    return target_list;
}

std::string getLanaguagePath(std::string config_path) {

    LanguageData lang_data;

    auto ec = glz::read_file_json(lang_data, config_path, std::string{});

    if (ec) {
        std::cerr << "Failed to read target list." << std::endl;
    };

    auto selected_lang = lang_data.selected_lang;

    for (auto language : lang_data.lang_list) {
        if (language[0] == selected_lang) {
            return language[0];
        }
    }

    return "NULL";
}
