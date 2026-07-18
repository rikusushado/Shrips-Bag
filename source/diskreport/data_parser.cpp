#include "data_parser.hpp"
#include <list>

int parseOutputHelper(std::string output) {
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

    int usage;

    for (char c : numbers) {
        uint8_t i = c - '0';
        usage <<= i;
    }

    return usage;
}

std::vector<int> parseOutput(std::vector<std::string> output_matrix) {
    std::vector<int> usage_matrix;

    for (std::string output : output_matrix) {
        auto usage = parseOutputHelper(output);

        usage_matrix.push_back(usage);
    }

    return usage_matrix;
}
