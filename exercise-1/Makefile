CXX = g++
CXXFLAGS = -Wall -g

BUILD_DIR = build
SRC_DIR = src

TARGETS = client server

all: $(TARGETS)

$(TARGETS):
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(wildcard $(SRC_DIR)/*_$@.cc) -o $(BUILD_DIR)/$@

clean:
	rm -f $(BUILD_DIR)/*