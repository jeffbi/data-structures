/// \file   double_linked_list.h
/// \brief  structure definition and function declarations for a doubly-linked list in C.
/// \author Jeffrey K. Bienstadt
/// \copyright  Copyright (c) 2021 Jeffrey K. Bienstadt

#ifndef INC_DOUBLE_LINKED_LIST_H
#define INC_DOUBLE_LINKED_LIST_H


/// \brief  The doubly-linked list node structure.
///
/// This structure is the core of the doubly-linked list,
/// holding the list node's data and the pointers to
/// the next and previouis nodes in the list.
typedef struct _dll_node
{
    int data;               ///< The data stored in the linked list.
    struct _dll_node *next; ///< Pointer to tne next node in the list.
    struct _dll_node *prev; ///< Pointer to tne previous node in the list.
} dll_node;

typedef enum {
    DLL_FORWARD,
    DLL_BACKWARD
} dll_direction;

dll_node *dll_create_node(int data);
dll_node *dll_find_data(dll_node *start, int data, dll_direction direction);
dll_node *dll_find_head_node(dll_node *start);
dll_node *dll_find_tail_node(dll_node *start);
dll_node *dll_append_node(dll_node **head, dll_node *node);
dll_node *dll_append_data(dll_node **head, int data);
dll_node *dll_insert_node_after(dll_node *after, dll_node *node);
dll_node *dll_insert_data_after(dll_node *after, int data);
dll_node *dll_insert_node_before(dll_node **before, dll_node *node);
dll_node *dll_insert_data_before(dll_node **before, int data);
dll_node *dll_prepend_node(dll_node **head, dll_node *node);
dll_node *dll_prepend_data(dll_node **head, int data);
void dll_remove_node(dll_node **head, dll_node *node);
void dll_erase(dll_node **head);

#endif  // INC_DOUBLE_LINKED_LIST_H
