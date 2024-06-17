#pragma once
#include <iostream>
#include <cstring>
#include <span>
#include <socketapi.h>
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <io.h>
#include <Winsock2.h>
#include <Ws2tcpip.h>
#define access _access

#else
#include <unistd.h>
#include <arpa/inet.h>
#endif

class TCPClient {
public:
    TCPClient(const std::string& server_ip, int server_port);
    ~TCPClient();

    bool connectToServer();
    bool sendDataWithDelay(const std::string& data, int delay_ms);

private:
    bool sendData(std::span<const char> data);
    bool sendLastByte(char last_byte);
    void delay(int milliseconds);

    std::string server_ip_;
    int server_port_;
    int sockfd_;
    struct sockaddr_in server_addr_;
};