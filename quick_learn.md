### 1\. C Language Fundamentals

-----

#### Return both an `int` and a `char*` from a function

Since a function can only have one return value, you must use a **struct** to group the different data types you want to return.

```c
#include <stdio.h>
#include <stdlib.h>

struct both {
    int a;
    char *p;
};

// Return a pointer to a struct
struct both* get_int_string() {
    // Allocate memory on the heap to avoid a dangling pointer
    struct both* new = (struct both*)malloc(sizeof(struct both));
    if (new == NULL) {
        // Handle memory allocation failure
        return NULL;
    }
    new->a = 5;
    // Pointers can be returned as they point to a stable location
    new->p = "asdasf";
    return new;
}
```

-----

#### Declare a function pointer which returns an `int` array and accepts a `struct` pointer

In C, a function cannot directly return a dynamically sized array. You should return a pointer to the array's first element.

```c
#include <stdio.h>
#include <stdlib.h>

struct both {
    int a;
    char *p;
};

// The function being pointed to
int* returns_array(struct both *ap) {
    // Allocate memory for the array on the heap
    int* n = (int*)malloc(sizeof(int) * 2);
    if (n == NULL) {
        return NULL;
    }
    n[0] = ap->a;
    n[1] = ap->a + 5;
    return n;
}

// Declaration of the function pointer
int* (*func_ptr_returns_array)(struct both*);

int main() {
    func_ptr_returns_array = &returns_array;

    struct both my_struct = { .a = 10 };
    int* result = func_ptr_returns_array(&my_struct);

    printf("Array elements: %d, %d\n", result[0], result[1]);
    free(result); // Free the allocated memory
    return 0;
}
```

-----

#### Difference between a `static` variable inside and outside a function

  * **Static variable inside a function:** Its **scope** is local to the function, but its **lifetime** is for the entire program. The variable is created only once on the data segment and retains its value between function calls. It cannot be accessed from outside the function.
  * **Static variable outside a function (global scope):** Its **scope** is limited to the file it's declared in (file scope). It is not visible to other files, preventing naming conflicts. Its **lifetime** is also for the entire program.

-----

#### Can you return the address of a static variable?

Yes, you can. A `static` variable's lifetime is for the entire program, so the address remains valid even after the function that declared it returns. Returning the address of a local, non-static variable would be a dangling pointer, as its memory is on the stack and would be deallocated.

-----

#### What is `volatile`? Where is it used?

The `volatile` keyword is a type qualifier that tells the compiler that a variable's value can be changed by something outside of the program's control. This prevents the compiler from performing certain optimizations that would be incorrect for such a variable.

It's used in scenarios where a variable can be modified by:

  * An **interrupt service routine (ISR)**.
  * Another **thread** in a multi-threaded program.
  * Memory-mapped hardware registers (common in embedded systems and device drivers).

-----

#### How does `free` know how many bytes to free?

The `malloc` family of functions stores metadata about the allocated memory block just before the returned pointer. This metadata typically includes the size of the block. When you call `free` with the pointer, it looks at this metadata to determine the size of the block to be freed.

-----

#### Allocate memory for a two-dimensional array using `malloc`

You can allocate a 2D array by using a pointer to a pointer.

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int rows = 3;
    int cols = 4;

    // Allocate memory for 'rows' number of pointers
    int **arr = (int **)malloc(rows * sizeof(int *));
    if (arr == NULL) { return 1; }

    // For each row, allocate memory for 'cols' number of integers
    for (int i = 0; i < rows; i++) {
        arr[i] = (int *)malloc(cols * sizeof(int));
        if (arr[i] == NULL) {
            // Error handling for allocation failure
            return 1;
        }
    }

    // Access and fill the array
    arr[1][2] = 100;
    printf("Value at arr[1][2]: %d\n", arr[1][2]);

    // Free the memory
    for (int i = 0; i < rows; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}
```

-----

#### How do you compile code as a shared object?

You use the `-shared` and `-fPIC` (Position Independent Code) flags with `gcc`.

```bash
# Compile source files to object files
gcc -c -fPIC source1.c source2.c

# Link object files into a shared library
gcc -shared -o libmylibrary.so source1.o source2.o
```

-----

#### What happens when you initialize a function pointer with the address of an `int`?

This is a **compiler error** in modern C standards because you are trying to assign a data pointer to a function pointer. A function pointer's type is fundamentally different from a data pointer's type, and this assignment is not allowed without an explicit typecast.

-----

#### Implement `sizeof` without using pointers

`sizeof` is a compile-time operator. A macro can be used to simulate its behavior for simple data types.

```c
#define getsize(x) ((char *)(&(x) + 1) - (char *)&(x))
```

**Explanation:** `(x) + 1` in pointer arithmetic moves the pointer `(x)` to the memory address immediately after the object. When you cast both pointers to `char*` and subtract them, you get the size in bytes.

-----

### 2\. Data Structures & Algorithms

-----

#### Delete a node without knowing the head of a linked list

This is a classic interview question. The solution is to **copy the data from the next node into the current node**, and then delete the next node.

```c
void delete_node(node* node) {
    if (node == NULL || node->next == NULL) {
        // Cannot delete the last node or a null node with this method
        return;
    }
    // Copy data from the next node to the current node
    node->data = node->next->data;
    node* temp = node->next; // Store address of the node to be deleted
    node->next = node->next->next; // Bypass the node
    free(temp); // Free the memory
}
```

-----

#### How do you find the middle of a linked list?

You can use the **slow and fast pointer** approach. Have two pointers start at the head of the list. Move one pointer (`slow`) one step at a time, and the other (`fast`) two steps at a time. When the `fast` pointer reaches the end of the list, the `slow` pointer will be at the middle.

-----

#### Insert a node into a sorted list

You need to traverse the list to find the correct position to insert the new node.

1.  If the list is empty or the new node's data is smaller than the head's data, insert the new node at the beginning.
2.  Otherwise, iterate through the list until you find a node where the next node's data is greater than or equal to the new node's data.
3.  Insert the new node between the current node and the next one.

-----

#### Write a program to find if a number is a power of 2

A number is a power of 2 if it has only one bit set to `1` in its binary representation. The expression `n & (n - 1)` will clear the lowest set bit. If the result is `0` and `n` is greater than `0`, then `n` is a power of 2.

```c
#include <stdio.h>
#include <stdbool.h>

bool is_power_of_two(int n) {
    if (n <= 0) {
        return false;
    }
    return (n & (n - 1)) == 0;
}
```

-----

#### Write a program to toggle a bit

To toggle a bit at a specific position `p`, you can use the **XOR** operator (`^`) with a bitmask. The bitmask should have `1` at position `p` and `0` everywhere else.

```c
#define TOGGLE_BIT(num, pos) ((num) ^ (1 << (pos)))
```

-----

### 3\. Operating Systems & Processes

-----

#### Difference between `wait`, `waitpid`, and `waitid`

  * **`wait()`:** This is a blocking call that waits for **any** child process to terminate. It returns the PID of the terminated child.
  * **`waitpid()`:** This can wait for a **specific** child process (given by its PID). It can also be made non-blocking by using the `WNOHANG` option, which is a major advantage.
  * **`waitid()`:** This is a more modern, flexible version of `waitpid()`. It allows you to specify which child processes to wait for using an ID type (e.g., PID, process group ID) and provides more detailed information about the child's termination status.

-----

#### How do you maintain private data for each thread?

Each thread has its own **stack**, which contains local variables. To maintain private data that is accessible across different function calls within a single thread, you can use **Thread-Local Storage (TLS)**. In C, you can achieve this using the `__thread` keyword or `pthread_key_create` and `pthread_getspecific` from the Pthreads library.

-----

#### How are traps generated?

A trap is a type of interrupt that occurs in response to a program's instruction. It is generated by the CPU when a specific event occurs, such as:

  * A **system call**, which is a trap into the kernel.
  * An **invalid memory access** (e.g., segmentation fault).
  * A **division by zero**.
  * A **breakpoint** (used in debugging).

-----

#### What happens during a `segfault`?

A segmentation fault (`segfault`) occurs when a program attempts to access a memory location that it is not allowed to access. The memory management unit (MMU) detects this illegal access and generates a fault. This fault is handled by the kernel, which then sends a `SIGSEGV` signal to the process, causing it to terminate.

-----

#### Difference between `mutex` and `semaphore`

  * **Mutex (Mutual Exclusion):** A mutex is a locking mechanism. Only **one thread** can hold the mutex at a time. It is used to protect a critical section of code, ensuring that it is executed by only one thread. A mutex is typically **owned** by the thread that locks it.
  * **Semaphore:** A semaphore is a signaling mechanism. It can be used to control access to a resource with a limited number of instances. It has a counter, and threads can acquire (decrement) or release (increment) the semaphore. A semaphore does not have an owner, meaning one thread can acquire it and another can release it. A binary semaphore is like a mutex, but it lacks ownership.

-----

#### Why are pipes used only between related processes?

Pipes are a form of **Unidirectional** IPC. The file descriptors for the read and write ends of the pipe are created in the parent process. When the parent calls `fork()`, the child process inherits copies of these same file descriptors. This is what allows them to communicate. This is why pipes are limited to processes that share a common ancestor.

-----

#### Is multithreading necessary in a single-core processor? Why?

Yes, multithreading is still necessary and beneficial. The primary advantage of multithreading in a single-core environment is not parallel execution but **concurrency**. Threads can be used to:

  * **Avoid blocking:** While one thread is blocked waiting for an I/O operation, the CPU can switch to another thread to perform useful work.
  * **Improve responsiveness:** In a GUI application, one thread can handle user input while a separate thread performs a long-running task in the background, preventing the application from freezing.

-----

### 4\. Networking & Sockets

-----

#### Can `accept` be called if `listen` fails?

No. The `listen()` call is a prerequisite for `accept()`. It sets the socket in a passive mode, ready to accept incoming connections, and establishes a queue for those connections. Without a successful `listen()` call, the socket is not prepared to handle connection requests, and `accept()` will fail.

-----

#### What is the need for `listen`? Is `accept` not sufficient?

`listen()` is crucial because it performs two key functions:

1.  It tells the OS that the socket is a **server socket** and should be ready to accept connections.
2.  It sets the maximum size of the **pending connection queue**. The queue holds incoming connection requests that have been received but not yet handled by `accept()`.

`accept()`'s role is to dequeue one of these pending connection requests and create a **new socket** for communication with that specific client. `listen()` prepares the socket for this process.

-----

#### How do you avoid blocking other than by using `select`?

You can make a socket **non-blocking** by setting the `O_NONBLOCK` flag using `fcntl()`. Other methods for non-blocking I/O include:

  * **`poll()`:** A more efficient and scalable alternative to `select()`.
  * **`epoll()` (Linux-specific):** The most scalable and highest-performance method for handling a large number of concurrent connections.

-----

#### Disadvantage of using `select`?

The main disadvantage of `select()` is its lack of scalability. It uses a bitmask (a `fd_set`) to monitor file descriptors, which has a fixed size. As the number of file descriptors increases, `select()` becomes inefficient because:

  * The bitmask has to be rebuilt every time.
  * The kernel has to iterate through all file descriptors in the set to check for events, even if only a few are active.

-----

#### Is a socket descriptor blocking?

By default, socket descriptors are **blocking**. A blocking socket means that a call to a function like `accept()`, `read()`, or `write()` will not return until the operation is complete. You must explicitly change a socket to be non-blocking.

-----

#### How does TCP/IP work?

TCP/IP (Transmission Control Protocol/Internet Protocol) is a suite of protocols that provides the fundamental rules for communication over the internet.

  * **IP** handles addressing and routing data packets between different hosts. It is the core of the internet's addressing system.
  * **TCP** provides a reliable, connection-oriented service on top of IP. It ensures data is delivered in order, retransmits lost packets, and provides flow control.
  * **UDP (User Datagram Protocol)** is an alternative to TCP that provides an unreliable, connectionless service. It is faster but does not guarantee delivery or order.

-----

### 5\. Multithreading & Synchronization

-----

#### How does a thread function return a structure?

A thread function returns a value using `pthread_exit()`. The return value is a `void*` pointer, which can be a pointer to a dynamically allocated struct. This returned pointer is then retrieved by the main thread using `pthread_join()`.

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int a;
    int b;
} NODE;

void* thread_function() {
    NODE* i = (NODE*)malloc(sizeof(NODE));
    if (i == NULL) return NULL;
    i->a = 20;
    i->b = 10;
    printf("Address %p \n", i);
    pthread_exit((void *)i);
    // Code after pthread_exit() is not executed
    return NULL;
}

int main() {
    pthread_t th;
    NODE* local = NULL;

    pthread_create(&th, NULL, thread_function, NULL);
    pthread_join(th, (void**)&local);

    printf("Structure local variables: %d, %d \n", local->a, local->b);
    free(local);
    return 0;
}
```

-----

#### Is there bandwidth improvement after using threads?

Not directly. Bandwidth is a property of the underlying network connection. However, threads can significantly improve **throughput** (the amount of work done over a period of time) by allowing the program to utilize the CPU more efficiently, especially in I/O-bound tasks. While one thread is blocked on a network read, other threads can continue to process data.

-----

#### Two threads, slow because `malloc` is used. How would you improve the performance?

`malloc` can introduce performance bottlenecks, especially in a multithreaded environment, because it uses locks to protect its internal data structures, causing threads to serialize. To improve performance, you could:

1.  **Thread-Specific Malloc:** Use a memory allocator that is designed for multithreaded environments, such as **TCMalloc** (Google) or **jemalloc** (Facebook). These allocators use thread-local caches to minimize locking.
2.  **Pre-allocate Memory:** Allocate a large pool of memory once at the start of the program and manage it yourself using a custom allocator. This avoids frequent calls to `malloc` and `free` within the critical path.
3.  **Memory Pool per Thread:** Each thread can have its own private memory pool, eliminating the need for a global lock.

-----

#### What is priority inversion? How do you prevent it?

Priority inversion is a scenario in which a high-priority task is indirectly blocked by a low-priority task. This happens when the high-priority task needs to acquire a resource (e.g., a mutex) that is currently held by a low-priority task. While the low-priority task holds the resource, an intermediate-priority task can preempt it, causing the high-priority task to be blocked for an indefinite amount of time.

It is typically prevented using:

  * **Priority Inheritance:** The low-priority task temporarily inherits the priority of the highest-priority task waiting on the resource it holds. This ensures that the low-priority task is not preempted by any intermediate-priority tasks.
  * **Priority Ceiling:** The priority of a critical section is set to the priority of the highest-priority task that could ever enter it. When a task enters the critical section, its priority is raised to this ceiling, preventing any other tasks from preempting it.

-----

#### How would you define a stack size of a thread?

The stack size of a thread can be set using the `pthread_attr_setstacksize()` function before creating the thread. You first initialize a thread attributes object with `pthread_attr_init()` and then pass this object to `pthread_create()`.

-----

#### When a thread is created, does it get a stack from the parent process?

When a new thread is created, it gets its own private stack. This stack is allocated within the process's address space. The parent process (which is now the main thread) and the child thread share the same heap, global data, and code, but their stacks are separate.
