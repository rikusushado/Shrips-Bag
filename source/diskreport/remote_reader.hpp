#pragma once

#include <string>
#include <vector>

#include <libssh/libssh.h>

std::string readUsage(std::string host, uint16_t port, std::string user, std::string key_path);

std::vector<std::string> readUsageOnTargets(std::string config_path);
