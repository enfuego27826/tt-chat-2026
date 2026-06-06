#pragma once
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "chat-sockets.h"
#include "../utils.h"

namespace tt::chat::server{

class Server{
public:
    explicit Server(int port);

    void run();

private:
    net::Socket listening_socket_;
    net::Address server_address_;

    void handle_client (net::Socket client_socket);
};
}
