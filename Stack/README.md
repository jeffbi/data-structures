# Stack
The stack is a very simple first-in last-out (LIFO) data structure. New items are _pushed_ onto the stack, making the last pushed item the new "top" of the stack. This can be visualized as

```
        ---------
        |       |
 Top--->|  42   |<---Third item pushed
        |       |
        ---------
        |       |
        |   7   |<---Second item pushed
        |       |
        ---------
        |       |
        |  16   |<---First item pushed
        |       |
        ---------
```
Only the top item on the stack is accesible. The top item may be removed by _popping_ it off the stack, making the previously pushed item the new top of the stack. Some implementations provide a mechanism to access the top element of the stack, while others require popping the top value off the stack to access it.

The capacity of a stack, the maximum number of item that a stack may contain, might be bounded (having a fixed maximum) or it might be unbounded, having no restrictions on the capacity other than available memory. A bounded stack is often implemented using an array. Unbounded stacks are typically implemented using another unbounded data structure such as a linked list or a deque.

## How it works
The specifics of how a stack is implemented depends on the underlying data structure used to contain the stack's data.

An array-based stack keeps an index referring to the array position that is the current top of the stack. That index is incremented for each push and decremented for each pop.
```
Index of current top |
                     V
        ---------------------
  Array | 16 |  7 | 42 |    |
        ---------------------
          0    1    2    3
```

A stack implemented using a linked list prepends each pushed item to the beginning of the list, making the new item the new head of the list. Popping at item off this stack removes the head node from the list and makes the next node the new head.
```
Node at current top |
                    V
            -----------   -----------   -----------
Linked list | 42 |next|-->|  7 |next|-->| 16 |next|
            -----------   -----------   -----------
             Head Node                   Tail Node
```

## Performance
Pushing and popping values onto and off of the stack are constant-time operations. Stacks do not generally have operations for inserting or removing items from inside the stack or for searching within the stack.

## Implementations
Implementations of the stack are presented here in C and in C++. These implementations are provided for educational purposes and are not tuned for production code.

The C implementation is a simple, bounded array-based stack.

The C++ implementation uses a linked list to store the stack's data.
