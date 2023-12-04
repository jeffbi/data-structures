/// \file   single_linked_list.c
/// \brief  Implementation of linked list in C.
/// \author Jeffrey K. Bienstadt
/// \copyright  Copyright (c) 2019--2023 Jeffrey K. Bienstadt

#include <stdlib.h> // for malloc/free

#include "double_linked_list.h"

/// \brief  Create a new doubly-linked list node populated with the specified data.
/// \param data The data to be carried by the new node.
/// \return A pointer to a new dll_node structure.
///
/// The node is created on the heap with malloc.
///
/// The new node's \c next and \c prev pointers are set to NULL.
///
/// The new node is not yet part of a linked list. The node will have to be
/// added to a list via one of the other functions.
dll_node *dll_create_node(int data)
{
    dll_node *node = (dll_node *)malloc(sizeof(dll_node));

    if (node != NULL)
    {
        node->prev = node->next = NULL;
        node->data = data;
    }

    return node;
}

/// \brief  Search a linked list for a node that contains the specified data.
/// \param start        A pointer to the node of the linked list to begin the search.
/// \param data         The data to find.
/// \param direction    The direction to search, forward or backward.
/// \return On success returns a pointer to the first node containing the
///         desired data. On failure returns NULL.
dll_node *dll_find_data(dll_node *start, int data, dll_direction direction)
{
    if (start == NULL)
        return NULL;

    switch (direction)
    {
        case DLL_FORWARD:
            while (start != NULL)
            {
                if (start->data == data)
                    return start;
                start = start->next;
            }
            break;

        case DLL_BACKWARD:
            while (start != NULL)
            {
                if (start->data == data)
                    return start;
                start = start->prev;
            }
            break;

        default:
            break;
    }

    return NULL;
}

/// \brief  Traverse the linked list until the head node (the first node in
///         the list) is found.
/// \param start A pointer to the node from which to begin the search.
/// \return On success returns a pointer to the head node of the list.
///         On failure returns NULL.
dll_node *dll_find_head_node(dll_node *start)
{
    if (start == NULL)
        return NULL;

    while (start->prev != NULL)
        start = start->prev;

    return start;
}

/// \brief  Traverse the linked list until the tail node (the last node in
///         the list) is found.
/// \param start A pointer to the node from which to begin the search.
/// \return On success returns a pointer to the tail node of the list.
///         On failure returns NULL.
dll_node *dll_find_tail_node(dll_node *start)
{
    if (start == NULL)
        return NULL;

    while (start->next != NULL)
        start = start->next;

    return start;
}

/// \brief  Appends a node to the end of the linked list.
/// \param head A pointer to pointer to the head node of the linked list.
/// \param node The node to be appended to the linked list.
/// \return A pointer to the appended node.
/// \remark The \p head parameter is a pointer to pointer. This is because the
///         appended node could become the new head of this list if the list
///         is empty.
dll_node *dll_append_node(dll_node **head, dll_node *node)
{
    if (*head == NULL)
    {
        node->prev = node->next = NULL;
        *head = node;
    }
    else
    {
        dll_node *tail = dll_find_tail_node(*head);

        tail->next = node;
        node->prev = tail;
    }

    return node;
}

/// \brief  Creates a new node with the specified data and appends the node to
///         the end of the linked list.
/// \param head A pointer to pointer to the head node of the linked list.
/// \param data The data to be stored in the created and appended node.
/// \return A pointer to the newly created and appended node.
/// \remark The \p head parameter is a pointer to pointer. This is because the
///         appended node could become the new head of this list if the list
///         is empty.
dll_node *dll_append_data(dll_node **head, int data)
{
    return dll_append_node(head, dll_create_node(data));
}

/// \brief  Inserts a node into the linked list, following a specified node.
/// \param after    A pointer to the node after which the new node is to be inserted.
///                 This parameter must not be NULL.
/// \param node     A pointer to the node to be inserted.
/// \return A pointer to the inserted node.
dll_node *dll_insert_node_after(dll_node *after, dll_node *node)
{
    node->next = after->next;
    node->prev = after;
    after->next = node;

    return node;
}

/// \brief  Creates a new node with the specified data and inserts the node
/// into the linked list.
/// \param after    A pointer to the node after which the new node is to be inserted.
///                 This parameter must not be NULL.
/// \param data     The data to be stored in the created and inserted node.
/// \return A pointer to the newly created and inserted node.
dll_node *dll_insert_data_after(dll_node *after, int data)
{
    return dll_insert_node_after(after, dll_create_node(data));
}

/// \brief  Inserts a node into the linked list, before a specified node.
/// \param before   A pointer to the node before which the new node is to be inserted.
///                 This parameter must not be NULL.
/// \param node     A pointer to the node to be inserted.
/// \return A pointer to the inserted node.
dll_node *dll_insert_node_before(dll_node **before, dll_node *node)
{
    if (*before == NULL)    // Empty list. node becomes head node.
    {
        node->prev = node->next = NULL;
        *before = node;
    }
    else if ((*before)->prev == NULL) // Inserting before the head node
    {
        node->prev = NULL;
        node->next = *before;
        (*before)->prev = node;
        *before = node; // node is new head node
    }
    else
    {
        node->prev = (*before)->prev;
        node->next = *before;
        node->prev->next = node;
        (*before)->prev = node;
    }

    return node;
}

/// \brief  Creates a new node with the specified data and inserts the node
/// into the linked list.
/// \param before   A pointer to the node before which the new node is to be inserted.
///                 This parameter must not be NULL.
/// \param data     The data to be stored in the created and inserted node.
/// \return A pointer to the newly created and inserted node.
dll_node *dll_insert_data_before(dll_node **before, int data)
{
    return dll_insert_node_before(before, dll_create_node(data));
}

/// \brief  Inserts a new node at the beginning of the linked list. The new node
///         becomes the new head of the list.
/// \param head A pointer to pointer to the head of the linked list.
/// \param node A pointer to the node to be inserted at the beginning of the
///             linked list.
/// \return A pointer to the prepended node.
/// \remark The \p head parameter is a pointer to pointer. This is because the
///         new node will become the new head of the linked list.
dll_node *dll_prepend_node(dll_node **head, dll_node *node)
{
    node->next = *head;
    node->prev = NULL;
    if (*head != NULL)
        (*head)->prev = node;
    *head = node;

    return node;
}

/// \brief  Creates a new node with the specified data and inserts the node at
///         the beginning of the linked list
/// \param head A pointer to pointer to the head of the linked list.
/// \param data The data to be stored in the created and prepended node.
/// \return A pointer to the newly created and prepended node.
/// \remark The \p head parameter is a pointer to pointer. This is because the
///         new node will become the new head of the linked list.
dll_node *dll_prepend_data(dll_node **head, int data)
{
    return dll_prepend_node(head, dll_create_node(data));
}

/// \brief  Removes a node from a linked list.
/// \param head A pointer to pointer to the head node of the linked list.
/// \param node The node to be removed from the linked list
/// \remark The \p head parameter is a pointer to pointer. This is because the
///         node to be removed may be he head node, in which case we would need
///         to make the next node the new head node.
/// \remark Memory allocated to the removed node is not freed.
void dll_remove_node(dll_node **head, dll_node *node)
{
    if (*head == NULL)
        return; // Empty list, do nothing

    // Are we removing the head?
    if (node == *head)
    {
        *head = (*head)->next;
        (*head)->prev = NULL;
        node->next = NULL;
    }
    else
    {
        dll_node *previous = node->prev;

        // Unlink the node from the linked list
        previous->next = node->next;
        node->next->prev = previous;
        node->prev = node->next = NULL;
    }
}

/// \brief  Erases an entire linked list.
/// \param head A pointer to pointer to the head node of the linked list.
/// \remark The \p head parameter is a pointer to pointer. This is because the head
///         node will become NULL, indicating that the list is empty.
/// \remark As each node is removed from the list its allocated memory is freed.
void dll_erase(dll_node **head)
{
    // If the list is already empty, do nothing
    if (*head == NULL)
        return;

    dll_node *current = *head;

    while (current != NULL)
    {
        dll_node *next = current->next;

        free(current);
        current = next;
    }

    *head = NULL;
}
