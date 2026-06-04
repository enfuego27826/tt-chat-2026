# Exercise 3

**Update this README with your answers to the questions below.**

## Re-using Code

- Read the code in `src/tcp_echo_client.cc`
- A new function `check_error()` has been created and `create_socket()` from 
  exercise-2 has been refactored to make use of it
- What are the benefits of writing code in this way?
- Are there any costs to writing code like this?
- Apply `check_error` to all the code in `src/`

## Introduction to Compiler Explorer

- Try out the old `create_socket()` and the new `check_error()` and 
  `create_socket()` in [Compiler Explorer](https://godbolt.org) - Interactive 
  tool for exploring how C++ code compiles to assembly
- What is happening here?

Answer: so since we are passing the arguement as a string to `check_error()`, a temporary std::string object has to be passed for that we have to do heap allocation for the string etc. etc., which causes a few more instructions mentioned below - 

```asm
mov     edi, 23
mov     ebx, eax
call    "operator new(unsigned long)"
movdqa  xmm0, XMMWORD PTR .LC1[rip]
movabs  rcx, 752786625060479086
mov     QWORD PTR [rsp+16], 22
mov     QWORD PTR [rsp], rax
movups  XMMWORD PTR [rax], xmm0
mov     BYTE PTR [rax+22], 0
mov     QWORD PTR [rax+14], rcx
mov     QWORD PTR [rsp+8], 22
```
Which is the typical abstraction overhead problem. Everything else is pretty much the same except that the destructor of the string is also called at the end of scope. 

- Can you think of any different approaches to this problem?

Answer: Either use `std::optional` and leave the whole error handling to the caller or use `const char*` or `std::string_view` as an arguement for `check_error()`, which allows the message to be passed as a string literal so we don't need a temporary string object and no allocation.

- How can you modify your Makefile to generate assembly code instead of
  compiled code?

Answer: add the following lines - 

```
asm: $(ASM_TARGETS)

$(BUILD_DIR)/%.s: $(SRC_DIR)/tcp_echo_%.cc | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -S $< -o $@
```

-S is a compiler flag which tells it to compile the code into assembly and stop there.


- **Note**: You can save the generated assembly from Compiler Explorer
- **Bonus**: Can you view assembly code using your IDE?

Answer: Yes, you can either get the compiler explorer extension or watch the disassembly view through the vs code debugger however for it, i would prefer compiler explorer (the extension in vs code) since its more convenient and easier to use.

- **Bonus**: How do you see the assembly when you step through each line in
  debugging mode from your IDE?

Answer: while debugging, i can open disassembly view in vs code. after starting a debug session and pausing at a breakpoint, i use the command paletter and select open disassembly view or you can right click into the call stack (wtv function you want to see) and open disassembly, and as i step through the program, the highlighted assembly updates to show the code being executed.

- [x86 assembly reference](http://ref.x86asm.net/) - Comprehensive reference 
  for x86 assembly language instructions and syntax

## More About Memory Management

- Make sure you have `-fsanitize=address` in both your `CXX_FLAGS` and 
  `LD_FLAGS` in your Makefile
- What do `-fsanitize=address`, `CXX_FLAGS` and `LD_FLAGS` mean?
- With the new tool of the Compiler Explorer, and keeping in mind what you 
  have learned about how to use debug mode
- What happens when you look at a `std::string` using the above methods?

Answer: We have talked about using debug mode in earlier exercises, in compiler explorer i have attached the snippet above. looking at it, we can see that the std::string object contains metadata for other stuff as well, like pointer to the char buffer, current size and capacity. 

- Where is the text in your `std::string`?

Answer: for small strings, the text is usually stored directly inside the std::string object using SSO. for larger strings, the text is stored on the heap and the string obj contains the pointer to that buffer.

- What is `std::optional`?

Answer: it is a way to represent a value that may or may not exist.

- How do you find out the memory layout of a `std::optional`?

Answer: I used compiler explorer for this since we have played around with debug mode a lot in previous few exercises. Here's the output for the given code - 

```cpp
std::optional<int> opx = 42;
```

```asm
mov     QWORD PTR [rbp-8], 0
mov     DWORD PTR [rbp-8], 42
mov     BYTE PTR [rbp-4], 1
```

As you can see, to initialize the object it first resets the whole memory to 0 (it takes around 16 bytes here -> 4 integer + 1 bool + 3 padding). Then it stores the integer at `[rbp-8]` and the bool at `[rbp-4]`, the bool represent whether the value exists or not, proof for it is below - 

```cpp
std::optional<int> lsx = std::nullopt;
```

```asm
mov     QWORD PTR [rbp-8], 0
```

as you can see here it just initialized the whole memory, did nothing else. so that bool actually represents whether the value exists or not.

- Read https://en.cppreference.com/w/cpp/memory#Smart_pointers - Guide to 
  modern C++ memory management using smart pointers
- Which pointer types are the most important to know about?

Answer: unique_ptr, shared_ptr, weak_ptr

- Which smart pointer should you use by default if you can?

Answer: if possible use unique_ptr, i think scott myer's book has an entire item explaining why its good, but ill be concise here. it has the lowest overhead (its pretty similar to a raw pointer only), ownership is explicit and makes ownership relation clear, if else you require using something that is not an unique_ptr, you can go ahead with shared_ptr but it has its fair amount of overhead you might have to consider (its double the memory since two pointers need to be mantained, one to the object and one to the control block) and then ref count incremention is slower since its atomic.

- Does changing your optimization level in `CXXFLAGS` from `-O0` to `-O3` have
  any impact on the answers to any of the above questions?

Answer: yes, changing the optimization level can change generated assembly and the memory management code but the fundamentals don't change, a string will still store text using sso or on heap, optional will still store a value together with a bool flag. optimization mainly changes how these things are implemented in the generated code. 

## More Thinking About Performance

- After your experiments with Compiler Explorer, do you have any updates for
  your answers in exercise-2?

### Bonus: Do Not Watch Now 

- [More about Compiler Explorer](https://www.youtube.com/watch?v=bSkpMdDe4g4) - 
  Deep dive into compiler optimization and assembly analysis
  - Create a struct which contain many different data types
  - Look at the memory layout in the debugger
  - Create a `char` or `uint8_t` pointer to the beginning of the struct, 
    iterate to the end of the struct, printing out the value of each byte in 
    hexadecimal

Answer: I ran this code - 

```cpp
#include<bits/stdc++.h>

struct Foo{
    int x;
    char y;
    bool z;
    uint64_t l;
    
    Foo(int x, char y, bool z, uint64_t l): x(x), y(y), z(z), l(l) {}
};

int main(){
    Foo a(5,'c',true,(uint64_t)1203);

    auto* x = reinterpret_cast<const uint8_t*>(&a);

    for(int i = 0; i < sizeof(Foo); ++i){
        std::cout << std::hex << std::setw(2) << std::setfill('0')
                  << static_cast<int>(x[i])
                  << ' ';    }
}
```

Which outputs - 

```bash
05 00 00 00 63 01 00 00 b3 04 00 00 00 00 00 00 
```

  - Try accessing different parts of the struct and see in compiler explorer
    what the assembly looks like

Answer: For this code - 

```cpp
#include<bits/stdc++.h>

struct Foo{
    int x;
    char y;
    bool z;
    uint64_t l;
    
    Foo(int x, char y, bool z, uint64_t l): x(x), y(y), z(z), l(l) {}
};

int main(){
    Foo x(4,'c',true,(uint64_t)432);
}
```

```asm
"Foo::Foo(int, char, bool, unsigned long)":
        push    rbp
        mov     rbp, rsp
        mov     QWORD PTR [rbp-8], rdi
        mov     DWORD PTR [rbp-12], esi
        mov     BYTE PTR [rbp-13], dl
        mov     BYTE PTR [rbp-14], cl
        mov     QWORD PTR [rbp-24], r8
        mov     rax, QWORD PTR [rbp-8]
        mov     edx, DWORD PTR [rbp-12]
        mov     DWORD PTR [rax], edx
        mov     rax, QWORD PTR [rbp-8]
        movzx   edx, BYTE PTR [rbp-13]
        mov     BYTE PTR [rax+4], dl
        mov     rax, QWORD PTR [rbp-8]
        movzx   edx, BYTE PTR [rbp-14]
        mov     BYTE PTR [rax+5], dl
        mov     rax, QWORD PTR [rbp-8]
        mov     rdx, QWORD PTR [rbp-24]
        mov     QWORD PTR [rax+8], rdx
        nop
        pop     rbp
        ret
        .set    "Foo::Foo(int, char, bool, unsigned long)","Foo::Foo(int, char, bool, unsigned long)"
"main":
        push    rbp
        mov     rbp, rsp
        sub     rsp, 16
        lea     rax, [rbp-16]
        mov     r8d, 432
        mov     ecx, 1
        mov     edx, 99
        mov     esi, 4
        mov     rdi, rax
        call    "Foo::Foo(int, char, bool, unsigned long)"
        mov     eax, 0
        leave
        ret
```

As you can see there's struct padding and the whole struct takes up 16 bytes.

  - What happens if you iterate the pointer to outside the bounds of your
    array?

Answer: Undefined behavior, can be garbage values, segmentation fault or you can access corrupted memory.

  - Let's say your struct is called `Foo`
  - What is the difference between `std::vector<Foo>` and `std::vector<Foo*>`?

Answer: One holds the objects in the vector and the other one holds the pointer to the heap allocated objects.

  - What are the tradeoffs between using `std::vector<Foo>` vs 
    `std::vector<Foo*>`? 

Answer: Although the first one offers better cache locality, automatic lifetime management, no dangling pointers and avoids pointer chasing but the second one has its fair share of benefits as well, it supports polymorphism and when the vector has to resize beyond its current capacity, we end up moving lesser stuff and its faster (for a bigger Foo). worse cache locality, object lifetime management, risk of leaking stuff -> cons of `vector<Foo*>`

  - Give an example where `std::vector<Foo>` is a better choice than 
    `std::vector<Foo*>`

Answer: suppose we have a small struct which has like two integers and we have a lot of those structs inside the vector and we need to loop through them all for an event, then its really useful since they are stored contigiously and are cache friendly, also the struct is small so move cost isn't too much in the event of resizing the vector.

  - Give another example where the opposite is true

Answer: when you want polymorphism or the move cost to be not too expensive.

  - Can you create `std::vector<Foo&>`? 

Answer: no, references is cpp are not assignable and movable, while vector requires elements to be movable and assignable.

  - Can you create `std::vector<std::optional<Foo>>`?

Answer: yes

  - What happens if your struct contains another struct?

Answer: the inner struct is stored directly inside the outer struct as a subobject

  - What is the difference between a struct and a class?

Answer: struct is just class with all members/functions being public.