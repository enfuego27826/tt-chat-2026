#include "client.h"

namespace tt::chat::client{

Client::Client(const std::string& ip, int port): connection_socket_(), server_address_(ip,port){}

void Client::connect_to_server(){
    auto err_code = connect(connection_socket_.get(),server_address_.as_sockaddr(),server_address_.size());
    check_error(err_code < 0, "Invalid address/ Address not supported\n");
}

void Client::send_and_receive(const std::string &message){
    const int kBufferSize = 1024;
    char recv_buffer[kBufferSize] = {0};

    send(connection_socket_.get(), message.c_str(), message.size(), 0);
    std::cout << "Sent: " << message << "\n";

    ssize_t read_size = read(connection_socket_.get(), recv_buffer, kBufferSize);
    check_error(read_size < 0, "Read error.\n");

    if (read_size > 0) {
        std::cout << "Received: " << recv_buffer << "\n";
    } else if (read_size == 0) {
        std::cout << "Server closed connection.\n";
    }
}
}