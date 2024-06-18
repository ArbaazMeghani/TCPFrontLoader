#include "urlresolver.h"

bool URLResolver::parseURL(const std::string &url, std::string &hostname, int &port, std::string &path)
{
    std::regex url_regex(R"(^(http://|https://)?([^:/]+)(:([0-9]+))?(/.*)?$)");
    std::smatch url_match_result;

    if (std::regex_match(url, url_match_result, url_regex))
    {
        hostname = url_match_result[2].str();
        port = url_match_result[4].str().empty() ? 80 : std::stoi(url_match_result[4].str());
        path = url_match_result[5].str().empty() ? "/" : url_match_result[5].str();
        return true;
    }
    return false;
}

std::string URLResolver::resolveHostname(const std::string &hostname)
{
    struct addrinfo hints, *res;
    std::memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; // IPV4 addresses
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(hostname.c_str(), nullptr, &hints, &res) != 0)
    {
        std::cerr << "Error resolving hostname\n";
        return "";
    }

    struct sockaddr_in *h = (struct sockaddr_in *)res->ai_addr;
    std::string ip = inet_ntoa(h->sin_addr);
    freeaddrinfo(res);

    return ip;
}
