#pragma once
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "net/chat-sockets.h"
#include "utils.h"

namespace tt::chat::client{

class Client{
public:

    Client(const std::string& ip, int port);
    
    void connect_to_server();
    void send_and_receive(const std::string &message);

private:
    net::Socket connection_socket_;
    net::Address server_address_;
};
}