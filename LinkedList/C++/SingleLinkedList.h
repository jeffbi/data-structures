/// \file   SingleLinkedList.h
/// \brief  Implementation of a singly-linked list in C++
/// \author Jeffrey K. Bienstadt
/// \copyright  Copyright (c) 2019--2023 Jeffrey K. Bienstadt

#ifndef INC_SINGLE_LINKED_LIST
#define INC_SINGLE_LINKED_LIST

/// \brief  An implementation of a singly-linked list.
template<typename T>
class SingleLinkedList
{
public:
    /// \brief  The linked list node structure.
    ///
    /// This class is the core of the linked list, holding the list element's
    /// data and the pointer to the next node in the list.
    ///
    class node_t
    {
    private:
        T       _data;              ///< Data contained in the node
        node_t *_next{nullptr};     ///< Pointer to the next node

    public:
        explicit node_t(const T &data)
          : _data{data}
        {}

        node_t(const node_t &) = delete;
        node_t & operator=(const node_t &) = delete;

        /// \brief  Return a reference to the node's data.
        T &data() noexcept
        {
            return _data;
        }

        /// \brief  Return a pointer to the node's next node
        node_t *next() const noexcept
        {
            return _next;
        }

    private:
        void next(node_t *node) noexcept
        {
            _next = node;
        }

        friend SingleLinkedList;
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
        erase();
    }

    /// \brief  Return a pointer to the head node
    node_t *head() const noexcept
    {
        return _head_node;
    }

    /// \brief  Return a pointer to the tail node.
    node_t *tail() const noexcept
    {
        return _tail_node;
    }

    /// \brief  Return the number of elements in the linked list.
    size_t size() const noexcept
    {
        return _count;
    }

    /// \brief  Determine if a SingleLinkedList is empty.
    ///
    /// \return \c true \c if the SingleLinkedList is empty, \c false otherwise.
    bool is_empty() const noexcept
    {
        return head() == nullptr;
    }

    /// \brief  Prepend a new item to the beginning of a linked list. The new
    ///         item becomes the new head of the linked list.
    ///
    /// \param data The data to be added to the linked list.
    /// \return A pointer to the to the prepended node.
    node_t *prepend(const T &data)
    {
        node_t *new_node{new node_t(data)};

        new_node->next(_head_node);
        if (is_empty())
            _tail_node = new_node;
        _head_node = new_node;

        ++_count;

        return new_node;
    }

    /// \brief  Insert a new item into the linked list immediately following
    ///         the specified node.
    ///
    /// \param data The data to be inserted into the list.
    /// \param node A pointer to an existing node in the linked list.
    ///
    /// \return A pointer to the new item's node.
    node_t *insert_after(const T &data, node_t *node)
    {
        node_t *new_node{new node_t(data)};

        new_node->next(node->next());
        node->next(new_node);

        ++_count;

        return new_node;
    }

    /// \brief  Append a new item to the end of the linked list.
    ///
    /// \param data The data to be appended to the linked list.
    /// \return A pointer to the appended item's node.
    node_t *append(const T &data)
    {
        return is_empty() ? prepend(data)
                          : insert_after(data, tail());
    }

    /// \brief  Remove from the linked list the item immediately following
    ///         the specified node.
    ///
    /// \param node A pointer to an existing node in the linked list.
    ///
    /// \return A pointer to the list node following the removed node.
    node_t *remove_after(node_t *node)
    {
        if (node->next() != nullptr)
        {
            node_t *next{node->next()};

            node->next(next->next());
            if (next == tail())
                _tail_node = node;

            delete next;
            --_count;
        }

        return node->next();
    }

    /// \brief  Remove the specified node from the linked list.
    ///
    /// \param node A pointer to the node to be removed.
    /// \return A pointer to the node following the removed node.
    ///
    /// \remark This function must traverse the linked list to find the node
    ///         previous to the specified node in order to keep the links
    ///         coherent. Unlike remove_after, this function may be used to
    ///         remove the head node.
    node_t *remove(node_t *node)
    {
        node_t *next_node{node->next()};

        if (node == head())
        {
            if (next_node == nullptr)
                _head_node = _tail_node = nullptr;
            else
                _head_node = next_node;

            delete node;
            --_count;
            return next_node;
        }
        else
        {
            // Find the node previous to the node to be removed and remove_after that node.
            node_t *previous = _head_node;

            while (previous != nullptr)
            {
                if (previous->next() == node)
                    return remove_after(previous);
            }
        }
    }

    /// \brief  Erase the linked list. Memory allocated to nodes is reclaimed.
    void erase()
    {
        node_t *current{head()};

        while (current != nullptr)
        {
            node_t *next{current->next()};

            delete current;
            current = next;
        }

        _head_node = _tail_node = nullptr;
        _count = 0;
    }

    /// \brief  Locate the first node containing the given data value.
    ///
    /// \param data Reference to an object of type \c T to be searched for.
    ///
    /// \return A pointer to the list node containing the specified value,
    ///         or \c nullptr if the data item was not found.
    ///
    /// \remark Type \c T must be comparable to another object of type \c T
    ///         via the equality operator (operator==).
    node_t *find(const T &data)
    {
        node_t *current{head()};

        while (current != nullptr)
        {
            if (current->data() == data)
                break;

            current = current->next();
        }

        return current;
    }

// Instance data
private:
    node_t *_head_node{nullptr};    ///< Pointer to head node
    node_t *_tail_node{nullptr};    ///< Pointer to tail node
    size_t  _count{0};              ///< Number of elements in the linked list
};

#endif // INC_SINGLE_LINKED_LIST
