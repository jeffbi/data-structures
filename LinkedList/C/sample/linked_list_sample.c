// Copyright (c) 2019--2023 Jeffrey K. Bienstadt

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../single_linked_list.h"
#include "../double_linked_list.h"

void traverse_single_list(const sll_node *start)
{
    unsigned int n = 0u;

    printf("\nTraversing singly-linked list\n");

    while (start != NULL)
    {
        printf("Node address = %p, Data = %d, next = %p\n",
                (void *)start, start->data, (void *)start->next);
        start = start->next;
        ++n;
    }

    printf("%u nodes traversed\n", n);
}

unsigned int count_single_list(const sll_node *start)
{
    unsigned int n = 0u;

    while (start != NULL)
    {
        ++n;
        start = start->next;
    }

    return n;
}

void traverse_double_list(const dll_node *start, dll_direction direction)
{
    unsigned int n = 0u;

    printf("\nTraversing doubly-linked list, %s\n",
            direction == DLL_BACKWARD ? "backward" : "forward");

    while (start != NULL)
    {
        printf("Node address = %p, Data = %d, next = %p\n",
                (void *)start, start->data, (void *)start->next);
        start = direction == DLL_BACKWARD ? start->prev : start->next;
        ++n;
    }

    printf("%u nodes traversed\n", n);
}

unsigned int count_double_list(const dll_node *start, dll_direction direction)
{
    unsigned int n = 0u;

    while (start != NULL)
    {
        ++n;
        start = direction == DLL_BACKWARD ? start->prev : start->next;
    }

    return n;
}

void test_singly_linked_list()
{
    sll_node *list_head = NULL;
    sll_node *node = NULL;
    sll_node *last = NULL;
    time_t then;
    time_t now;
    unsigned int count = 0u;

    // List_head is a valid list, containing 0 elements.
    traverse_single_list(list_head);

    // We can create a new list simply by creating a new node.
    list_head = sll_create_node(42);
    traverse_single_list(list_head);

    // Erase the list.
    sll_erase(&list_head);

    // We can append to a list, even an empty one.
    sll_append_node(&list_head, sll_create_node(42));
    sll_append_data(&list_head, 123);
    traverse_single_list(list_head);

    // We can prepend to a list, creating a new head.
    sll_prepend_data(&list_head, 67);
    sll_prepend_node(&list_head, sll_create_node(4));
    traverse_single_list(list_head);

    // We can easily insert items into the middle of a list, without copying data.
    node = sll_insert_node_after(sll_find_data(list_head, 42),
                                 sll_create_node(1001));
    node = sll_insert_data_after(node, 94);
    traverse_single_list(list_head);

    // We can remove a node from the list, also without copying data.
    node = sll_find_data(list_head, 42);
    sll_remove_node(&list_head, node);
    free(node); // We're responsible for freeing the memory for the node.
    traverse_single_list(list_head);

    // We can erase the entire list
    sll_erase(&list_head); // Memory for all nodes in the list is freed.
    traverse_single_list(list_head);

    printf("prepending 10,000,000 elements\n");
    then = time(NULL);
    for (int i=0; i < 10000000; i++)
        sll_prepend_data(&list_head, i);
    now = time(NULL);
#if defined(_MSC_VER)
    printf("prepending took about %lld seconds\n", now - then);
#else
    printf("prepending took about %ld seconds\n", now - then);
#endif

    printf("appending just 500 elements (this can take quite a while)\n");
    then = time(NULL);
    for (int i=0; i < 500; i++)
        sll_append_data(&list_head, i);
    now = time(NULL);
#if defined(_MSC_VER)
    printf("appending took about %lld seconds\n", now - then);
#else
    printf("appending took about %ld seconds\n", now - then);
#endif

    // A faster way to append a lot of elements, using insert
    printf("appending 10,000,000 elements using insert\n");
    then = time(NULL);
    last = sll_find_tail_node(list_head);
    for (int i=0; i < 10000000; i++)
        last = sll_insert_data_after(last, i);
    now = time(NULL);
#if defined(_MSC_VER)
    printf("appending via insert took about %lld seconds\n", now - then);
#else
    printf("appending via insert took about %ld seconds\n", now - then);
#endif

    then = time(NULL);
    count = count_single_list(list_head);
    now = time(NULL);
#if defined(_MSC_VER)
    printf("counting (%u nodes) took about %lld seconds\n", count, now - then);
#else
    printf("counting (%u nodes) took about %ld seconds\n", count, now - then);
#endif

    printf("erasing 20,000,500 elements\n");
    then = time(NULL);
    sll_erase(&list_head);
    now = time(NULL);
#if defined(_MSC_VER)
    printf("erasing took about %lld seconds\n", now - then);
#else
    printf("erasing took about %ld seconds\n", now - then);
#endif
}

void test_doubly_linked_list()
{
    dll_node *list_head = NULL;
    dll_node *node = NULL;
    dll_node *last = NULL;
    time_t then;
    time_t now;
    unsigned int count = 0u;

    // List_head is a valid list, containing 0 elements.
    traverse_double_list(list_head, DLL_FORWARD);

    // We can create a new list simply by creating a new node.
    list_head = dll_create_node(42);
    traverse_double_list(list_head, DLL_FORWARD);

    // Erase the list.
    dll_erase(&list_head);

    // We can append to a list, even an empty one.
    dll_append_node(&list_head, dll_create_node(42));
    dll_append_data(&list_head, 123);
    traverse_double_list(list_head, DLL_FORWARD);

    // We can prepend to a list, creating a new head.
    dll_prepend_data(&list_head, 67);
    dll_prepend_node(&list_head, dll_create_node(4));
    traverse_double_list(list_head, DLL_FORWARD);

    // We can easily insert items into the middle of a list, without copying data.
    node = dll_insert_node_after(dll_find_data(list_head, 42, DLL_FORWARD),
                                 dll_create_node(1001));
    node = dll_insert_data_after(node, 94);
    traverse_double_list(list_head, DLL_FORWARD);

    // We can also insert before an item in a list.
    node = dll_insert_node_before(&list_head, dll_create_node(2002));
    node = dll_insert_data_before(&node, 106);
    traverse_double_list(list_head, DLL_FORWARD);

    // We can remove a node from the list, also without copying data.
    node = dll_find_data(list_head, 42, DLL_FORWARD);
    dll_remove_node(&list_head, node);
    free(node); // We're responsible for freeing the memory for the node.
    traverse_double_list(list_head, DLL_FORWARD);

    // We can erase the entire list
    dll_erase(&list_head); // Memory for all nodes in the list is freed.
    traverse_double_list(list_head, DLL_FORWARD);

    printf("prepending 10,000,000 elements\n");
    then = time(NULL);
    for (int i=0; i < 10000000; i++)
        dll_prepend_data(&list_head, i);
    now = time(NULL);
#if defined(_MSC_VER)
    printf("prepending took about %lld seconds\n", now - then);
#else
    printf("prepending took about %ld seconds\n", now - then);
#endif

    printf("appending just 500 elements (this can take quite a while)\n");
    then = time(NULL);
    for (int i=0; i < 500; i++)
        dll_append_data(&list_head, i);
    now = time(NULL);
#if defined(_MSC_VER)
    printf("appending took about %lld seconds\n", now - then);
#else
    printf("appending took about %ld seconds\n", now - then);
#endif

    // A faster way to append a lot of elements, using insert
    printf("appending 10,000,000 elements using insert\n");
    then = time(NULL);
    last = dll_find_tail_node(list_head);
    for (int i=0; i < 10000000; i++)
        last = dll_insert_data_after(last, i);
    now = time(NULL);
#if defined(_MSC_VER)
    printf("appending via insert took about %lld seconds\n", now - then);
#else
    printf("appending via insert took about %ld seconds\n", now - then);
#endif

    // We can traverse the entire list, both forward...
    // (we'll use count_double_list, it's quieter)
    then = time(NULL);
    count = count_double_list(list_head, DLL_FORWARD);
    now = time(NULL);
#if defined(_MSC_VER)
    printf("counting forward (%u nodes) took about %lld seconds\n", count, now - then);
#else
    printf("counting forward (%u nodes) took about %ld seconds\n", count, now - then);
#endif

    // ...and backward
    last = dll_find_tail_node(list_head);
    then = time(NULL);
    count = count_double_list(last, DLL_BACKWARD);
    now = time(NULL);
#if defined(_MSC_VER)
    printf("counting backward (%u nodes) took about %lld seconds\n", count, now - then);
#else
    printf("counting backward (%u nodes) took about %ld seconds\n", count, now - then);
#endif

    printf("erasing 20,000,500 elements\n");
    then = time(NULL);
    dll_erase(&list_head);
    now = time(NULL);
#if defined(_MSC_VER)
    printf("erasing took about %lld seconds\n", now - then);
#else
    printf("erasing took about %ld seconds\n", now - then);
#endif
}

int main(void)
{
    test_singly_linked_list();
    printf("\n\n=================================================\n\n");
    test_doubly_linked_list();

    return 0;
}
