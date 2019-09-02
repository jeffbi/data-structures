# Linked List Implementation in C
This directory contains a simple implementation of the Linked List data structure in the C language. The node structure is provided along with several functions to demonstrate operations on the list.

## Implementing the node structure
A linked list is a sequence of nodes, each containing the data to be stored and a pointer to the next node in the sequence. The type of data can be essentially anything, but this implementation uses a simple integer as the node's data.

The definition of the node structure is
```C
typedef struct ll_node
{
    int data;
    struct ll_node *next;
} ll_node;
```
This structure contains the node's data and a pointer to the next node in the list which is another structure of the same type. The tail node will have the `next` pointer set to `NULL`, indicating that there is no next node in the list.

## Implementing the functions
The functions that perform operations on the linked list do so by directly creating, traversing and manipulating instances of the node structure. The functions provide a fairly low-level implementation, without additional abstractions.

The functions that are implemented here are not a complete collection of functions. The user is encouraged to implement additional functions as needed.
