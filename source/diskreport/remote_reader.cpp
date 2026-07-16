#include "remote_reader.hpp"
#include "ShripsBag/shripssh.hpp"
#include <iostream>

std::vector<TargetList> getConfig(std::string config_path) {

    std::vector<TargetList> target_list;

    auto ec = glz::read_file_json(target_list, config_path, std::string{});

    if (ec) {
        std::cerr << "Failed to read target list." << std::endl;
    };

    return target_list;
}

std::string readUsage(std::string host, uint16_t port, std::string user, std::string key_path) {
    auto session = ShripSsh::createSession();
    ShripSsh::sessionSetup(session, host, port, user);

    auto pubkey = ShripSsh::sshKeyFromFile(key_path);

    ShripSsh::authenticate(session, pubkey);

    auto channel = ShripSsh::createChannel(session);

    ShripSsh::channelOpen(channel, session);

    ShripSsh::channelExec(channel, "df -h /");

    std::string output = ShripSsh::channelOutput(channel);

    ShripSsh::sessionClose(channel, session, pubkey);

    return output;
}

std::vector<std::string> readUsageOnTargets(std::string config_path) {
    auto target_list = getConfig(config_path);

    std::vector<std::string> disk_free_readings;

    for (auto& target : target_list) {
        auto output = readUsage(target.address, target.port, target.user, target.key_path);

        disk_free_readings.push_back(output);
    }


    return disk_free_readings;
}
