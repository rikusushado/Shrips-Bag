#include "config_reader.hpp"

#include "remote_reader.hpp"

#include "ShripsBag/shripssh.hpp"

#include <iostream>

string readUsage(string host, uint16_t port, string user, string key_path) {
    auto session = ShripSsh::createSession();
    ShripSsh::sessionSetup(session, host, port, user);

    auto pubkey = ShripSsh::keyFromFile(key_path);

    ShripSsh::authenticate(session, pubkey);

    auto channel = ShripSsh::createChannel(session);

    ShripSsh::channelOpen(session, channel);

    ShripSsh::channelExec(channel, "df -h /");

    string output = ShripSsh::channelOutput(channel);

    ShripSsh::sessionClose(session, channel, pubkey);

    return output;
}

vector<string> readUsageOnTargets(string config_path) {
    auto target_list = getTargets(config_path);

    vector<string> disk_free_readings;

    for (auto& target : target_list) {
        auto output = readUsage(target.address, target.port, target.user, target.key_path);

        if (output == "") {
            cerr << "Failed to read storage usage on: " << target.name << endl;
        }

        disk_free_readings.push_back(output);
    }

    return disk_free_readings;
}
