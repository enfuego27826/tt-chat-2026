CXX = g++
CXXFLAGS = -Wall -Wextra -g -std=c++20

BUILD_DIR = build
SRC_DIR = src

TARGETS = $(BUILD_DIR)/client $(BUILD_DIR)/server

all: $(TARGETS)

$(BUILD_DIR)/%: $(SRC_DIR)/tcp_echo_%.cc
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean