/// \file   single_linked_list.h
/// \brief  structure definition and function declarations for a singly-linked list in C.
/// \author Jeffrey K. Bienstadt
/// \copyright  Copyright (c) 2019 Jeffrey K. Bienstadt

#ifndef INC_SINGLE_LINKED_LIST_H
#define INC_SINGLE_LINKED_LIST_H

/// \brief  The singly-linked list node structure.
///
/// This structure is the core of the singly-linked list,
/// holding the list node's data and the pointer to
/// the next node in the list.
typedef struct _sll_node
{
    int data;               ///< The data stored in the linked list.
    struct _sll_node *next; ///< Pointer to tne next node in the list.
} sll_node;

sll_node *sll_create_node(int data);
sll_node *sll_find_data(sll_node *start, int data);
sll_node *sll_find_tail_node(sll_node *start);
sll_node *sll_append_node(sll_node **head, sll_node *node);
sll_node *sll_append_data(sll_node **head, int data);
sll_node *sll_insert_node_after(sll_node *after, sll_node *node);
sll_node *sll_insert_data_after(sll_node *after, int data);
sll_node *sll_prepend_node(sll_node **head, sll_node *node);
sll_node *sll_prepend_data(sll_node **head, int data);
void sll_remove_node(sll_node **head, sll_node *node);
void sll_erase(sll_node **head);

#endif  // INC_SINGLE_LINKED_LIST_H
