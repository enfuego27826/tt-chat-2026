# Thanks to Job Vranish (https://spin.atomicobject.com/2016/08/26/makefile-c-projects/)

# define the C/C++ compiler to use
CXX := g++

# define the C/C++ compiler flags
CXXFLAGS :=-std=c++20 -Wall -Wextra -pedantic -fsanitize=address

CXX_DEBUG_FLAGS :=-g3 -ggdb3
CXX_RELEASE_FLAGS :=-O3
CXX_ASSEMBLY_FLAGS :=-S -masm=intel -fverbose-asm -fno-asynchronous-unwind-tables -fno-rtti 

CXXFLAGS += $(CXX_DEBUG_FLAGS)

LDFLAGS := -fsanitize=address

BUILD_DIR := build
SRC_DIR := src

# Find all the C and C++ files we want to compile recursively
SRCS := $(shell find $(SRC_DIR) -type f -name '*.cc')

# Prepends BUILD_DIR and appends .o to every src file
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
NON_MAIN_OBJS := $(filter-out %main.cc.o, $(OBJS))

ASMS := $(SRCS:%=$(BUILD_DIR)/%.s)

# String substitution for dependency files
DEPS := $(OBJS:.o=.d)

# Every folder in ./src will need to be passed to GCC so that it can find header files
INC_DIRS := $(shell find $(SRC_DIR) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# The -MMD and -MP flags together generate Makefiles for us!
CPPFLAGS := $(INC_FLAGS) -MMD -MP

all: $(BUILD_DIR)/server $(BUILD_DIR)/client

# Build the Server executable
$(BUILD_DIR)/server: $(BUILD_DIR)/src/server-main.cc.o $(NON_MAIN_OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(BUILD_DIR)/src/server-main.cc.o $(NON_MAIN_OBJS) -o $(BUILD_DIR)/server $(LDFLAGS)

# Build the Client executable
$(BUILD_DIR)/client: $(BUILD_DIR)/src/client-main.cc.o $(NON_MAIN_OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(BUILD_DIR)/src/client-main.cc.o $(NON_MAIN_OBJS) -o $(BUILD_DIR)/client $(LDFLAGS)

# Compile C++ source files into object files
$(BUILD_DIR)/%.cc.o: %.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# Assembly generation
$(BUILD_DIR)/%.cc.s: %.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(CXX_ASSEMBLY_FLAGS) $< -o $@

.PHONY: assembly
assembly: $(ASMS)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

# Include the .d makefiles.
-include $(DEPS)