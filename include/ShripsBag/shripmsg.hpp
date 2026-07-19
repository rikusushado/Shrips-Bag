#pragma once

#include <curl/curl.h>
#include <string>

using namespace std;

struct ShripMsg {
    static int zulipSendMessage(string url, string credentials, string message);
};
