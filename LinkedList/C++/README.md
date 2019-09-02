# Linked List Implementation in C++
This directory contains an implementation of the Linked List data structure in the C++ language.

This is a header-only implementation. The entirety of the Linked List code is in the LinkedList.h file.

## Implementing the node structure
A linked list is a sequence of nodes, each containing the data to be stored and a pointer to the next node in the sequence. Since the implementation uses a template, the data can be of any desired type.

The definition of the node structure is essentially
```C++
template<typename T>
struct list_node_t
{
    T            _data;
    list_node_t *_next;

    list_node_t(const T &data)
      : _data{data},
        _next{nullptr}
    {}

    list_node_t() = delete;
    list_node_t(const list_node_t &) = delete;
    list_node_t & operator=(const list_node_t &) = delete;
};
```
This structure contains the node's data and a pointer to the next node in the list which is another structure of the same type. The constructor sets the value of the node's data and expressly sets the node's `_next` pointer to `nullptr`, indicating that there is no node that follows this one.

The structure is not copyable, because the linked list concerns itself only with pointers.

> Note: The structure uses "raw" pointers rather than `unique_ptr` because using smart pointers would require additional code to properly handle the destruction of the list. Otherwise lists with a sufficiently large number of nodes would cause a stack overflow during destruction. Handling this is outside the scope of this sample linked list.

## Iterator
This implementation uses a simple iterator to abstract away the underlying details of the Linked List. This iterator, coupled with the `LinkedList`'s `begin()` and `end()` functions, allows the list to be traversed using the C++ range-based for statement.

However, the iterators are not compatible with the C++ standard library algorithms such as `std::find`. See [Iterators.md](Iterators.md) to learn how to make the `ListIterator` work with these algorithms.

## Educational purposes only
The code presented here is for educational purposes only. The C++ standard library contains the `forward_list` class which provides a complete implementation of a singly linked list that has been thoroughly tested and optimized for performance.
