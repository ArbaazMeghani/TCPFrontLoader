#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <iostream>
#include <cstring>
#include <span>
#include <thread>
#include <chrono>
#include <unistd.h>
#include <arpa/inet.h>

class TCPClient
{
public:
    TCPClient(const std::string &server_ip, int server_port);
    ~TCPClient();

    bool connectToServer();
    bool sendDataWithDelay(const std::string &data, int delay_ms);
    std::string receiveData();

private:
    bool sendData(std::span<const char> data);
    bool sendLastByte(char last_byte);
    void delay(int milliseconds);
    void setReceiveTimeout(int seconds);

    std::string server_ip_;
    int server_port_;
    int sockfd_;
    struct sockaddr_in server_addr_;
};

#endif