# Stack Implementation in C
This directory contains a simple implementation of the Stack data structure in the C language. The implementation provides a bounded (fixed-size) array-based stack. The type of data stored on the stack may be essentialy anything, but this implementation uses a simple integer as the data type.

## Implementing the stack
The C implementation uses a dynamically allocated array so the maximum size of the stack can be specified when the stack is created. The definition of the `stack` structure is:
```C
typedef struct stack
{
    int capacity;   // stack capacity
    int top;        // current position of the top of the stack
    int *data;      // contents of the stack
} stack;
```
When the stack is created, `capacity` stores the maximum size of the stack, `data` points to a dynamically allocated array of size `capacity`, and `top` is set to -1 indicating that the stack is empty. Each _push_ operation inserts a value into the array at the location immediately following the value of `top`, then `top` is incremented to index that location which is then the top of the stack. The _top_ request just returns the value at the location indexed by `top`, and the _pop_ operation simply decrements `top` to reset the top of the stack to the previous location. When the number of pops equals the number of pushes, the value of `top` becomes -1 and the stack is empty.
