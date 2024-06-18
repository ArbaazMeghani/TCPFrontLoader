#ifndef URLRESOLVER_H
#define URLRESOLVER_H

#include <iostream>
#include <regex>
#include <netdb.h>
#include <arpa/inet.h>

class URLResolver
{
public:
    bool parseURL(const std::string &url, std::string &hostname, int &port, std::string &path);
    std::string resolveHostname(const std::string &hostname);
};

#endif