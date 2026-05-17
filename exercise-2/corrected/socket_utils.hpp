#pragma once
#include<optional>
#include<string>

int create_socket();

bool send_all(int sock, const std::string &message);

std::optional<std::string> read_all(int sock, char *buffer, int kBufferSize);