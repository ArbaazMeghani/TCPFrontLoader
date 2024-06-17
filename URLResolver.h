#pragma once
#include <iostream>
#include <regex>

#ifdef _WIN32
#include <Winsock2.h>
#include <Ws2tcpip.h>
#define access _access

#else
#include <arpa/inet.h>
#endif

class URLResolver {
public:
    bool parseURL(const std::string& url, std::string& hostname, int& port, std::string& path);
    std::string resolveHostname(const std::string& hostname);
};