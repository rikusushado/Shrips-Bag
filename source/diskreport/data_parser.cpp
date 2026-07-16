#include "data_parser.hpp"
#include <cstdint>
#include <iostream>
#include <list>

std::vector<std::string> getConfig(std::string config_path) {

    std::vector<TargetList> target_list;

    auto ec = glz::read_file_json(target_list, config_path, std::string{});

    if (ec) {
        std::cerr << "Failed to read target list." << std::endl;
    };

    std::vector<std::string> name_list;

    for (auto& target : target_list) {
        name_list.push_back(target.name);
    }

    return name_list;
}

uint8_t parseOutputHelper(std::string output) {
    std::list<char> numbers;
    ssize_t count = 0;

    for (char item : output) {
        if (count == 3) {
            count -= 1;
            numbers.pop_front();
        }

        if (item == '%' && count > 0) {
            break;
        }
        else if (isdigit(item)) {
            count += 1;
            numbers.push_back(item);
        } else {
            count = 0;
            numbers.clear();
        }
    }

    uint8_t usage;

    for (char c : numbers) {
        uint8_t i = c - '0';
        usage <<= i;
    }

    return usage;
}

std::vector<uint8_t> parseOutput(std::vector<std::string> output_matrix) {
    std::vector<uint8_t> usage_matrix;

    for (std::string output : output_matrix) {
        auto usage = parseOutputHelper(output);

        usage_matrix.push_back(usage);
    }

    return usage_matrix;
}
