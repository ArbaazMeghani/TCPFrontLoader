#include <vector>
#include <thread>
#include <iostream>
#include <stop_token>
#include "urlresolver.h"
#include "tcpclient.h"
#include "httprequest.h"

// Example usage function
void sendDataToServer(const std::string &url, HTTPRequest::Method method, const std::string &body, int delay_ms, std::stop_token st)
{
    URLResolver resolver;
    std::string hostname, path;
    int port;

    if (!resolver.parseURL(url, hostname, port, path))
    {
        std::cerr << "Failed to parse URL: " << url << "\n";
        return;
    }

    std::string server_ip = resolver.resolveHostname(hostname);
    if (server_ip.empty())
    {
        std::cerr << "Failed to resolve hostname: " << hostname << "\n";
        return;
    }

    HTTPRequest request(method, path, hostname);
    request.setBody(body);

    TCPClient client(server_ip, port);
    if (!client.connectToServer())
    {
        std::cerr << "Failed to connect to server: " << server_ip << ":" << port << "\n";
        return;
    }

    std::string request_str = request.buildRequest();

    if (!client.sendDataWithDelay(request_str, delay_ms))
    {
        std::cerr << "Failed to send data to server: " << server_ip << ":" << port << "\n";
    }
    else
    {
        std::cout << "Data sent successfully to server: " << server_ip << ":" << port << "\n";
    }

    std::string response = client.receiveData();
    std::cout << "Received response: " << response << "\n";
}

// Usage example
int main()
{
    // List of server URLs
    std::vector<std::string> urls = {
        "tcpbin.com:4242"};

    std::vector<std::string> data = {
        "Hello, World! This is a test message for server 1.\n"};

    int delay_ms = 5000; // Delay of 5 seconds

    // Create threads for each server
    std::vector<std::jthread> threads;
    for (size_t i = 0; i < urls.size(); ++i)
    {
        threads.emplace_back(sendDataToServer, urls[i], HTTPRequest::Method::GET, data[i], delay_ms, std::stop_token{});
    }

    // Threads will automatically be joined when they go out of scope
    return 0;
}
