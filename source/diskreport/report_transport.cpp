#include "report_transport.hpp"

#include "ShripsBag/shripmsg.hpp"
#include "config_reader.hpp"

#include <iostream>

#include <curl/curl.h>

int sendUsageZulip(vector<string> tool_options, string report_content) {
    string url = tool_options[0];

    string email = tool_options[1];
    string api_key = tool_options[2];

    string credentials = email + ":" + api_key;

    CURL *curl;

    char* encoded_stream  = curl_easy_escape(curl, tool_options[3].c_str(), tool_options[3].length());
    char* encoded_topic   = curl_easy_escape(curl, tool_options[4].c_str(), tool_options[4].length());
    char* encoded_content = curl_easy_escape(curl, report_content.c_str(), report_content.length());


    string post_fields = "type=stream"
    "&to=" + std::string(encoded_stream) +
    "&topic=" + std::string(encoded_topic) +
    "&content=" + std::string(encoded_content);

    int ec = ShripMsg::zulipSendMessage(url, credentials, post_fields);

    if (ec == -1) return 400;

    if (ec != 0) {
        ec += 400;
    }

    return ec;
}


int sendUsageReport(string config_path, string report_content) {
    NotifierConfig notifier_config = getNotifierConfig(config_path);

    string tool_name = notifier_config.tool_name;

    if (tool_name == "Unknown") return 203;

    int ec;
    if ( tool_name == "Zulip" ) {
        ec = sendUsageZulip(notifier_config.tool_options, report_content);
    } else {
        cerr << "Failed: Messanger or notifier unkown." << endl;
        return 203;
    }

    return 0;
}
