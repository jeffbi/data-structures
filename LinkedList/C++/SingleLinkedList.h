/// \file   SingleLinkedList.h
/// \brief  Implementation of a singly-linked list in C++
/// \author Jeffrey K. Bienstadt
/// \copyright  Copyright (c) 2019-2021 Jeffrey K. Bienstadt

#ifndef INC_SINGLE_LINKED_LIST
#define INC_SINGLE_LINKED_LIST

/// \brief  An implementation of a singly-linked list.
template<typename T>
class SingleLinkedList
{
private:
    struct node_t;

    /// \brief  Base of the linked list node structure.
    ///
    /// This allows us to have a "dummy node" before the head node.
    /// The dummy node has just a pointer to the head, there is no
    /// additional storage needed for data contained in an actual node.
    struct node_base
    {
        node_t *_next{nullptr};
    };

    /// \brief  The linked list node structure.
    ///
    /// This structure is the core of the linked list, holding the list element's
    /// data and the pointer to the next node in the list.
    ///
    /// This structure is not exposed to the list user. Instead it is abstracted
    /// away by the Iterator class.
    struct node_t : public node_base
    {
        T   _data;

        explicit node_t(const T &data)
          : _data{data}
        {}

        node_t(const node_t &) = delete;
        node_t & operator=(const node_t &) = delete;
    };

public:
    /// \brief  A forward iterator that provides access to the data in a \c LinkedList.
    ///
    /// \remark An iterator acts like a pointer to the data in a linked list.
    /// \remark This iterator may be used in a range-based \c for.
    class Iterator
    {
    public:
        /// \brief  Construct an \c Iterator with a \c node
        ///
        /// \param node The linked list node to be wrapped by this iterator.
        explicit Iterator(node_t *node = nullptr) noexcept
          : _node{node}
        {}
        Iterator(const Iterator &) = default;
        Iterator & operator=(const Iterator &) = default;

        /// \brief  Dereference the iterator, gaining access to the underlying data.
        ///
        /// \return A reference to the data pointed to by this iterator.
        T & operator*() const noexcept
        {
            return _node->_data;
        }

        /// \brief  Use pointer-like arrow operator to access members of the underlying data.
        ///
        /// \return A pointer to the underlying data.
        T * operator->() const noexcept
        {
            return &_node->_data;
        }

        /// \brief  Prefix increment operator. Increments the iterator to point to
        ///         the next node in the linked list.
        ///
        /// \return *this
        Iterator & operator++() noexcept
        {
            _node = _node->_next;
            return *this;
        }

        /// \brief  Postfix increment operator. Increments the iterator to point to
        ///         the node in the linked list.
        ///
        /// \return An iterator pointing to the next item in the linked list.
        Iterator operator++(int) noexcept
        {
            Iterator tmp{*this};
            ++*this;
            return tmp;
        }

        /// \brief  Equality operator. Determines if this iterator is equal to another,
        ///         i.e., if they both refer to the same node in the linked list.
        ///
        /// \param rhs  A refererce to a ListIterator to compare to this iterator.
        ///
        /// \return \c true if \p rhs is equal to this iterator, \c false otherwise.
        bool operator==(const Iterator &rhs) const noexcept
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
        bool operator!=(const Iterator &rhs) const noexcept
        {
            return !(*this == rhs);
        }

        friend SingleLinkedList;
    private:
        node_t *_node;
    };


    /// \brief  Default-construct an empty SingleLinkedList.
    SingleLinkedList() noexcept = default;

    SingleLinkedList(const SingleLinkedList &) = delete;
    SingleLinkedList & operator=(const SingleLinkedList &) = delete;

    /// \brief  Destroy a Linked List.
    ///
    /// Any contained nodes will be removed and their memory reclaimed.
    ~SingleLinkedList()
    {
        clear();
    }

    /// \brief  Determine if a SingleLinkedList is empty.
    ///
    /// \return \c true \c if the SingleLinkedList is empty, \c false \c otherwise.
    bool is_empty() const noexcept
    {
        return _pre_head._next == nullptr;
    }

    /// \brief  Prepend a new item to the beginning of a linked list. The new
    ///         item becomes the new head of the linked list.
    ///
    /// \param data The data to be added to the linked list.
    /// \return An iterator to the prepended item.
    Iterator prepend(const T &data)
    {
        node_t *node = new node_t(data);

        if (is_empty())
        {
            _pre_head._next = node;
        }
        else
        {
            node->_next = _pre_head._next;
            _pre_head._next = node;
        }

        return Iterator(node);
    }

    /// \brief  Append a new item to the end of the linked list.
    ///
    /// \param data The data to be appended to the linked list.
    /// \return An iterator to the appended item.
    ///
    /// \remark This function must locate the tail of the linked list in order
    ///         to append the new item. This can be slow in large lists.
    ///         Consider using the \c insert_after function when appending more
    ///         than one item to the end of a long list.
    Iterator append(const T &data)
    {
        node_t *node = new node_t(data);

        if (is_empty())
            _pre_head._next = node;
        else
            find_tail_node()->_next = node;

        return Iterator(node);
    }

    /// \brief  Insert a new item into the linked list immediately following
    ///         the specified iterator.
    ///
    /// \param it   An iterator pointing to an existing item in the linked list.
    /// \param data The data to be inserted into the list.
    ///
    /// \return An iterator pointing to the new list item.
    Iterator insert_after(const Iterator &it, const T &data)
    {
        node_t *node = it._node;
        node_t *new_node = new node_t(data);

        new_node->_next = node->_next;
        node->_next = new_node;

        return Iterator(new_node);
    }

    Iterator remove_after(const Iterator &it)
    {
        node_t *node = it._node;
        node_t *rem = node->_next; // node to be removed

        if (rem)
        {
            node->_next = rem->_next;
            delete rem;
        }

        return Iterator(node->_next);
    }

    /// \brief  Erase the linked list. Memory allocated to nodes is reclaimed.
    void clear() noexcept
    {
        node_t *current = _pre_head._next;

        while (current)
        {
            node_t *next = current->_next;

            delete current;
            current = next;
        }

        _pre_head._next = nullptr;
    }

    /// \brief  Return an iterator to the head of the linked list.
    Iterator begin() const noexcept
    {
        return Iterator(_pre_head._next);
    }

    /// \brief  Return an iterator to one past the tail of the linked list.
    Iterator end() const noexcept
    {
        return Iterator(nullptr);
    }

    /// \brief  Return an iteraor to the position just before the head of
    ///         the linked list.
    ///
    ///         This iterator's use cases are for use with \c insert_after
    ///         and \c remove_after. It may be incremented, but it must not
    ///         be dereferenced either with the \c * or \c -> operators.
    Iterator before_begin() noexcept
    {
        return Iterator(static_cast<node_t *>(&_pre_head));
    }

    /// \brief  Return an iterator to the last element of the linked list.
    Iterator tail() const noexcept
    {
        return Iterator(find_tail_node());
    }

private:
    /// \brief  Helper function to find the last node in the list.
    ///
    /// \return A pointer to the last node in the list, or nullptr if the list
    ///         is empty.
    node_t *find_tail_node() const noexcept
    {
        if (is_empty())
            return nullptr;

        node_t *current = _pre_head._next;

        while (current->_next)
            current = current->_next;

        return current;
    }

// Instance data
private:
    node_base  _pre_head;   // The "dummy node" before the head.
};

#endif // INC_SINGLE_LINKED_LIST
