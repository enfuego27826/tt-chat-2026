# Exercise 4

**Update this README with your answers to the questions below.**

## Learning Multi-File C++ Projects

- Move code that can be shared between `tcp_echo_server.cc` and 
  `tcp_echo_client.cc` to separate `.h` and `.cc` files
- How would you compile from the command line?

```bash
g++ -Wall -Wextra -g -std=c++20 -Iinclude src/tcp_echo_client.cpp src/socket_utils.cpp -o build/client
```

above is for client, server is the same just replace client with server here.

- How would you compile using make?

Answer: i actually used header files in my exercise-2 solution as well so this wasn't much work, i just copy pasted the same make file. just use `make` in terminal. but here's what the makefile syntax should look like - 

```
TARGETS = $(BUILD_DIR)/client $(BUILD_DIR)/server
COMMON_SRC = $(SRC_DIR)/socket_utils.cpp

all: $(TARGETS)

$(BUILD_DIR)/%: $(SRC_DIR)/tcp_echo_%.cpp $(COMMON_SRC) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@
```

as you can see common_src is included in both client and server since its required for linking.

- How would you compile using VS Code?

Answer: I can either open the terminal in vs code and run or configure a `task.json` that involves make and then run it using run build task on vs code.

### Compiling vs Linking

- What is the difference between compiling and linking in C++?

Answer: in compiling, we convert each `.cpp` file into an object file `.o`, at this stage compiler only checks wherher function declaration exists not where their definitions are, linking happens afterwards, where all the object files are combined and references for the functions are resolved. 

- What is the difference between creating an executable and creating a 
  library?

  Answer: executable is the complete program that contains a `main` function and can be run directly but a library is just a collection of reusable code other programs can link with. libraries usually don't contain main and cannot be run directly.

- How do you compile a library, and then use that library to compile an
  executable?

Answer: first compile the library into an object file and then you can compile and link your code with the library, it goes like - 


```bash
g++ -c socket_utils.cpp -o socket_utils.o

g++ tcp_echo_client.cpp socket_utils.o -o client
```

you can also create a static library out of the library object file and compile and link it with your code.

### Reminder 
[Quickstart tutorial to make](https://makefiletutorial.com/) - Learn make 
fundamentals with practical examples and common patterns.

## Experiments in Performance

- Is it better to have many small files spread across many directories, or
  a few large files across fewer directories?
- Is there a difference in compilation time between the two?
- How can you assess performance other than compilation speed?