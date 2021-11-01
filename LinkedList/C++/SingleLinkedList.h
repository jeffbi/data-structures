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
public:
    /// \brief  The linked list node structure.
    ///
    /// This class is the core of the linked list, holding the list element's
    /// data and the pointer to the next node in the list.
    ///
    class node_t
    {
    private:
        T       _data;
        node_t *_next{nullptr};

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

        friend SingleLinkedList;
    };

public:
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
    ///
    /// \remark This function linearly traverses the list from head to tail,
    ///         so it will be fairly slow for long lists.
    node_t *tail() const noexcept
    {
        return find_tail_node();
    }

    /// \brief  Determine if a SingleLinkedList is empty.
    ///
    /// \return \c true \c if the SingleLinkedList is empty, \c false \c otherwise.
    bool is_empty() const noexcept
    {
        return _head_node == nullptr;
    }

    /// \brief  Prepend a new item to the beginning of a linked list. The new
    ///         item becomes the new head of the linked list.
    ///
    /// \param data The data to be added to the linked list.
    /// \return A pointer to the to the prepended node.
    node_t *prepend(const T &data)
    {
        node_t *node = new node_t{data};

        if (!is_empty())
            node->_next = _head_node;
        _head_node = node;

        return node;
    }

    /// \brief  Append a new item to the end of the linked list.
    ///
    /// \param data The data to be appended to the linked list.
    /// \return A pointer to the appended item's node.
    ///
    /// \remark This function must locate the tail of the linked list in order
    ///         to append the new item. This can be slow in large lists.
    ///         Consider using the \c insert_after function when appending more
    ///         than one item to the end of a long list.
    node_t *append(const T &data)
    {
        return is_empty() ? prepend(data)
                          : insert_after(find_tail_node(), data);
    }

    /// \brief  Insert a new item into the linked list immediately following
    ///         the specified node.
    ///
    /// \param node A pointer to an existing node in the linked list.
    /// \param data The data to be inserted into the list.
    ///
    /// \return A pointer to the new item's node.
    node_t *insert_after(node_t *node, const T &data)
    {
        node_t *new_node = new node_t{data};

        new_node->_next = node->_next;
        return node->_next = new_node;
    }

    /// \brief  Remove the item from the linked list immediately following
    ///         the specified node.
    ///
    /// \param node A pointer to an existing node in the linked list.
    ///
    /// \return A pointer to the list node following the removed node.
    node_t *remove_after(node_t *node)
    {
        if (node->_next != nullptr)
        {
            node_t *next_node = node->_next;

            node->_next = next_node->_next;

            delete next_node;
        }

        return node->next;
    }

    /// \brief  Erase the linked list. Memory allocated to nodes is reclaimed.
    void erase()
    {
        node_t *current = head();

        while (current)
        {
            node_t *next = current->_next;

            delete current;
            current = next;
        }

        _head_node = nullptr;
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

        node_t *current = head();

        while (current->next())
            current = current->next();

        return current;
    }

// Instance data
private:
    node_t *_head_node{nullptr};
};

#endif // INC_SINGLE_LINKED_LIST
