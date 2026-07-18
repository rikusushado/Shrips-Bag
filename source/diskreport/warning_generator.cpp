#include "warning_generator.hpp"
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

vector<string> loadLangChunks(std::string lang_dir_path) {
    vector<string> lang_chunks;

    string head = lang_dir_path + "/" + "head.md";
    string table = lang_dir_path + "/" + "table.md";
    string foot = lang_dir_path + "/" + "foot.md";

    lang_chunks.push_back(read_file(head));
    lang_chunks.push_back(read_file(table));
    lang_chunks.push_back(read_file(foot));

    return lang_chunks;
}

string generateWarning(vector<string> lang_chunks, vector<TargetList> target_list, vector<uint8_t> usage_matrix) {
    string warning_string = lang_chunks[0];
    warning_string += "---\n";
    warning_string += lang_chunks[1];

    int count = 0;
    for ( auto target : target_list ) {
        uint8_t usage = usage_matrix[count];
        uint8_t treshold = target.warning_treshold;

        if (usage >= treshold) {
            warning_string += "| ";
            warning_string += "**" + target.name + "**";

            warning_string += " | ";

            warning_string += "`" + to_string(usage) + "`";
            warning_string += " |\n";
        }

        ++count;
    }

    warning_string += "---\n";
    warning_string += lang_chunks[2];

    time_t actual_time = std::time(nullptr);
    tm *local_time = std::localtime(&actual_time);

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", local_time);

    string formatted_time = buffer;

    warning_string += "*" + formatted_time + "*\n";

    warning_string += "---\n";

    return warning_string;
}
