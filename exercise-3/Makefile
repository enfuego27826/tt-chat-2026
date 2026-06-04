CXX = g++
CXXFLAGS = -Wall -Wextra -g -std=c++20 -Iinclude

BUILD_DIR = build
SRC_DIR = src

TARGETS = $(BUILD_DIR)/client $(BUILD_DIR)/server
ASM_TARGETS = $(BUILD_DIR)/client.s $(BUILD_DIR)/server.s

all: $(TARGETS)

asm: $(ASM_TARGETS)

$(BUILD_DIR)/%: $(SRC_DIR)/tcp_echo_%.cc | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BUILD_DIR)/%.s: $(SRC_DIR)/tcp_echo_%.cc | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -S $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all asm clean