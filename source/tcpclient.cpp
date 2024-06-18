#include "headers/tcpclient.h"

TCPClient::TCPClient(const std::string &server_ip, int server_port)
    : server_ip_(server_ip), server_port_(server_port), sockfd_(-1)
{
    std::memset(&server_addr_, 0, sizeof(server_addr_));
    server_addr_.sin_family = AF_INET;
    server_addr_.sin_port = htons(server_port_);
    inet_pton(AF_INET, server_ip_.c_str(), &server_addr_.sin_addr);
}

TCPClient::~TCPClient()
{
    if (sockfd_ != -1)
    {
        close(sockfd_);
    }
}

bool TCPClient::connectToServer()
{
    sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_ < 0)
    {
        std::cerr << "Error creating socket\n";
        return false;
    }

    if (connect(sockfd_, (struct sockaddr *)&server_addr_, sizeof(server_addr_)) < 0)
    {
        std::cerr << "Error connecting to server\n";
        close(sockfd_);
        return false;
    }

    return true;
}

bool TCPClient::sendData(std::span<const char> data)
{
    size_t total_sent = 0;
    size_t data_length = data.size();

    while (total_sent < data_length)
    {
        size_t sent = send(sockfd_, data.data() + total_sent, data_length - total_sent, 0);
        if (sent < 0)
        {
            std::cerr << "Error sending data\n";
            return false;
        }
        total_sent += sent;
    }

    return true;
}

bool TCPClient::sendLastByte(char last_byte)
{
    size_t sent = send(sockfd_, &last_byte, 1, 0);
    if (sent < 0)
    {
        std::cerr << "Error sending last byte\n";
        return false;
    }
    return true;
}

void TCPClient::delay(int milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

bool TCPClient::sendDataWithDelay(const std::string &data, int delay_ms)
{
    if (data.empty())
    {
        std::cerr << "Data is empty\n";
        return false;
    }

    // Extract last byte
    char last_byte = data.back();
    std::span<const char> main_data(data.data(), data.size() - 1);

    // Send main data
    if (!sendData(main_data))
    {
        return false;
    }

    // Delay
    delay(delay_ms);

    // Send last byte
    if (!sendLastByte(last_byte))
    {
        return false;
    }

    return true;
}
