/// \file   SingleLinkedList.h
/// \brief  Implementation of a singly-linked list in C++
/// \author Jeffrey K. Bienstadt
/// \copyright  Copyright (c) 2019-2021 Jeffrey K. Bienstadt

#ifndef INC_SINGLE_LINKED_LIST
#define INC_SINGLE_LINKED_LIST

#include <stdexcept>

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
        node_t *new_node = new node_t{data};

        new_node->_next = _head_node;
        _head_node = new_node;

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
        if (!is_empty() && node != nullptr)
        {
            node_t *new_node = new node_t{data};

            new_node->_next = node->_next;
            node->_next = new_node;

            return new_node;
        }

        throw std::invalid_argument("SingleLinkedList::insert_after");
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
                          : insert_after(data, find_tail_node());
    }

    /// \brief  Remove the specified node from the linked list.
    ///
    /// \param node A pointer to the node to be removed.
    /// \return A pointer to the node following the removed node.
    ///
    /// \remark This function must traverse the linked list to find the node
    ///         previous to the specified node in order to keep the links
    ///         coherent.
    node_t *remove(node_t *node)
    {
        if (!is_empty() && node != nullptr)
        {
            if (node == _head_node)
            {
                _head_node = node->_next;
                delete node;
                return _head_node->_next;
            }
            else
            {
                node_t *previous = _head_node;

                while (previous != nullptr)
                {
                    if (previous->_next == node)
                    {
                        previous->_next = node->_next;
                        delete node;
                        return previous->_next;
                    }
                }
            }
        }

        throw std::invalid_argument("SingleLinkedList::remove");
    }

    /// \brief  Remove from the linked list the item immediately following
    ///         the specified node.
    ///
    /// \param node A pointer to an existing node in the linked list.
    ///
    /// \return A pointer to the list node following the removed node.
    node_t *remove_after(node_t *node)
    {
        if (!is_empty() && node != nullptr)
        {
            if (node->_next != nullptr)
            {
                node_t *next_node = node->_next;
                node->_next = next_node->_next;

                delete next_node;
            }

            return node->next;
        }

        throw std::invalid_argument("SingleLinkedList::remove_after");
    }

    /// \brief  Erase the linked list. Memory allocated to nodes is reclaimed.
    void erase()
    {
        node_t *current = head();

        while (current != nullptr)
        {
            node_t *next = current->_next;

            delete current;
            current = next;
        }

        _head_node = nullptr;
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
        node_t *current = head();

        while (current != nullptr) {
            if (current->data() == data)
                break;

            current = current->next();
        }

        return current;
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

        while (current->next() != nullptr)
            current = current->next();

        return current;
    }

// Instance data
private:
    node_t *_head_node{nullptr};
};

#endif // INC_SINGLE_LINKED_LIST
