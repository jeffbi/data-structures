/// \file   linked_list.h
/// \brief  structure definition and class declarations for a linked list in C.
/// \author Jeffrey K. Bienstadt
/// \copyright  Copyright (c) 2019 Jeffrey K. Bienstadt

#ifndef INC_LINKED_LIST
#define INC_LINKED_LIST

/// \brief  The linked list node structure.
///
/// This structure is the core of the linked list, holding the list element's
/// data and the pointer to the next node in the list.
typedef struct ll_node
{
    int data;               ///< The data stored in the linked list.
    struct ll_node *next;   ///< Pointer to tne next node in the list.
} ll_node;

ll_node *list_create_node(int data);
ll_node *list_find_data(ll_node *head, int data);
ll_node *list_find_tail_node(ll_node *head);
ll_node *list_append_node(ll_node **head, ll_node *node);
ll_node *list_append_data(ll_node **head, int data);
ll_node *list_insert_node(ll_node *after, ll_node *node);
ll_node *list_insert_data(ll_node *after, int data);
ll_node *list_prepend_node(ll_node **head, ll_node *node);
ll_node *list_prepend_data(ll_node **head, int data);
void list_remove_node(ll_node **head, ll_node *node);
void list_erase(ll_node **head);

#endif  // INC_LINKED_LIST
