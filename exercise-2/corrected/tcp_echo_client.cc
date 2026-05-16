#include <arpa/inet.h>
#include <cstdlib>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <optional>

int create_socket() {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    return -1;
  }
  return sock;
}

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

bool send_all(int sock, const std::string &message){
  size_t total_sent = 0;

  while(total_sent < message.size()){
    ssize_t send_size = send(sock, message.c_str()+total_sent,
                            message.size()-total_sent,0);

    if(send_size <= 0){
      return false;
    }

    total_sent += send_size;
  }

  return true;
}

std::optional<std::string> read_all(int sock, char* buffer, int kBufferSize){
  std::string received;

  while(true){
    ssize_t read_size = read(sock,buffer,kBufferSize);

    if(read_size == 0) {
      std::cout << "Server closed connection.\n";
      return std::nullopt;
    }

    if(read_size < 0){
      std::cerr << "Read error \n";
      return std::nullopt;
    }

    received.append(buffer,read_size);

    auto pos = received.find('\n');
    if(pos != std::string::npos){ 
      received.erase(pos);
      break;
    }
  }

  return received;
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