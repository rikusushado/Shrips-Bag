#include <libssh/libssh.h>
#include <string>


struct ShripSsh {
    static ssh_session createSession();

    static void sessionSetup(ssh_session session, std::string host, uint16_t remote_port, std::string user);

    static ssh_key sshKeyFromFile(std::string key_path);

    static void authenticate(ssh_session session, ssh_key pubkey);

    static ssh_channel createChannel(ssh_session session);

    static void channelOpen(ssh_channel channel, ssh_session session);

    static void channelExec(ssh_channel channel, std::string command);

    static std::string channelOutput(ssh_channel channel);

    static void sessionClose(ssh_channel channel, ssh_session session, ssh_key pubkey);
};
