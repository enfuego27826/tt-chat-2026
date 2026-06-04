#pragma once

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>

void check_error(bool test, std::string error_message);

int create_socket();
