#include <glaze/glaze.hpp>
#include <string>
#include <vector>

struct TargetList {
    std::string name{"Unknown"};
    std::string address{"Unknown"};
    uint16_t port{22};
    std::string user{"Unknown"};
    std::string key_path{"Unknown"};
};

std::vector<std::string> getConfig(std::string config_path);
