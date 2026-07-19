#pragma once

#include <libssh/libssh.h>
#include <string>

using namespace std;

struct ShripSsh {
    static ssh_session createSession();

    static void sessionSetup(ssh_session session, string host, uint16_t remote_port, string user);

    static ssh_key keyFromFile(string key_path);

    static void authenticate(ssh_session session, ssh_key pubkey);

    static ssh_channel createChannel(ssh_session session);

    static void channelOpen(ssh_session session, ssh_channel channel);

    static void channelExec(ssh_channel channel, string command);

    static string channelOutput(ssh_channel channel);

    static void sessionClose(ssh_session session, ssh_channel channel, ssh_key pubkey);
};
