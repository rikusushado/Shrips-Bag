#include "report_generator.hpp"
#include "config_reader.hpp"

#include <cstdint>
#include <ctime>

#include <fstream>

string read_file(string file_path)
{
    ifstream file(file_path);
    if (!file.is_open())
    {
        return "";
    }

    string content;
    string line;
    while (getline (file, line)) {
        content += line + "\n";
    }

    return content;
}

vector<string> loadLangChunks(string config_path) {
    string lang_dir_path = getLanaguagePath(config_path);

    vector<string> lang_chunks;

    string head = lang_dir_path + "/head.md";
    string table = lang_dir_path + "/table.md";

    lang_chunks.push_back(read_file(head));
    lang_chunks.push_back(read_file(table));

    return lang_chunks;
}

string generateWarning(string config_path, vector<int> usage_matrix) {
    vector<string> lang_chunks = loadLangChunks(config_path);

    string warning_string = lang_chunks[0];
    warning_string += lang_chunks[1];

    vector<TargetList> target_list = getTargets(config_path);

    int count = 0;
    for ( auto target : target_list ) {
        uint8_t usage = usage_matrix[count];
        uint8_t treshold = target.warning_treshold;

        if (usage >= treshold) {
            warning_string += "| ";
            warning_string += target.name;

            warning_string += " | ";

            warning_string += "`" + to_string(usage) + "`";
            warning_string += " |\n";
        }

        ++count;
    }

    warning_string += "---\n";

    time_t actual_time = std::time(nullptr);
    tm *local_time = std::localtime(&actual_time);

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", local_time);

    string formatted_time = buffer;

    warning_string += "*" + formatted_time + "*\n";

    warning_string += "---\n";

    return warning_string;
}
