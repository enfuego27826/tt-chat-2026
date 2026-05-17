#include <arpa/inet.h>
#include <cstdlib>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <optional>
#include "socket_utils.hpp"


bool set_binary_address(sockaddr_in &address, const std::string &server_ip) {
  if (inet_pton(AF_INET, server_ip.c_str(), &address.sin_addr) <= 0) {
    std::cerr << "Invalid address/ Address not supported\n";
    return false;
  }

  return true;
}

std::optional<sockaddr_in> create_address(const std::string &server_ip, int port) {
  sockaddr_in address{};
  address.sin_family = AF_INET;
  address.sin_port = htons(port);

  if(!set_binary_address(address, server_ip)) {
    return std::nullopt;
  }

  return address;
}

bool connect_to_server(int sock, sockaddr_in &server_address) {
  if (connect(sock, (sockaddr *)&server_address, sizeof(server_address)) < 0) {
    return false;
  }

  return true;
}

void send_and_receive_message(int sock, const std::string &message) {
  const int kBufferSize = 1024;
  // #Question - is buffer the best name we can use?
  char buffer[kBufferSize] = {0};

  // Send the message to the server
  if(!send_all(sock, message+ "\n")) {
    std::cerr << "Error in sending message!" << "\n";
    return;
  }

  std::cout << "Sent: " << message << "\n";

  // Receive response from the server
  auto received = read_all(sock,buffer,kBufferSize);

  if(!received){
    return; 
  }

  std::cout << "Received: " << *received << "\n";
}

// #Question - what can be improved in this function?
std::string read_args(int argc, char *argv[]) {
  return (argc > 1) ? argv[1] : "Hello from client";
}

int main(int argc, char *argv[]) {
  const int kPort = 8080;
  const std::string kServerAddress = "127.0.0.1";

  std::string message = read_args(argc, argv);

  int my_socket = create_socket();

  if(my_socket < 0){
    std::cerr << "Socket creation error\n";
    return -1;
  }

  auto server_address = create_address(kServerAddress, kPort);

  if(!server_address){
    close(my_socket);
    std::cerr << "Failed to create server address\n";
    return -1;
  }

  if(!connect_to_server(my_socket, *server_address)){
    close(my_socket);
    std::cerr << "Connection failed\n";
    return -1;
  }
  send_and_receive_message(my_socket, message);
  close(my_socket);

  return 0;
}