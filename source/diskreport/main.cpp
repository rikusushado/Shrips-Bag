#include "remote_reader.hpp"
#include "data_parser.hpp"
#include "warning_generator.hpp"
#include "report_transport.hpp"

int main() {
    string config_path = "~/.shripsbag";
    vector<string> ouput_matrix = readUsageOnTargets(config_path);

    vector<int> usage_matrix = parseOutput(ouput_matrix);
    string report_content = generateWarning(config_path, usage_matrix);

    int ec = sendUsageReport(config_path, report_content);

    return ec;
};
