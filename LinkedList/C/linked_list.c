/// \file   linked_list.c
/// \brief  Implementation of linked list in C.
/// \author Jeffrey K. Bienstadt
/// \copyright  Copyright (c) 2019 Jeffrey K. Bienstadt

#include <stdlib.h> // for malloc/free

#include "linked_list.h"

/// \brief  Create a new linked-list node populated with the specified data.
/// \param data The data to be carried by the new node.
/// \return A pointer to a new ll_node structure.
///
/// The node is created on the heap with malloc.
///
/// The new node's \c next pointer is set to NULL.
///
/// The new node is not yet part of a linked list. The node will have to be
/// added to a list via one of the other functions.
ll_node *list_create_node(int data)
{
    ll_node *node = (ll_node *)malloc(sizeof(ll_node));

    if (node != NULL)
    {
        node->next = NULL;
        node->data = data;
    }

    return node;
}

/// \brief  Search a linked list for a node that contains the specified data.
/// \param head     A pointer to the head node of the linked list to search.
/// \param data     The data to find.
/// \return On success returns a pointer to the first node containing the
///         desired data. On failure returns NULL.
ll_node *list_find_data(ll_node *head, int data)
{
    ll_node *current = head;

    while (current != NULL)
    {
        if (current->data == data)
            break;
        current = current->next;
    }

    return current;
}

/// \brief  Traverse the linked list until the tail node (the last node in
//          the list) is found.
/// \param head A pointer to the head node of the linked list to traverse.
/// \return On success returns a pointer to the tail node of the list.
///         On failure returns NULL.
ll_node *list_find_tail_node(ll_node *head)
{
    if (head == NULL)
        return NULL;

    ll_node *current = head;
    while (current->next != NULL)
        current = current->next;

    return current;
}

/// \brief  Appends a node to the end of the linked list.
/// \param head A pointer to pointer to the head node of the linked list.
/// \param node The node to be appended to the linked list.
/// \return A pointer to the appended node.
/// \remark The \p head parameter is a pointer to pointer. This is because the
///         appended node could become the new head of this list if the list
//          is empty.
ll_node *list_append_node(ll_node **head, ll_node *node)
{
    if (*head == NULL)
        *head = node;
    else
        list_find_tail_node(*head)->next = node;

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
ll_node *list_append_data(ll_node **head, int data)
{
    return list_append_node(head, list_create_node(data));
}

/// \brief  Inserts a node into the linked list, following a specified node.
/// \param after    A pointer to the node after which the new node is to be inserted.
/// \param node     A pointer to the node to be inserted.
/// \return A pointer to the inserted node.
ll_node *list_insert_node(ll_node *after, ll_node *node)
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
ll_node *list_insert_data(ll_node *after, int data)
{
    return list_insert_node(after, list_create_node(data));
}

/// \brief  Inserts a new node at the beginning of the linked list. The new node
///         becomes the new head of the list.
/// \param head A pointer to pointer to the head of the linked list.
/// \param node A pointer to the node to be inserted at the beginning of the
///             linked list.
/// \return A pointer to the prepended node.
/// \remark The \p head parameter is a pointer to pointer. This is because the
///         new node will become the new head of the linked list.
ll_node *list_prepend_node(ll_node **head, ll_node *node)
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
ll_node *list_prepend_data(ll_node **head, int data)
{
    return list_prepend_node(head, list_create_node(data));
}

/// \brief  Removes a node from a linked list.
/// \param head A pointer to pointer to the head node of the linked list.
/// \param node The node to be removed from the linked list
/// \remark The \p head parameter is a pointer to pointer. This is because the
///         node to be removed may be he head node, in which case we would need
///         to make the next node the new head node.
/// \remark Memory allocated to the removed node is not freed.
void list_remove_node(ll_node **head, ll_node *node)
{
    // Are we removing the head?
    if (node == *head)
    {
        (*head)->next = NULL;
        *head = (*head)->next;
    }
    else
    {
        ll_node *prev = *head;

        // Traverse the list looking for the node previous to the desired node.
        while (prev->next != NULL)
        {
            if (prev->next == node)
            {
                // Unlink the node from the linked list
                prev->next = node->next;
                node->next = NULL;
                return;
            }

            prev = prev->next;
        }
    }
}

/// \brief  Erases an entire linked list.
/// \param head A pointer to pointer to the head node of the linked list.
/// \remark The \p head parameter is a pointer to pointer. This is because the head
///         node will become NULL, indicating that the list is empty.
/// \remark As each node is removed from the list its allocated memory is freed.
void list_erase(ll_node **head)
{
    // If the list is already embty, do nothing
    if (head == NULL || *head == NULL)
        return;

    ll_node *current = *head;

    while (current != NULL)
    {
        ll_node *next = current->next;

        free(current);
        current = next;
    }

    *head = NULL;
}
