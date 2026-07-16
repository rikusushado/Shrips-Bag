#include <iostream>
#include "ShripsBag/shripssh.hpp"

ssh_session ShripSsh::createSession() {
    ssh_session session = ssh_new();
    if (session == nullptr) {
        std::cerr << "Could not create SSH session." << std::endl;
    }

    return session;
}

void ShripSsh::sessionSetup(ssh_session session, std::string host, uint16_t remote_port, std::string user) {
    uint16_t port = remote_port;
    if (remote_port == 0) {
        port = 22;
    }

    ssh_options_set(session, SSH_OPTIONS_HOST, host.c_str());
    ssh_options_set(session, SSH_OPTIONS_PORT, &port);
    ssh_options_set(session, SSH_OPTIONS_USER, user.c_str());
}

void ShripSsh::authenticate(ssh_session session, ssh_key pubkey) {
    int ec;
    ec = ssh_userauth_publickey(session, nullptr, pubkey);

    if (ec != SSH_AUTH_SUCCESS) {
        std::cerr << "Failed to authenticate." << std::endl;
        ssh_free(session);
    }

    ec = ssh_connect(session);
    if (ec != SSH_OK) {
        std::cerr << "Failed to connect." << std::endl;
        ssh_free(session);
        ssh_key_free(pubkey);
    }
}


void ShripSsh::sessionClose(ssh_channel channel, ssh_session session, ssh_key pubkey) {
    ssh_channel_free(channel);
    ssh_disconnect(session);
    ssh_free(session);
    ssh_key_free(pubkey);
}
