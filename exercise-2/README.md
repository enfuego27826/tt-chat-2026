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

## Introduction to C++ and Sockets Programming

- Read the code in `src/`
- Are there any bugs in this code? 
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

## Learn Basics of Debugging in Your IDE

- How do you enable debug mode in your IDE?
- In debug mode, how do you add a watch?
- In debug mode, how do you add a breakpoint?
- In debug mode, how do you step through code?

### Memory Management and Debug Mode in Your IDE

- How do you see the memory layout of a `std::string` from your IDE debug mode?
- How do you see the memory layout of a struct from your IDE debug mode?