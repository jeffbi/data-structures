/// \file   DoubleLinkedList.h
/// \brief  Implementation of a doubly-linked list in C++
/// \author Jeffrey K. Bienstadt
/// \copyright  Copyright (c) 2021 Jeffrey K. Bienstadt

#ifndef INC_DOUBLE_LINKED_LIST
#define INC_DOUBLE_LINKED_LIST

/// \brief  An implementation of a doubly-linked list.
template<typename T>
class DoubleLinkedList
{
public:
    /// \brief  The linked list node structure.
    ///
    /// This class is the core of the linked list, holding the list element's
    /// data and the pointers to the next and previous node in the list.
    ///
    class node_t
    {
    private:
        T       _data;              ///< Data contained in the node
        node_t *_next{nullptr};     ///< Pointer to the next node
        node_t *_prev{nullptr};     ///< Pointer to the previous name

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

        /// \brief  Return a pointer to the node's next node.
        node_t *next() const noexcept
        {
            return _next;
        }

        /// \brief  Return a pointer to the node's previous node.
        node_t *prev() const noexcept
        {
            return _prev;
        }

    private:
        void next(node_t *node)
        {
            _next = node;
        }

        void prev(node_t *node)
        {
            _prev = node;
        }

        friend DoubleLinkedList;
    };

    /// \brief  Default-construct an empty DoubleLinkedList.
    DoubleLinkedList() noexcept = default;

    DoubleLinkedList(const DoubleLinkedList &) = delete;
    DoubleLinkedList & operator=(const DoubleLinkedList &) = delete;

    /// \brief  Destroy a Linked List.
    ///
    /// Any contained nodes will be removed and their memory reclaimed.
    ~DoubleLinkedList()
    {
        erase();
    }

    /// \brief  Return a pointer to the head node.
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

    /// \brief  Determine if a DoubleLinkedList is empty.
    ///
    /// \return \c true  if the DoubleLinkedList is empty, \c false otherwise.
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

        new_node->next(head());
        if (is_empty())
            _tail_node = new_node;
        else
            head()->prev(new_node);
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
        new_node->prev(node);
        node->next(new_node);
        if (new_node->_next == nullptr)
            _tail_node = new_node;
        else
            new_node->next()->prev(new_node);

        ++_count;

        return new_node;
    }

    /// \brief  Insert a new item into the linked list immediately preceding
    ///         the specified node.
    ///
    /// \param data The data to be inserted into the list.
    /// \param node A pointer to an existing node in the linked list.
    ///
    /// \return A pointer to the new item's node.
    node_t *insert_before(const T &data, node_t *node)
    {
        return node == head() ? prepend(data)
                              : insert_after(data, node->prev());
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

    /// \brief  Remove the specified node from the linked list.
    ///
    /// \param node A pointer to the node to be removed.
    /// \return A pointer to the node following the removed node.
    node_t *remove(node_t *node)
    {
        node_t *next_node{node->next()};

        if (node == head())
        {
            if (next_node == nullptr)
            {
                _head_node = _tail_node = nullptr;
            }
            else
            {
                next_node->prev(nullptr);
                _head_node = next_node;
            }
        }
        else if (node == tail())
        {
            node->prev()->next(nullptr);
            _tail_node = node->prev();
        }
        else
        {
            node->prev()->next(next_node);
            next_node->prev(node->prev());
        }

        delete node;
        --_count;

        return next_node;
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

        _tail_node = _head_node = nullptr;
        _count = 0;
    }

    /// \brief  Locate the first node containing the given value.
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
    node_t *_head_node{nullptr};    ///< Pointer to the head node
    node_t *_tail_node{nullptr};    ///< Pointer to the tail node
    size_t  _count{0};              ///< Number of elements in the linked list
};

#endif // INC_DOUBLE_LINKED_LIST
