#include "chat-sockets.h"

int tt::chat::net::create_socket() {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  tt::chat::check_error(sock < 0, "Socket creation error\n");
  return sock;
}

sockaddr_in tt::chat::net::create_address(int port) {
  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_port = htons(port);
  return address;
}

namespace tt::chat::net{
  Socket::Socket(){
    socket_fd_ = socket(AF_INET,SOCK_STREAM,0);
    tt::chat::check_error(socket_fd_ < 0, "Socket creation error\n");
  }

  Socket::Socket(int fd): socket_fd_(fd){}

  Socket::~Socket(){
    close_sock();
  }

  Socket::Socket(Socket&& other) noexcept{
    socket_fd_ = other.socket_fd_;
    other.socket_fd_ = -1;
  }

  Socket& Socket::operator=(Socket&& other) noexcept{
    if(this == &other) return *this;
    
    close_sock();
    socket_fd_ = other.socket_fd_;
    other.socket_fd_ = -1;

    return *this;
  }

  int Socket::get() const{
    return socket_fd_;
  }

  bool Socket::is_valid() const{
    return (socket_fd_ != -1);
  }

  void Socket::close_sock(){
    if(socket_fd_ != -1) close(socket_fd_);
    socket_fd_ = -1;
  }

  Address::Address(int port){
    create_address(port);
    address_.sin_addr.s_addr = INADDR_ANY;
  }

  Address::Address(const std::string &server_ip, int port){
    create_address(port);
    auto err_code = inet_pton(AF_INET,server_ip.c_str(), &address_.sin_addr);
    check_error(err_code <= 0, "Invlaid address/ Address not supported\n"); 
  }

  void Address::create_address(int port){
    address_.sin_family = AF_INET;
    address_.sin_port = htons(port);  
  }

  const sockaddr* Address::as_sockaddr() const{
    return reinterpret_cast<const sockaddr*>(&address_);
  }

  socklen_t Address::size() const{
    return sizeof(address_);
  }
}
