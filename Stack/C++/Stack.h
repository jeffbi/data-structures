/// \file   Stack.h
/// \brief  Implementation of a stack in C++.
/// \author Jeffrey K. Bienstadt
/// \copyright  Copyright (c) 2019 Jeffrey K. Bienstadt

#ifndef INC_STACK
#define INC_STACK

/// \brief  An implementation of a stack, based on a singly-linked list.
template <typename T>
class Stack
{
public:

    /// \brief  Default-construct a Stack
    Stack()
      : _size{0},
        _head{nullptr}
    {
    }

    /// \brief  Destroy the stack, deleting any data nodes in the linked list.
    ~Stack()
    {
        while (_head)
        {
            node *new_head = _head->_next;
            delete _head;
            _head = new_head;
        }
    }

    /// \brief  Push a new value onto the stack.
    ///
    /// \param value    A \c const reference to the item to be pushed.
    void push(const T &value)
    {
        node *new_head = new node(value);

        // Prepend the new data node to the head of the list
        new_head->_next = _head;
        _head = new_head;

        ++_size;
    }

    /// \brief  Remove the item on the top of the stack.
    void pop()
    {
        node *old_head = _head;

        // Remove the node at the head and make the next node the new head.
        _head = old_head->_next;
        delete old_head;
        --_size;
    }

    /// \brief  Access the top item on the stack.
    ///
    /// \return A const reference to the top element in the stack.
    const T &top() const
    {
        return _head->_data;
    }

    /// \brief  Determine if the stack is empty.
    ///
    /// \return \c true if the stack is empty, \c false otherwise.
    bool is_empty() const noexcept
    {
        return _head == nullptr;
    }

    /// \brief  Get the number of items currently on the stack.
    ///
    /// \return The number of items currently on the stack.
    size_t size() const noexcept
    {
        return _size;
    }

private:
    // This is our linked list node
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

    size_t  _size;  // The current number of items in the stack.
    node   *_head;  // The current head of the list, which is also the top of the stack.
};

#endif  // INC_STACK
