#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <optional>
#include <string>

const int kBufferSize = 1024;

int create_socket() {
  int my_sock = socket(AF_INET, SOCK_STREAM, 0);

  if(my_sock < 0) {
    return -1;
  }

  return my_sock;
}

bool set_socket_options(int sock, int opt) {
  if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                 sizeof(opt)) < 0) {
    return false;
  }

  return true;
}

sockaddr_in create_address(int port) {
  sockaddr_in address{};
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);

  return address;
}

bool bind_address_to_socket(int sock, sockaddr_in &address) {
  if(bind(sock,(sockaddr *)&address, sizeof(address)) < 0) {
    return false;
  }

  return true;
}

bool listen_on_socket(int sock) {
  if(listen(sock, 3) < 0) {
    return false;
  }

  return true;
}

bool start_listening_on_socket(int my_socket, sockaddr_in &address) {
  const int kSocketOptions = 1;

  if(!set_socket_options(my_socket, kSocketOptions)) {
    return false;
  }

  if(!bind_address_to_socket(my_socket, address)) {
    return false;
  }

  if(!listen_on_socket(my_socket)) {
    return false;
  }

  return true;
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

void handle_accept(int client_socket) {
  char buffer[kBufferSize] = {0};

  auto received = read_all(client_socket, buffer, kBufferSize);

  if(!received) {
    close(client_socket);
    return;
  }

  std::cout << "Received: " << *received << "\n";

  if(!send_all(client_socket, *received + "\n")) {
    std::cerr << "Send error\n";
    close(client_socket);
    return;
  }

  std::cout << "Echo message sent\n";

  close(client_socket);
}

void handle_connections(int sock) {
  // #Question - is it good to have an infinite loop?
  while(true) {
    sockaddr_in client_address{};
    socklen_t client_size = sizeof(client_address);

    int accepted_socket =
        accept(sock,(sockaddr *)&client_address, &client_size);

    if(accepted_socket < 0) {
      std::cerr << "accept error\n";
      continue;
    }

    handle_accept(accepted_socket);
  }
}

int main() {
  const int kPort = 8080;
  int my_socket = create_socket();

  if(my_socket < 0) {
    std::cerr << "Socket creation error\n";
    return -1;
  }

  sockaddr_in address = create_address(kPort);

  // #Question - is there a better name for this function?
  if(!start_listening_on_socket(my_socket, address)) {
    std::cerr << "Failed to setup server socket\n";
    close(my_socket);
    return -1;
  }

  std::cout << "Server listening on port " << kPort << "\n";

  handle_connections(my_socket);
  close(my_socket);

  return 0;
}