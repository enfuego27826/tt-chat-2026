#include "server.h"
#include "../utils.h"

namespace tt::chat::server{

Server::Server(int port): listening_socket_(), server_address_(port){
    int sock = listening_socket_.get();
    int opt = 1;
    int err_code = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                             &opt, sizeof(opt));
    check_error(err_code < 0, "setsockopt() error\n");

    err_code = bind(sock,server_address_.as_sockaddr(),server_address_.size()); 
    check_error(err_code < 0, "bind failed\n");

    err_code = listen(sock, 3);
    check_error(err_code < 0, "listen failed\n");
}

void Server::run(){
    while(true){
        sockaddr_in client_addr{};
        socklen_t client_len = sizeof(client_addr);

        int client_fd_ = accept(listening_socket_.get(),(sockaddr*)&client_addr, &client_len);
        check_error(client_fd_ < 0, "Accept error\n");

        net::Socket client_socket(client_fd_);
        handle_client(std::move(client_socket));
    }
}

void Server::handle_client(net::Socket client_socket){
    const int kBufferSize = 1024;
    char buffer[kBufferSize] = {0};
    int sock = client_socket.get();
    ssize_t read_size = read(sock, buffer, kBufferSize);

    check_error(read_size < 0,
                    "Read error on client socket " + std::to_string(sock));
    if (read_size > 0) {
    std::cout << "Received:" << buffer << "\n";
    send(sock, buffer, read_size, 0);
    std::cout << "Echo message sent\n";
    } else if (read_size == 0) {
    std::cout << "Client disconnected.\n";
    } else {
    std::cerr << "Read error on client socket " << sock << "\n";
    }
}
}
