# Exercise 2

**Update this README with your answers to the questions below.**

## Sources of Information for Questions from Before

### Socket 
- https://man7.org/linux/man-pages/man2/socket.2.html - System call reference
  for creating communication endpoints
- Or type `man socket` in terminal
- https://man7.org/linux/man-pages/man7/socket.7.html - Socket interface 
  overview and protocol families
- Or type `man 7 socket` in terminal
- When would you want to use a `SOCK_RAW` stream?

### TCP and IP Protocols
- [IPv4](https://www.rfc-editor.org/info/rfc791) - Internet Protocol 
  specification defining packet structure and routing
- [IPv6](https://www.rfc-editor.org/info/rfc8200) - Next-generation Internet 
  Protocol with expanded address space
- [TCP](https://datatracker.ietf.org/doc/html/rfc9293) - Transmission Control 
  Protocol providing reliable, ordered data delivery
    
### C++
- [C++23 ISO standard draft](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/n4950.pdf) - 
  Working draft of the C++ language specification
- Is the above the official C++23 spec? 
<<<<<<< HEAD
- Answer: No, it is a working draft of the C++23 standard and not the final officially published ISO document.

- Where is the official C++23 spec?
- Answer: The official C++ standard is published by ISO and usually requires purchasing/access through ISO's website.

- Why was this link chosen instead?
- Answer: The working drafts are publicly accessible for free and are extremely close to the final standard.

- Is this a helpful reference for learning C++?
- Answer: Not really for beginners. The standard is more of a formal technical/legal specification rather than a tutorial. 

- Can the various implementations of C++ compilers be different from the
  C++ standard?
- Answer: Yes, compilers can differ in implementation details, optimization behavior, although they generally try to follow the ISO standard closely.

- What are the most widely used and most significant C++ compilers?
- Answer: GCC, Clang and MSVC are the most widely used and significant C++ compilers.

- Where is the equivalent spec for C++26?
- Answer: Similar working drafts for C++26 can be found on the WG21 website where ongoing proposals and draft standards are published.

- Where do you find the spec for the HTTP protocol?
- Answer: The HTTP protocol specifications are published as RFC docs by the IETF.

- What about HTTPS? Is there a spec for that protocol?
- Answer: Yes there's a spec. HTTPS is essentially HTTP running over TLS (Transport Layer Security), so its specification comes from both the HTTP RFCs and the TLS RFCs.
=======
- Where is the official C++23 spec?
- Why was this link chosen instead?
- Is this a helpful reference for learning C++?
- Can the various implementations of C++ compilers be different from the
  C++ standard?
- What are the most widely used and most significant C++ compilers?
- Where is the equivalent spec for C++26?

- Where do you find the spec for the HTTP protocol?
- What about HTTPS? Is there a spec for that protocol?
>>>>>>> upstream/main

## Introduction to C++ and Sockets Programming

- Read the code in `src/`
- Are there any bugs in this code? 
<<<<<<< HEAD
- Answer:
  - `sockaddr_in address;` was not zero initialized which could leave garbage bytes in memory, so it was fixed using `sockaddr_in address{}`.
  
  - The code directly printed `buffer` even though `read()` does not guarantee null termination. This was fixed using `std::string(buffer, read_size)` and `append(buffer, read_size)`.
  
  - `send()` was unchecked earlier even though TCP can do partial sends. This was fixed by implementing `send_all()` which keeps sending until the whole message is sent.
  
  - The code assumed one `read()` call means one full message which is incorrect since TCP is a byte stream. This was fixed by implementing `read_all()` using '\n' as a delimiter. This made an assumption that message can't have '\n' but we need a delimiter so that's why I went with that choice.
  
  - Helper functions were directly calling `exit()` which prevented callers from handling errors properly. This was improved using `bool` returns and `std::optional`.
  
  - `std::optional` was used in functions like `create_address()` and `read_all()` to clearly represent possible failure cases.
  
  - The server reused the same `sockaddr_in` inside `accept()` which gets overwritten with client data. This was fixed using a separate `client_address`.
  
  - Some early returns leaked sockets. This was fixed by explicitly calling `close()` before returning on failure.

- What can you do to identify if there are bugs in the code?
- Answer: Reading compiler warnings carefully, having several tests, testing edge cases, using debugging tools like `gdb`, sanitizers like `-fsanitize=address`/`-fsanitize=undefined` and carefully addressing memory/resource handling are some of the best ways to identify bugs in code.

## Refactoring: Extract Function

- I am writing the answers to the comments here since during refactoring I probably messed them up.

- buffer is better named
- read_args can remove all the conditions here and just use a ternary message also there should be a default message, this all helps in reducing unnecessary copying also optimization levels like `-O2` will inline it so it only helps more.
- `start_listening_on_socket` can be named as `setup_server_socket()` since the function also sets socket options and binds the address, not just starts listening.

- What is different in this code compared to exercise-1?
- Answer: Compared to exercise 1, this code was more modular and split logic into smaller helper functions for socket creation, binding, listening and handling connections. It also introduced a more structured server flow instead of putting everything inside `main()`.

- Is this code better or worse than exercise-1?
- Answer: It was better in terms of readability and separation of stuff since the logic was divided into functions, but it still had several correctness and robustness issues related to networking and memory handling (they both had it from the start).

- What are the tradeoffs compared to exercise-1?
- Answer: The modular structure made the code easier to understand and extend, but it also introduced more complexity which made debugging slightly harder compared to the smaller exercise 1 version.

- Are you able to spot any mistakes or inconsistencies in the changes?
- Answer: `read_args()` default message was not being used, `set_socket_options()` returning `bool` felt useless since we never really used the return meaningfully and `handle_connections()` inconsistently recreated the address instead of using the one already made in `main()`.  

## Thinking About Performance

- Does writing code this way have any impact on performance?
- Answer: Yes, extra abstractions like helper functions, `std::optional`, repeated string operations etc. can add some overhead, but modern compilers optimize a lot of this especially with optimization flags like `-O2`/`-O3`. Usually the safety and maintainability benefits are worth it unless they becomes a significant bottleneck.

- What do we mean when we say performance?
- Answer: Performance usually refers to how efficiently a program uses time and resources like CPU, memory, disk or network. Most commonly people mean how fast the program runs.

- How do we measure performance in a program?
- Answer: We can measure performance using benchmarks, profiling tools and metrics like execution time, memory usage, latency, etc.

## Play with Git

- There isn't necessarily a single correct answer for how to abstract the  code from exercise-1 into functions
- Try different ways to refactor the code from exercise-1 to make it more readable.

- I did a mistake here, I am sorry for that. I didn't read this and started refactoring the code on my own without reading later sections. Now that I read it I realized I should've made smaller commits.

- Make sure to commit each change as small and self-contained commit
- This will make it easier to revert your code if you need to

- What is `git tag`? How is `git tag` different from `git branch`?
- Answer: `git tag` basically marks a specific commit permanently while a branch is movable and keeps changing as new commits are added. Tags are more like checkpoints whereas branches are active lines of work.

- How can you use `git tag` and `git branch` to make programming easier and more fun?
- Answer: Branches make it easy to experiment with features/fixes without breaking the main codebase, while tags are useful for saving stable milestones (just how you save tactically in games) so you can always go back and compare progress later.
=======
- What can you do to identify if there are bugs in the code?

## Refactoring: Extract Function

- What is different in this code compared to exercise-1?
- Is this code better or worse than exercise-1?
- What are the tradeoffs compared to exercise-1?
- Are you able to spot any mistakes or inconsistencies in the changes?
  
## Thinking About Performance

- Does writing code this way have any impact on performance?
- What do we mean when we say performance?
- How do we measure performance in a program?

## Play with Git

- There isn't necessarily a single correct answer for how to abstract the 
  code from exercise-1 into functions
- Try different ways to refactor the code from exercise-1 to make it more
  readable.
- Make sure to commit each change as small and self-contained commit
- This will make it easier to revert your code if you need to
- What is `git tag`? How is `git tag` different from `git branch`?
- How can you use `git tag` and `git branch` to make programming easier and
  more fun?
>>>>>>> upstream/main

## Learn Basics of Debugging in Your IDE

- How do you enable debug mode in your IDE?
<<<<<<< HEAD
- Answer: In vs code you can open the Run and Debug panel (`Ctrl + Shift + D`) and either press `F5` or create a `launch.json` configuration to start debugging.

- In debug mode, how do you add a watch?
- Answer: While debugging, VS Code has a "Watch" section in the debug sidebar where you can add variables/expressions you want to continuously monitor.

- In debug mode, how do you add a breakpoint?
- Answer: You can click on the left side of a line number to toggle a breakpoint on that line.

- In debug mode, how do you step through code?
- Answer: vs code provides controls like Step Over (`F10`), Step Into (`F11`), Step Out (`Shift + F11`) and Continue (`F5`) to move through the code while debugging.
=======
- In debug mode, how do you add a watch?
- In debug mode, how do you add a breakpoint?
- In debug mode, how do you step through code?
>>>>>>> upstream/main

### Memory Management and Debug Mode in Your IDE

- How do you see the memory layout of a `std::string` from your IDE debug mode?
<<<<<<< HEAD
- Answer: In VS Code debug mode I can put a breakpoint, expand the `std::string` variable inside the Variables panel and inspect its internal fields like `_M_local_buf`, `_M_dataplus`, `_M_string_length`, etc.. I can also use watches/debug console expressions like `message.c_str()` to inspect the raw character buffer and observe things like Small String Optimization (SSO).

- How do you see the memory layout of a struct from your IDE debug mode?
- Answer: In VS Code debug mode I can put a breakpoint and expand the struct variable inside the Variables panel to inspect all its fields and nested members. I can also use watch with pointers like `&my_struct` to inspect raw memory more directly if needed.
=======
- How do you see the memory layout of a struct from your IDE debug mode?
>>>>>>> upstream/main
