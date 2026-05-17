#include "socket_utils.hpp"
#include<iostream>
#include<sys/socket.h>
#include<unistd.h>

int create_socket() {
  int my_sock = socket(AF_INET, SOCK_STREAM, 0);

  if(my_sock < 0) {
    return -1;
  }

  return my_sock;
}

bool send_all(int sock, const std::string &message) {
  size_t total_sent = 0;

  while(total_sent < message.size()) {
    ssize_t send_size =
        send(sock, message.c_str() + total_sent,
             message.size() - total_sent, 0);

    if(send_size <= 0) {
      return false;
    }

    total_sent += send_size;
  }

  return true;
}

std::optional<std::string> read_all(int sock, char *buffer, int kBufferSize) {
  std::string received;

  while(true) {
    ssize_t read_size = read(sock, buffer, kBufferSize);

    if(read_size == 0) {
      std::cout << "Client disconnected.\n";
      return std::nullopt;
    }

    if(read_size < 0) {
      std::cerr << "Read error\n";
      return std::nullopt;
    }

    received.append(buffer, read_size);

    auto pos = received.find('\n');

    if(pos != std::string::npos) {
      received.erase(pos);
      break;
    }
  }

  return received;
}