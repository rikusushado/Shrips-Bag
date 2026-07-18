#include "ShripsBag/shripssh.hpp"

ssh_key ShripSsh::keyFromFile(std::string key_path) {
    ssh_key pubkey = NULL;
    int ec;

    ec = ssh_pki_import_pubkey_file(key_path.c_str(), &pubkey);

    if (ec != SSH_OK) {
    }

    return pubkey;
}
