#include "httprequest.h"

HTTPRequest::HTTPRequest(Method method, const std::string &path, const std::string &host)
    : method_(method), path_(path), host_(host)
{
    addHeader("Host", host);
    addHeader("Connection", "close");
}

void HTTPRequest::addHeader(const std::string &name, const std::string &value)
{
    headers_.emplace_back(name, value);
}

void HTTPRequest::setBody(const std::string &body)
{
    body_ = body;
    addHeader("Content-Length", std::to_string(body.size()));
}

std::string HTTPRequest::methodToString(Method method) const
{
    switch (method)
    {
    case Method::GET:
        return "GET";
    case Method::POST:
        return "POST";
    case Method::PUT:
        return "PUT";
    case Method::DELETE:
        return "DELETE";
    case Method::PATCH:
        return "PATCH";
    case Method::HEAD:
        return "HEAD";
    case Method::OPTIONS:
        return "OPTIONS";
    default:
        return "";
    }
}

std::string HTTPRequest::buildRequest() const
{
    std::ostringstream request;
    request << methodToString(method_) << " " << path_ << " HTTP/1.1\r\n";
    for (const auto &header : headers_)
    {
        request << header.first << ": " << header.second << "\r\n";
    }
    request << "\r\n";
    request << body_;
    return request.str();
}
