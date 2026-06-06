#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "./net/server.h"

int main() {
  const int kPort = 8080;

  try{
    tt::chat::server::Server server(kPort);
    std::cout << "Server listening on port " << kPort << "\n";

    server.run();
  }

  catch(const std::exception& e){
    std::cerr << "Server error: " << e.what() << "\n";
    return EXIT_FAILURE;
  }

  return 0;
}
