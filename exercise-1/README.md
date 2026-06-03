# Exercise 1

**Update this README with your answers to the questions below.**

## How to Approach This Exercise

Before you scroll down to the questions, try this:

1. **Don't peek at the questions yet.** Pretend you've just been handed a brief
   that says: *"Learn these topics as deeply as you can — g++ CLI, Make, Git,
   sockets, and memory management in C++."* That's the whole assignment.
   How would you go about it? What would you read, what would you try, in what
   order, and how would you know when you've understood something well enough?
   Write that plan down in this README, then actually follow it.

2. **Now go through the questions below and answer them like you're an LLM.**
   No live Googling, no Stack Overflow, no asking ChatGPT mid-question. You may
   refer to notes *you* took during step 1 — that's your context window. Answer
   from what you've internalised.

3. **Reflect on how it went.** Honestly:
   - Did your self-directed learning actually prepare you for the questions, or
     did you over-study things that never came up?
<<<<<<< HEAD
   - Answer: For most of the things here, I already knew them since I did a compiler design course so I knew about makefiles, g++ CLI, about networks stuff, I read beej's guide to network programming and it turned out to be good enough, I also saw some helpful websites (like geeks for geeks) and medium blogs. It turned out to be pretty good! I wasn't over prepared neither under prepared, it was more like I understood the internals, now yes I will try to think intuitively according to the internals and try to answer according to them.

   - Which questions blindsided you? Why — was the topic missing from your
     plan, or did you skim past it?
   - Answer: Thankfully nothing here :), I have done enough mistakes in my past that I mindfully try to grasp anything I do and it turned out to be a pretty good attempt here.

=======
   - Which questions blindsided you? Why — was the topic missing from your
     plan, or did you skim past it?
>>>>>>> upstream/main
   - Map your experience onto the *known knowns / known unknowns / unknown
     unknowns* idea. The interesting category is usually the last one: things
     you didn't even realise you should have learned. What were yours, and how
     could a better learning plan have surfaced them earlier?
<<<<<<< HEAD
   - Answer: Half of the things I know actually origin from the last category (not the stuff asked here!). From multi-agent systems, llm security, functional programming, a bit of hardware verification stuff and I believe its better to just dive deep for some time into a rabbit hole but the important part is coming back. Fortunately here whatever I read (from the resources mentioned above) and knew previously from all my coursework was enough. 
=======
>>>>>>> upstream/main

The point of this exercise isn't to get the questions "right" — it's to notice
the gap between how you *think* you learn and how you actually do, so you can
close it.

## Learning How to Learn

- Answer the following questions in this file and commit and push your changes.
- Bonus sections are more difficult and optional.
- How can you find the information required to complete these tasks?
<<<<<<< HEAD
- Answer: First of all see all the reading material on the provided notion page and read them according to their similarity scores! Then googling always helps, you'll always find something helpful there and now that ai mode does really good web scraping and summarizing you can rely on it, reddit is a really good platform when you need to find actual useful resources (ironically it is). 

- How can you tell if the source of your information is good?
- Answer: I think reliability of source is one of the first things to check. After that, practical verification matters a lot to me, if the concepts from the source actually match the behavior I observe while experimenting, it is usually a good sign. Good sources also explain why something works instead of just giving steps to copy paste. Comparing multiple sources and checking official docs also helps verify correctness.

- How would you define "good" in this situation?
- Answer: In this situation I would define a good source as something that is reliable, technically correct, practically verifiable and explains the reasoning behind concepts instead of just giving instructions to follow blindly.
=======
- How can you tell if the source of your information is good?
- How would you define "good" in this situation?
>>>>>>> upstream/main

## Learn Basics of g++ CLI

- Compile the TCP client and server using `g++` from command line.
<<<<<<< HEAD
- Answer: Compiled through g++ -Wall -g /src/tcp_echo_client.cc -o /build/client
  
- What are the most important command line arguments to learn for `g++`?
- Answer: The flags and knowing what each of them does is super important to understand. Including the c++ version you are using is important as well (since the default version of your compiler might not be the one you intend to use), say if you are using c++ 20 - `-std=c++20`. For example `-Wall -Wextra` can help you show clearer warning which is really helpful in debugging and finding places where code could go wrong. Sanitizers like `-fsanitize=address` and `-fsanitize=undefined` are extremely useful during debugging. Address Sanitizer helps detect memory-related bugs such as buffer overflows and use after free errors, while UB Sanitizer helps catch undefined behavior like integer overflows, invalid shifts and other dangerous runtime issues. The optimization levels like `O0` `O1` `O3` and when to use what and since there are tradeoffs to each one of them and not naively using `O3` every time! (Optimization is a NP hard problem so you got to use some heuristics which aren't always useful!). `-g` helps with including symbols for debugging tools like gdb, etc..
  
- What is the difference between debug vs release versions?
- Answer: In debug version our main focus is debugging, diagonistics and correctness of the program. We might not want to include compiler optimizations here since they do reorder instructions and as a result we might not be able to model behavior of certain variables which is crucial for debugging. In a release build our main focus is performance now that we have tested everything and we are sure of stuff, but wait there's a catch! There can still be a few bugs, so we might want to use `-g`, so that if a user faces a bug in a certain situation (which we clearly weren't able to model in test!), we can use those symbol informations for debugging using various debugging tools.
  
- What are the tradeoffs between debug and release versions?
- Answer: I would say the main tradeoff between them is debuggable-ity and performance. Debug builds are designed to help with developement/debugging without optimizations, enabling assertions and tracking/diagonising symbols/variables which makes it easier to track program state and variables but this also makes the program slower in comparison. Release builds on the other hand focus on performance and efficiency by enabling compiler optimizations (like `O2` or `O3` depending on the use case) and removing and debugging harnesses we had earlier resulting in smaller binary executables. The downside is that release builds this way get really harder to debug since optimization may reorder instructions, inline functions, etc. which make it harder to trace program behavior (because our mental model of the program and what is being executed clearly becomes way different!).
  
- What arguments would you use in a debug build?
- Answer:  `-Wall -Wextra`, `-g`, `-fsanitize=address`, `-O0` as explained earlier that they do the work which is crucial for debugging. Also include the version of c++ you are using for example `-std=c++20`.

- What about for release?
- Answer: We might use optimizations flags like `-O2` or `-O3` depending on the use case, and `-DNDEBUG` which disables debug assertions. Even though release builds are optimized, sometimes we may still include `-g` so that if users encounter bugs in production, we still have symbol information available for profiling and debugging tools.

- What other kinds of build types are useful?
- Answer: Except these builds, there are several builds that are used. For example RelWithDebInfo is commonly used because it combines optimizations (-O2) with debug symbols (-g) which helps in profiling and debugging performance issues in near production environments. Sanitizer builds using flags like `-fsanitize=address` and `-fsanitize=undefined` are extremely useful for detecting memory corruption, invalid accesses and undefined behavior during development. Coverage builds using `--coverage` help measure how much of the codebase is actually being tested. There are also profiling builds which are compiled specifically for performance analysis tools like gprof or perf.
=======
- What are the most important command line arguments to learn for `g++`?
- What is the difference between debug vs release versions?
- What are the tradeoffs between debug and release versions?
- What arguments would you use in a debug build?
- What about for release?
- What other kinds of build types are useful?
>>>>>>> upstream/main

## Learn Basics of Make

- Create a Makefile that will speed up the process.
- [Quickstart tutorial to make](https://makefiletutorial.com/) - Learn make 
  fundamentals with practical examples and common patterns.
- How else can you learn about make?
<<<<<<< HEAD
- Answer: Googling docs/tutorials is always a good way to start, but I personally think the best way to learn make is by actually using it in projects. I had previously used it in compiler assignments and small systems projects which helped me understand dependencies, targets and rebuild logic much better than just reading theory. Reading existing Makefiles, experimenting with small examples and using commands like make -n also helps a lot. 
  
- How can you tell if the resource you are using is correct?
- Answer: I think first comes reliability of source, thats an important thing to look for. After this I believe the best way is to verify things practically rather following tutorials blindly. If the concepts explained in the resource actually match the behavior you observe while experimenting, then it is usually a good sign. Good resources also explain why something works instead of just giving commands to copy paste. Referring to official documentation/man pages and comparing multiple sources also helps avoid misinformation. These are the ways I prefer using to verify if the resource I am using is of good quality or not.

=======
- How can you tell if the resource you are using is correct?
>>>>>>> upstream/main
- Create a makefile such that when you run `make` with no arguments, it will:
  - Create `build/` directory if it does not exist
  - Create executables **client** and **server** in `build/`, if needed
  - How does make know when it needs to rebuild the executables?
<<<<<<< HEAD
  - Answer: make mainly uses timestamps of files to decide whether something needs to be rebuilt or not. If a dependency/source file is newer than the target executable, make understands that the executable is outdated and recompiles it. Otherwise it skips rebuilding which helps make builds much faster.
    
  - Change your Makefile such that `make clean` will remove `build/` and all
    its contents
- What are the most important command line arguments to learn for make?
- Answer: Commands like make -j are good to know since they allow parallel builds and speed up compilation. That is very useful for large projects/codebases. make -n is useful for debugging Makefiles since it shows what commands would run without actually executing them. make clean is commonly used to remove generated build files and force a fresh rebuild. make -B can also be useful when we want to rebuild everything regardless of timestamps/dependencies.
  
- What are the most important directives to learn about in Makefile?
- Answer: Understanding targets, dependencies and variables is probably the most important thing in make. Directives like .PHONY are useful because they tell make that a target is not an actual file. Pattern rules are also super useful since they help avoid repetitive compilation rules. Automatic variables like `$@` and `$<` are also really important because they help us abstract rules in a cleaner way.
  
- What are the most important commands to implement in your Makefile?
- Answer: Commands like all and clean are definitely the most important ones. all is usually the default target and builds everything required while clean removes generated build files for fresh rebuilds. Commands like debug, release, run or test are useful as per the use case.
  
- Which ones are essential, which ones are nice to haves?
- Answer: Targets, dependencies, variables and commands like all and clean are essential because they are the main purpose of makefiles. Pattern rules, automatic variables, parallel builds and other commands are more like nice to haves initially, but they become really useful as projects become more complex.
  
=======
  - Change your Makefile such that `make clean` will remove `build/` and all
    its contents
- What are the most important command line arguments to learn for make?
- What are the most important directives to learn about in Makefile?
- What are the most important commands to implement in your Makefile?
- Which ones are essential, which ones are nice to haves?

>>>>>>> upstream/main
## Learn Basics of Git

- Read through the code in `src/`
- Answer any `#Questions` as a comment
- Commit and push your changes to git
- Each commit should be responding to a single task or question
- Why is it important to keep your commit to a single task or question?
<<<<<<< HEAD
- Answer: Keeping commits to a single task keeps history cleaner and makes debugging, reviewing and reverting changes much easier. If something breaks, it becomes easier to identify which commit caused the issue.
  
- Is it better to have a lot of very small commits, or one big commit when everything is working?
- Answer: Smaller meaningful commits are usually much better than one huge commit because they are easier to debug and review although that doesn't mean to make commits super tiny, they should be kind of logically grouped and there should not be large leaps of logic between them.
  
- What are the most important commands to know in git?
- Answer: Commands like `git status`, `git add`, `git commit`, `git push` and `git pull` are the staple of git commands. `git diff` and `git log` are useful for inspecting changes. `git branch`, `git merge` and `git rebase` help manage branches and commits.
=======
- Is it better to have a lot of very small commits, or one big commit when 
  everything is working?
- What are the most important commands to know in git?
>>>>>>> upstream/main

## Introduction to Sockets

- Read the code in `src/tcp-echo-client.cc` and add a way to change the 
  message sent using command line arguments
- **Example**: `./client "hello message from the command prompt"` should send
  `"hello message from the command prompt"` to the server
- Commit your changes into git
- What do all these headers do?
<<<<<<< HEAD
- Answer: `<iostream>` provides stream objects like `cout` and `cin` (also `cerr`), `<string>` provides `std::string`, `<sys/socket.h>` contains socket API like `socket`, `connect`, `send`, `bind`, etc.. `<arpa/inet.h>` provides methods related to IP address conversion like `inet_pton` and byte order conversions. `<netinet/in.h>` provides structs like `sockaddr_in`. `<unistd.h>` provides system calls like `close`, `read`, `write`, etc.. `<sys/types.h>` gives types used by many system calls.
  
- How do you find out which part of the below code comes from which header?
- Answer: I do this by either checking docs/man pages or using IDE features (vs code provides such a feature). For example `man inet_pton` tells us which header defines the function/type/class/etc.. If you miss a header by chance, your compiler is always there to help you as they often hint at missing headers.
  
- How do you change the code so that you are sending messages to servers other than localhost?
- Answer: We can do that by changing the variable `kServerAddress` from `127.0.0.1` to the server's ip address you want to connect to (you can also just add a command line arguement for it by supporting -
```cpp
if(argc > 2){
   kServerAddress = argv[2];
}
```

- How do you change the code to send to a IPv6 address instead of IPv4?
- Answer: First of all you need to change `AF_INET` to `AF_INET6`, `struct sockaddr_in` to `struct sockaddr_in6`, `sin_addr` to `sin6_addr`, `sin_port` to `sin6_port`. IPv6 address are 128 bit so seperate structs/APIs are used for them.
  
- **Bonus**: How do you change the client code to connect by hostname instead
  of IP address?
- Answer: (Answering as per I read in beej's guide) When we don't have an IP address we can use `getaddrinfo()` which resolves hostname into socket address structures (it provides a linked list on addresses). Through which we can iterate and try to connect. 
=======
- How do you find out which part of the below code comes from which header?
- How do you change the code so that you are sending messages to servers
  other than localhost?
- How do you change the code to send to a IPv6 address instead of IPv4?
- **Bonus**: How do you change the client code to connect by hostname instead
  of IP address?
>>>>>>> upstream/main
  
## Introduction to Memory Management

- What is happening in line 26 of `tcp-echo-client.cc`? 
  `if (inet_pton(AF_INET, kServerAddress.c_str(), &address.sin_addr) <= 0) {`
<<<<<<< HEAD
- Answer: We are basically converting the readable IP address format into binary format that the networking API will understand using the function `inet_pton`, `AF_INET` just tells that its a IPv4 address, `kserverAddress.c_str()` converts the `std::string` into a classic c style string and `&address.sin_addr` provides the memory location where the converted IP address will be stored. If `inet_pton` returns `0` or `-1`, the conversion basically failed.
  
- What is happening in line 31 of `tcp-echo-client.cc`?
  `if (connect(my_sock, (sockaddr *)&address, sizeof(address)) < 0) {`
- Answer: Here we are basically asking the OS to connect the socket to a remote server specified by `address` using the `connect` system call. `(sockaddr *)&address` casts the IPv4 socket struct into a generic socket struct because `connect` has to work with multiple socket types. `sizeof(address)` tells the OS the size of the structure being passed. If the return value is `< 0`, the connection basically failed.
    
- What is the difference between a pointer and a reference?
- Answer: A pointer stores the memory address of another object and can be reassigned, be `nullptr` and support pointer arithmetic. A reference on the other hand is just an alias to another object and cannot be reseated or null. Internally a reference may behave somewhat like a constant pointer (`int *const ri = &i`). References are generally cleaner/safer while pointers are more flexible.
  
- When is it better to use a pointer?
- Answer: Pointers are useful when an object may or may not exist (`nullptr`), when working with dynamic memory/low level memory or when working with C APIs (like we do in this exercise) and data structures like linked lists and trees.
  
- When is it better to use a reference?
- Answer: References are better when an object must always exist and we simply want to alias/pass it around without copying. They are generally cleaner and safer than pointers since they cannot be null or reseated. They are heavily used in operator overloading/other functions to avoid unneccessary copying.
  
- What is the difference between `std::string` and a C-style string?
- Answer: `std::string` is a proper C++ class which manages memory automatically and provides useful operations like concatenation, resizing, etc.. A C-style string is just a null terminated character array and is more low level but it is error prone as well.
  
- What type is a C-style string?
  
- Its usually represented as `char *` or `const char *` if you want a const c style string.

- What happens when you iterate a pointer?
- Answer: Iterating a pointer moves it forward in memory according to the size of the type it points to. For example incrementing an `int*` moves it by `sizeof(int)` bytes.
  
- What are the most important safety tips to know when using pointers?
- We should initialize them properly and avoid dereferencing invalid/null pointers. Also we should be careful about dangling pointers and out of bound memory access.
=======
- What is happening in line 31 of `tcp-echo-client.cc`?
  `if (connect(my_sock, (sockaddr *)&address, sizeof(address)) < 0) {`
- What is the difference between a pointer and a reference?
- When is it better to use a pointer?
- When is it better to use a reference?
- What is the difference between `std::string` and a C-style string?
- What type is a C-style string?
- What happens when you iterate a pointer?
- What are the most important safety tips to know when using pointers?
>>>>>>> upstream/main

## Learn Basics of Creating a C++ Project in Your IDE

- How do you compile and run your project in your IDE?
<<<<<<< HEAD
- Answer: In VS Code for smaller projects we can directly compile and run files using terminal commands/tasks like `g++ main.cc -o main && ./main` or the command for the language you are using. For larger projects it is usually better to use build systems like `make` or `cmake` and configure VS Code debugger around them.
=======
>>>>>>> upstream/main

## Improving Interactions with LLMs

- What is the most authoritative source of information about `socket()`
  from `<sys/socket.h>`?
<<<<<<< HEAD
- Answer: The man pages (`man socket`) are usually the most authoritative/practical source for understanding `socket()` and related APIs.

- What is the most authoritative source of information about the TCP and IP
  protocols?
- Answer: RFC document published by IETF are the most authoritative source for TCP/IP.
  
- What is the most authoritative source of information about the C++
  programming language?
- Answer: ISO C++ standard is the official authoritative source, while references like cppreference are practical resources.
  
- What information can you find about using Markdown when structuring prompts 
  to LLMs?
- Answer: Markdown helps structure prompts more clearly using headings, lists, code blocks, etc., making instructions easier for both humans and LLMs to parse.
  
- What is the difference between LLM and AI?
- Answer: AI is a subfield of CS whose main idea is to build systems that can simulate intelligent behavior, while an LLM (Large Language Model) is a specific type of AI focused on understanding/generating language.
  
- Is it grammatically correct in English to say "a LLM" or "an LLM"? Why?
- an LLM in my opinion since you pronounce it like (el el m), just how you call an umbrella.
=======
- What is the most authoritative source of information about the TCP and IP
  protocols?
- What is the most authoritative source of information about the C++
  programming language?
- What information can you find about using Markdown when structuring prompts 
  to LLMs?
- What is the difference between LLM and AI?
- Is it grammatically correct in English to say "a LLM" or "an LLM"? Why?
>>>>>>> upstream/main
