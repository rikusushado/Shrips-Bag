#pragma once

#include <string>
#include <vector>

#include <libssh/libssh.h>

using namespace std;

string readUsage(string host, uint16_t port, string user, string key_path);

vector<string> readUsageOnTargets(string config_path);
