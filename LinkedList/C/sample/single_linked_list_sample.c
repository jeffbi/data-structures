// Copyright (c) 2019 Jeffrey K. Bienstadt

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../single_linked_list.h"

void traverse_list(const sll_node *head)
{
    printf("\nTraversing linked list\n");

    int n = 0;
    while (head != NULL)
    {
        printf("Node address = %p, Data = %d, next = %p\n", (void *)head, head->data, (void *)head->next);
        head = head->next;
        ++n;
    }

    printf("%d nodes in the list\n", n);
}

int main(void)
{
    sll_node *list_head = NULL;

    // List_head is a valid list, containing 0 elements.
    traverse_list(list_head);

    // We can create a new list simply by creating a new node.
    list_head = sll_create_node(42);
    traverse_list(list_head);

    // Erase the list.
    sll_erase(&list_head);

    // We can append to a list, even an empty one.
    sll_append_node(&list_head, sll_create_node(42));
    sll_append_data(&list_head, 123);
    traverse_list(list_head);

    // We can prepend to a list, creating a new head.
    sll_prepend_data(&list_head, 67);
    sll_prepend_node(&list_head, sll_create_node(4));
    traverse_list(list_head);

    // We can easily insert items into the middle of a list, without copying data.
    sll_node *node = sll_insert_node(sll_find_data(list_head, 42),
                                     sll_create_node(1001));
    node = sll_insert_data(node, 94);
    traverse_list(list_head);

    // We can remove a node from the list, also without copying data.
    node = sll_find_data(list_head, 42);
    sll_remove_node(&list_head, node);
    free(node); // We're responsible for freeing the memory for the node.
    traverse_list(list_head);

    // We can erase the entire list
    sll_erase(&list_head); // Memory for all nodes in the list is freed.
    traverse_list(list_head);

    time_t then;
    time_t now;

    printf("prepending 10,000,000 elements\n");
    then = time(NULL);
    for (int i=0; i < 10000000; i++)
        sll_prepend_data(&list_head, i);
    now = time(NULL);
    printf("prepending took about %ld seconds\n", now - then);

    printf("appending just 500 elements (this can take several minutes)\n");
    then = time(NULL);
    for (int i=0; i < 500; i++)
        sll_append_data(&list_head, i);
    now = time(NULL);
    printf("appending took about %ld seconds\n", now - then);

    // A faster way to append a lot of elements, using insert
    printf("appending 10,000,000 elements using insert\n");
    then = time(NULL);
    sll_node *last = sll_find_tail_node(list_head);
    for (int i=0; i < 10000000; i++)
        last = sll_insert_data(last, i);
    now = time(NULL);
    printf("appending via insert took about %ld seconds\n", now - then);

    then = time(NULL);
    printf("erasing 20,000,500 elements\n");
    sll_erase(&list_head);
    now = time(NULL);
    printf("erasing took about %ld seconds\n", now - then);

    return 0;
}
