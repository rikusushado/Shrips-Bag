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

int parseOutputHelper(std::string output);

std::vector<int> parseOutput(std::vector<std::string> output_matrix);
