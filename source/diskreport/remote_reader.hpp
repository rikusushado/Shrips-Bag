#include <cstdint>
#include <glaze/glaze.hpp>
#include <libssh/libssh.h>
#include <string>
#include <sys/types.h>
#include <vector>

struct TargetList {
    std::string name{"Unknown"};
    uint8_t warning_treshold;
    std::string address{"Unknown"};
    uint16_t port{22};
    std::string user{"Unknown"};
    std::string key_path{"Unknown"};
};

std::vector<TargetList> getConfig(std::string config_path);

std::string readUsage(std::string host, uint16_t port, std::string user, std::string key_path);

std::vector<std::string> readUsageOnTargets(std::string config_path);
