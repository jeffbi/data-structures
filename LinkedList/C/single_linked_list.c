/// \file   single_linked_list.c
/// \brief  Implementation of linked list in C.
/// \author Jeffrey K. Bienstadt
/// \copyright  Copyright (c) 2019 Jeffrey K. Bienstadt

#include <stdlib.h> // for malloc/free

#include "single_linked_list.h"

/// \brief  Creates a new singly-linked list node populated with the specified data.
/// \param data The data to be carried by the new node.
/// \return A pointer to a new sll_node structure.
///
/// The node is created on the heap with malloc.
///
/// The new node's \c next pointer is set to NULL.
///
/// The new node is not yet part of a linked list. The node will have to be
/// added to a list via one of the other functions.
sll_node *sll_create_node(int data)
{
    sll_node *node = (sll_node *)malloc(sizeof(sll_node));

    if (node != NULL)
    {
        node->next = NULL;
        node->data = data;
    }

    return node;
}

/// \brief  Searches a linked list for a node that contains the specified data.
/// \param start    A pointer to the node of the linked list to begin the search.
/// \param data     The data to find.
/// \return On success returns a pointer to the first node containing the
///         desired data. On failure returns NULL.
sll_node *sll_find_data(sll_node *start, int data)
{
    while (start != NULL)
    {
        if (start->data == data)
            break;
        start = start->next;
    }

    return start;
}

/// \brief  Traverses the linked list until the tail node (the last node in
///         the list) is found.
/// \param start A pointer to the node from which to begin the search.
/// \return On success returns a pointer to the tail node of the list.
///         On failure returns NULL.
sll_node *sll_find_tail_node(sll_node *start)
{
    if (start != NULL)
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
sll_node *sll_append_node(sll_node **head, sll_node *node)
{
    if (*head == NULL)
        *head = node;
    else
        sll_find_tail_node(*head)->next = node;

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
sll_node *sll_append_data(sll_node **head, int data)
{
    return sll_append_node(head, sll_create_node(data));
}

/// \brief  Inserts a node into the linked list, following a specified node.
/// \param after    A pointer to the node after which the new node is to be inserted.
///                 This parameter must not be NULL.
/// \param node     A pointer to the node to be inserted.
/// \return A pointer to the inserted node.
sll_node *sll_insert_node_after(sll_node *after, sll_node *node)
{
    node->next = after->next;
    after->next = node;

    return node;
}

/// \brief  Creates a new node with the specified data and inserts the node
/// into the linked list.
/// \param after    A pointer to the node after which the new node is to be inserted.
/// \param data     The data to be stored in the created and inserted node.
/// \return A pointer to the newly created and inserted node.
sll_node *sll_insert_data_after(sll_node *after, int data)
{
    return sll_insert_node_after(after, sll_create_node(data));
}

/// \brief  Inserts a new node at the beginning of the linked list. The new node
///         becomes the new head of the list.
/// \param head A pointer to pointer to the head of the linked list.
/// \param node A pointer to the node to be inserted at the beginning of the
///             linked list.
/// \return A pointer to the prepended node.
/// \remark The \p head parameter is a pointer to pointer. This is because the
///         new node will become the new head of the linked list.
sll_node *sll_prepend_node(sll_node **head, sll_node *node)
{
    node->next = *head;
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
sll_node *sll_prepend_data(sll_node **head, int data)
{
    return sll_prepend_node(head, sll_create_node(data));
}

/// \brief  Removes the node following a given node from a linked list.
/// \param node A pointer to the node immediately prior to the node to be removed.
/// \return A pointer to the node following the removed node.
/// \remark The \p head parameter is a pointer to pointer. This is because the
///         node to be removed may be he head node, in which case we would need
///         to make the next node the new head node.
sll_node *sll_remove_node_after(sll_node *node)
{
    if (node->next != NULL)
    {
        sll_node *next = node->next;

        node->next = next->next;
        free(next);
    }

    return node->next;
}

/// \brief  Removes a node from a linked list.
/// \param head A pointer to pointer to the head node of the linked list.
/// \param node The node to be removed from the linked list.
/// \return A pointer to the node following the removed node.
/// \remark The \p head parameter is a pointer to pointer. This is because the
///         node to be removed may be he head node, in which case we would need
///         to make the next node the new head node.
sll_node *sll_remove_node(sll_node **head, sll_node *node)
{
    // Are we removing the head?
    if (node == *head)
    {
        *head = node->next;
        free(node);
        return *head;
    }
    else
    {
        sll_node *previous = *head;

        // Traverse the list looking for the node previous to the desired node.
        while (previous != NULL)
        {
            if (previous->next == node)
                return sll_remove_node_after(node);

            previous = previous->next;
        }
    }

    // No previous node was found.
    return NULL;
}

/// \brief  Erases an entire linked list.
/// \param head A pointer to pointer to the head node of the linked list.
/// \remark The \p head parameter is a pointer to pointer. This is because the head
///         node will become NULL, indicating that the list is empty.
/// \remark As each node is removed from the list its allocated memory is freed.
void sll_erase(sll_node **head)
{
    sll_node *current = *head;

    while (current != NULL)
    {
        sll_node *next = current->next;

        free(current);
        current = next;
    }

    *head = NULL;
}
