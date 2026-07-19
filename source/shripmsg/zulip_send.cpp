#include "ShripsBag/shripmsg.hpp"

#include <iostream>
#include <curl/curl.h>

int ShripMsg::zulipSendMessage(string url, string credentials, string post_fields) {
    int ec = -1;

    curl_global_init(CURL_GLOBAL_ALL);
    CURL* curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields.c_str());

        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
        curl_easy_setopt(curl, CURLOPT_USERPWD, credentials.c_str());

        CURLcode res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            cerr << "cURL Error: " << curl_easy_strerror(res) << endl;
            ec = 1;
        } else {
            cout << "Message request sent successfully." << endl;
            ec = 0;
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return ec;
}
