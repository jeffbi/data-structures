/// \file   LinkedList.h
/// \brief  Implementation of a linked list in C++
/// \author Jeffrey K. Bienstadt
/// \copyright  Copyright (c) 2019 Jeffrey K. Bienstadt

#ifndef INC_LINKED_LIST
#define INC_LINKED_LIST

/// \brief  The linked list node structure.
///
/// This structure is the core of the linked list, holding the list element's
/// data and the pointer to the next node in the list.
///
/// This structure is not exposed to the list user. Instead it is abstracted
/// away by the ListIterator.
template<typename T>
struct list_node_t
{
    T            _data; ///< The data stored in the linked list.
    list_node_t *_next; ///< Pointer to tne next node in the list.

    /// \brief  Construct a new node with its data. The node's
    ///         \c next pointer is set to \c null_ptr.
    list_node_t(const T &data)
      : _data{data},
        _next{nullptr}
    {}

    list_node_t() = delete;
    // The node is not copyable because we deal with them strictly as pointers.
    list_node_t(const list_node_t &) = delete;
    list_node_t & operator=(const list_node_t &) = delete;
};

/// \brief  A forward iterator that provides access to the data in a \c LinkedList.
///
/// \remark An iterator acts like a pointer to the data in a linked list.
/// \remark This iterator is usable in a range-based \c for.
template<typename T>
class ListIterator
{
public:
    /// \brief  Alias for the node type.
    using node_type = list_node_t<T>;

    ListIterator() = delete;
    /// \brief  Copy constructor.
    ListIterator(const ListIterator &) = default;
    /// \brief  Assignment operator.
    ListIterator & operator=(const ListIterator &) = default;

    /// \brief  Construct a \c ListIterator with a \c node
    ///
    /// \param node The linked list node to be wrapped by this iterator.
    ListIterator(node_type *node) noexcept
      : _node{node}
    {}


    /// \brief  Dereference the iterator, getting access to the underlying data.
    ///
    /// \return A reference to the data pointed to by this iterator.
    T & operator*() const noexcept
    {
        return _node->_data;
    }

    /// \brief  Prefix increment operator. Increments the iterator to point to
    ///         the next node in the linked list.
    ///
    /// \return *this
    ListIterator & operator++() noexcept
    {
        _node = _node->_next;
        return *this;
    }

    /// \brief  Postfix increment operator. Increments the iterator to point to
    ///         the node in the linked list.
    ///
    /// \return An iterator pointing to the next item in the linked list.
    ListIterator operator++(int) noexcept
    {
        ListIterator tmp = *this;
        ++*this;
        return tmp;
    }

    /// \brief  Equality operator. Determines if this iterator is equal to another,
    ///         i.e., if they both refer to the same node in the linked list.
    ///
    /// \param rhs  A refererce to a ListIterator to compare to this iterator.
    ///
    /// \return \c true if \p rhs is equal to this iterator, \c false otherwise.
    bool operator==(const ListIterator &rhs) const noexcept
    {
        return _node == rhs._node;
    }

    /// \brief  Inequality operator. Determines if this iterator is not equal
    ///         to another, i.e., if they each do not refer to the same node
    ///         in the linked list.
    ///
    /// \param rhs  A refererce to a ListIterator to compare to this iterator.
    ///
    /// \return \c true if \p rhs is not equal to this iterator, \c false otherwise.
    bool operator!=(const ListIterator &rhs) const noexcept
    {
        return _node != rhs._node;
    }

private:
    template<typename Ty>
    friend class LinkedList;

    node_type *_node;   // The linked list node wrapped by this iterator.
};

/// \brief  An implementation of a singly-linked list.
template<typename T>
class LinkedList
{
private:
    using node_type = list_node_t<T>;
    using iterator_type = ListIterator<T>;

public:
    /// \brief  Default-construct an empty LinkedList.
    LinkedList()
      : _head{nullptr}
    { }

    /// \brief  Destroy a Linked List.
    ///
    /// Any contained nodes will be removed and their memory reclaimed.
    ~LinkedList()
    {
        erase();
    }

    LinkedList(const LinkedList &) = delete;
    LinkedList & operator=(const LinkedList &) = delete;

    /// \brief  Determine if a LinkedList is empty.
    ///
    /// \return \c true \c if the LinkedList is empty, \c false \c otherwise.
    bool is_empty() const noexcept
    {
        return _head == nullptr;
    }

    /// \brief  Prepend a new item to the beginning of a linked list. The new
    ///         item becomes the new head of the linked list.
    ///
    /// \param data The data to be added to the linked list.
    void prepend(const T &data) noexcept
    {
        node_type *node = new node_type(data);

        if (is_empty())
        {
            _head = node;
        }
        else
        {
            node->_next = _head;
            _head = node;
        }
    }

    /// \brief  Append a new item to the end of the linked list.
    ///
    /// \param data The data to be appended to the linked list.
    ///
    /// \remark This function must locate the tail of the linked list in order
    ///         to append the new item. This can be slow in large lists.
    ///         Consider using the \c InsertAfter function when appending more
    ///         than one item to the end of a long list.
    void append(const T &data) noexcept
    {
        node_type *node = new node_type(data);

        if (is_empty())
        {
            _head = node;
        }
        else
        {
            node_type *tail = find_tail_node();
            tail->_next = node;
        }
    }

    /// \brief  Erase the linked list. All memory allocated to nodes is reclaimed.
    void erase() noexcept
    {
        node_type *current = _head;

        while (current)
        {
            node_type *next = current->_next;

            delete current;
            current = next;
        }

        _head = nullptr;
    }

    /// \brief  Return an iterator pointing to the head of the linked list.
    iterator_type begin() noexcept
    {
        return iterator_type(_head);
    }

    /// \brief  Return an iterator pointing to one past the tail of the linked list.
    iterator_type end() noexcept
    {
        return iterator_type(nullptr);
    }

    /// \brief  Return an iterator to the last element of the linked list.
    iterator_type tail() noexcept
    {
        return iterator_type(find_tail_node());
    }

    /// \brief  Insert a new item into the linked list immediately following
    ///         the specified iterator.
    ///
    /// \param it   An iterator pointing to an existing item in the linked list.
    /// \param data The data to be inserted into the list.
    ///
    /// \return An iterator pointing to the new list item.
    iterator_type insert_after(iterator_type it, const T &data) noexcept
    {
        node_type *node = it._node;
        node_type *new_node = new node_type(data);

        new_node->_next = node->_next;
        node->_next = new_node;

        return iterator_type(new_node);
    }

private:
    /// \brief  Helper function to find the last node in the list.
    ///
    /// \return A pointer to the last node in the list, or nullptr if the list
    ///         is empty.
    node_type *find_tail_node()
    {
        if (is_empty())
            return nullptr;

        node_type *current = _head;

        while (current->_next)
            current = current->_next;

        return current;
    }

private:
// Instance data
    node_type *_head;
};


#endif  // INC_LINKED_LIST
