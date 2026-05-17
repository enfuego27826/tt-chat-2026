CXX = g++
CXXFLAGS = -Wall -Wextra -g -std=c++20 -Iinclude

BUILD_DIR = build
SRC_DIR = corrected

TARGETS = $(BUILD_DIR)/client $(BUILD_DIR)/server
COMMON_SRC = $(SRC_DIR)/socket_utils.cpp

all: $(TARGETS)

$(BUILD_DIR)/%: $(SRC_DIR)/tcp_echo_%.cc $(COMMON_SRC) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean