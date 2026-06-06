#ifndef CHAT_SOCKETS_H
#define CHAT_SOCKETS_H

#include <arpa/inet.h>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "../utils.h"

namespace tt::chat::net {

int create_socket();
sockaddr_in create_address(int port);

class Socket{
public:
    Socket();
    explicit Socket(int fd);

    ~Socket();

    Socket(const Socket& other) = delete;
    Socket& operator=(const Socket& other) = delete;

    Socket(Socket&& other) noexcept;
    Socket& operator=(Socket&& other) noexcept;

    int get() const;
    bool is_valid() const;
    void close_sock();

private:
    int socket_fd_;
};

class Address{
public:
    explicit Address(int port); //server ctor
    Address(const std::string &server_ip, int port); //client ctor

    const sockaddr* as_sockaddr() const;
    socklen_t size() const;
    void create_address(int port);

private:
    sockaddr_in address_{};
};

} // namespace tt::chat::net

#endif // CHAT_SOCKETS_H
