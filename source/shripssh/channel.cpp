#include "ShripsBag/shripssh.hpp"

ssh_channel ShripSsh::createChannel(ssh_session session) {
    ssh_channel channel = ssh_channel_new(session);

    if (channel == nullptr) {
        ssh_disconnect(session);
        ssh_free(session);
    }

    return channel;
}

void ShripSsh::channelOpen(ssh_session session, ssh_channel channel) {
    int ec = ssh_channel_open_session(channel);

    if (ec != SSH_OK) {
        ssh_channel_free(channel);
        ssh_disconnect(session);
        ssh_free(session);
    }
}

void ShripSsh::channelExec(ssh_channel channel, string command) {
    ssh_channel_request_exec(channel, command.c_str());
}

string ShripSsh::channelOutput(ssh_channel channel) {
    string output = "";
    char buffer[(1024*64)];
    int nbytes;

    while ((nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0)) > 0) {
        output.append(buffer, nbytes);
    }

    return output;
}
