#pragma once

#include <string>
#include <vector>

using namespace std;

string read_file(string file_path);

vector<string> loadLangChunks(string lang_dir_path);

string generateWarning(string config_path, vector<int> usage_matrix);
