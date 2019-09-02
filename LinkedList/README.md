# Linked List
The Linked List is a linear data structure that consists of a series of _nodes_ that contain the data and which are _linked_ together. That is, each node contains the node's data and points to the next node in the list.
```
             Node A                        Node B
    |------------|--------|         |------------|--------|
    |            |        |         |            |        |
    |    Data    |  Next -|-------->|    Data    |  Next  |
    |____________|________|         |____________|________|
```
Linked list nodes are not required to occupy contiguous positions in memory. So long as each node links to the next node in the list, the nodes may occupy any position in memory and newly inserted nodes do not require that existing nodes be moved from their existing position.
```
             Node A                          Node B
    |------------|--------|         |------------|--------|
    |            |        |         |            |        |
    |    Data    |  Next -|--|  |-->|    Data    |  Next  |
    |____________|________|  |  |   |____________|________|
                             |  |
                             |  |
 |---------------------------|  |
 |                              |
 |             Node C           |
 |    |------------|--------|   |
 |    |            |        |   |
 |--->|    Data    |  Next -|---|
      |____________|________|
```
The first node in the list is called the _head_. The last node is called the _tail_. The tail node's `Next` item does not refer to another node and is usually set to the implementing language's _null_ value. A linked list that has no head is an empty list. A linked list of length 1 has a single node which is both the head and the tail node.

## How it works
To reach any given node in a linked list, the list must be traversed from the beginning, moving from node to node until the desired node is reached. Traversal is simple a matter of following each node's `Next` pointer to the next node, stopping either when the desired node has been reached or until there are no more nodes in the list. To search for a node that contains specific data, traverse the list comparing the each node's data to the searched-for value.

Inserting new nodes and removing existing nodes requires manipulating the nodes' `Next` pointers.

To append a new node to the end of the linked list, find the tail node and set its `Next` pointer to point to the new node, making the new node the new tail node.

Inserting a new node into the middle of the list requires manipulating the `Next` pointers of the new node and of the node that the new node is to follow. This requires two simple steps:
- set the new node's `Next` pointer to the node pointed to by the node that is to precede the new node
- set the preceding node's `Next` pointer to the new node

This is demonstrated by the two figures above. In the first figure there are two nodes, Node A and Node B, linked by Node A's `Next` pointer pointing to Node B. After inserting Node C into the list following Node A, Node C's `Next` pointer is pointing to Node B, and Node A's `Next` pointer now points to Node C.

To remove a node from the list, simply "unlink" the node from the list by setting the previous node's `Next` pointer to point to the node following the node to be removed.

## Performance
In contrast to data structures such as arrays, a linked list can grow as needed and insertions into the list are fast and efficient and occur in constant time. Since other nodes do not need to copied or moved to insert a new node, the insertaion takes the same amount of time no matter where the new node is inserted.

However, linked lists do not support the fast random access that arrays provide. To access a particular node, the list must be traversed node by node until the desired position within the list is reached. So while insertions and deletions occur in constant time, locating the position within the list takes linear time, i.e., it is directly proportional to the number of nodes in the list.

To illustrate this, on one test machine, using an implementation written in C, appending a mere one thousand elements one by one onto a linked list took around two to three _minutes_, which is a very long time. The vast majority of that time was taken up traversing the list to find the tail node on each append operation. Contrast that with prepending ten _million_ elements to the front of the list, resulting in a new head each time, which took around three to four seconds.

A large number of elements can be appended much more quickly by keeping track of the last node and simply inserting the new node after that node, then setting the saved last node to the new node. Using this method inserted 10,000,000 elements at the end of the list in under a second.

Each implementation's sample code demonstrates all of these operations.

## Implementations
Implementations of the linked list are presented here in C and in C++. These implementations are provided for educational purposes and are not tuned for production code.

The C implementation is a simple, low-level implementation that operates directly with the linked list nodes. No additional abstraction layer is provided, and the code size is fairly small.

The C++ implementation is somewhat larger and more complex than the C implementation. It provides a `LinkedList` class which abstracts away the lower-level operations and utilizes templates to allow the list to be used with any data type.
