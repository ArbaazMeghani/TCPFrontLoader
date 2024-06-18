#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <iostream>
#include <sstream>
#include <vector>

class HTTPRequest
{
public:
    enum class Method
    {
        GET,
        POST,
        PUT,
        DELETE,
        PATCH,
        HEAD,
        OPTIONS
    };

    HTTPRequest(Method method, const std::string &path, const std::string &host);

    std::string buildRequest() const;

    void addHeader(const std::string &name, const std::string &value);
    void setBody(const std::string &body);

private:
    Method method_;
    std::string path_;
    std::string host_;
    std::string body_;
    std::vector<std::pair<std::string, std::string>> headers_;
    std::string methodToString(Method method) const;
};

#endif