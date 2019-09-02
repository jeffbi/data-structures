# Stack Implementation in C++
This directory contains an implementation of the stack data structure in the C++ language. The implementations provides an unbounded stack using a linked list to contain the data.

This is a header-only implementation. The entirety of the stack code is in the `Stack.h` file. The `Stack` class is a class template allowing the stack to contain objects of any desired type.

## Implementing the stack
The C++ implementation of the stack utilizes a simple singly linked list to store the stack data, making the stack unbounded, meaning it can grow to be as large as available memory permits. The linked list node is a private nested structure within the `Stack` class. The definition of the linked list node is:
```C++
    struct node
    {
        // Construct a new linked list node with the pushed data item
        node(const T& value)
          : _data{value},
            _next{nullptr}
        {}

        T     _data;    // The pushed data
        node *_next;    // Pointer to the next node in the linked list
    };
```
The `Stack` also maintains a count of the number of items in the stack and a pointer to the current head node of the linked list. The head of the linked list is the top of the stack. Each _push_ operation creates a new item at the head of the linked list, making the than node the new head of the list and the new top of the stack. The _top_ request just returns a reference to the data value from the head node, and the _pop_ operation removes the current head node making the next node in the linked list the new head node and the new top of the stack. When the number of pops equals the number of pushes, the final linked list node is removed and the stack is empty.

## Educational purposes only
The code presented here is for educational purposes only. The C++ standard library contains the `stack` class which provides a complete implementation of a stack that has been thoroughly tested and optimized for performance.
