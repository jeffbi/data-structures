// Copyright (c) 2019-2021 Jeffrey K. Bienstadt

#include <chrono>
#include <iostream>

#include "../SingleLinkedList.h"
#include "../DoubleLinkedList.h"

template<typename T>
void traverse_list(T &list)
{
    std::cout << "Traversing linked list\n";

    int n = 0;
    for (auto *node = list.head(); node; node = node->next())
    {
        std::cout << "Data = " << node->data() << '\n';
        ++n;
    }

    std::cout << n << " nodes in the list\n";
}

template<typename T>
void traverse_list_backward(T &list)
{
    std::cout << "Traversing linked list backward\n";

    int n = 0;
    for (auto *node = list.tail(); node; node = node->prev())
    {
        std::cout << "Data = " << node->data() << '\n';
        ++n;
    }

    std::cout << n << " nodes in the list\n";
}


struct AB
{
    int a;
    int b;
    friend bool operator==(const AB &lhs, const AB &rhs);
};
bool operator==(const AB &lhs, const AB &rhs)
{
    return lhs.a == rhs.a && lhs.b == rhs.b;
}

void test_singly_linked_list()
{
    std::cout << "Testing singly-linked list.\n";

    // We can use our linked list with whatever type we need.
    SingleLinkedList<double> list;
    SingleLinkedList<AB> ab_list;

    traverse_list(list);

    list.append(98.6);

    traverse_list(list);

    // Append a few AB objects to our list of AB structures.
    std::cout << "Append AB objects\n";
    std::cout << "  First append\n";
    ab_list.append({42, 9});
    std::cout << "  Second append\n";
    ab_list.append({63, 80});
    std::cout << "  Third append\n";
    ab_list.append({1960, 12});


    // Use insert_after to insert new elements.
    std::cout << "insert_after\n";
    auto head_node = list.head();
    list.insert_after(3.14, head_node);
    list.insert_after(2.71828, head_node);
    traverse_list(list);

    list.erase();

    SingleLinkedList<int>   int_list;

    // search the list for data items;
    int_list.append(100);
    int_list.append(200);
    int_list.append(42);
    int_list.append(316);
    int_list.append(5656);
    auto node_42 = int_list.find(42);
    if (node_42)
        std::cout << "Found " << node_42->data() << " in node " << static_cast<void *>(node_42) << '\n';
    else
        std::cout << "Failed to find 42!\n";

    auto node_ab_63_80 = ab_list.find({63,80});
    if (node_ab_63_80)
        std::cout << "Found {" << node_ab_63_80->data().a << ',' << node_ab_63_80->data().b << "} in node " << static_cast<void *>(node_ab_63_80) << '\n';
    else
        std::cout << "Failed to find {63,80}!\n";


    int_list.erase();

    std::cout << "prepending 10,000,000 elements\n";
    auto then = std::chrono::high_resolution_clock::now();
    // prepend 10 million elements to the front of the list
    for (int i=0; i < 10000000; ++i)
        int_list.prepend(i);
    auto now = std::chrono::high_resolution_clock::now();

    std::cout << "prepending took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count()
              << " milliseconds\n";


    std::cout << "appending just 500 elements (this can take quite a while)\n";
    then = std::chrono::high_resolution_clock::now();
    for (int i=0; i < 500; ++i)
        int_list.append(i)->data();
    now = std::chrono::high_resolution_clock::now();

    std::cout << "appending took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count()
              << " milliseconds\n";


    // A faster way to append a lot of elements, using insert_after
    std::cout << "appending 10,000,000 elements using insert_after\n";
    then = std::chrono::high_resolution_clock::now();
    auto tail_node = int_list.tail();
    for (int i=0; i < 10000000; i++)
        tail_node = int_list.insert_after(i, tail_node);
    now = std::chrono::high_resolution_clock::now();

    std::cout << "appending via insert_after took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count()
              << " milliseconds\n";

    // erase all items in the list.
    then = std::chrono::high_resolution_clock::now();
    int_list.erase();
    now = std::chrono::high_resolution_clock::now();

    std::cout << "destroying 20,000,500 elements took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count()
              << " milliseconds\n";
}

void test_doubly_linked_list()
{
    std::cout << "Testing doubly-linked list.\n";

    // We can use our linked list with whatever type we need.
    DoubleLinkedList<double> list;
    DoubleLinkedList<AB> ab_list;

    traverse_list(list);

    list.append(98.6);

    traverse_list(list);

    // Append a few AB objects to our list of AB structures.
    ab_list.append({42, 9});
    ab_list.append({63, 80});
    ab_list.append({1960, 12});


    // Use insert_after to insert new elements.
    auto head_node = list.head();
    list.insert_after(3.14, head_node);
    auto node_e = list.insert_after(2.71828, head_node);
    traverse_list(list);

    // A doubly-linked list can efficiently insert before a given node
    list.insert_before(1.41421, node_e);
    traverse_list(list);

    // A doubly-linked list can traverse the list backward
    traverse_list_backward(list);

    list.erase();

    DoubleLinkedList<int>   int_list;

    // search the list for data items;
    int_list.append(100);
    int_list.append(200);
    int_list.append(42);
    int_list.append(316);
    int_list.append(5656);
    auto node_42 = int_list.find(42);
    if (node_42)
        std::cout << "Found " << node_42->data() << " in node " << static_cast<void *>(node_42) << '\n';
    else
        std::cout << "Failed to find 42!\n";

    auto node_ab_63_80 = ab_list.find({63,80});
    if (node_ab_63_80)
        std::cout << "Found {" << node_ab_63_80->data().a << ',' << node_ab_63_80->data().b << "} in node " << static_cast<void *>(node_ab_63_80) << '\n';
    else
        std::cout << "Failed to find {63,80}!\n";


    int_list.erase();

    std::cout << "prepending 10,000,000 elements\n";
    auto then = std::chrono::high_resolution_clock::now();
    // prepend 10 million elements to the front of the list
    for (int i=0; i < 10000000; ++i)
        int_list.prepend(i);
    auto now = std::chrono::high_resolution_clock::now();

    std::cout << "prepending took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count()
              << " milliseconds\n";


    std::cout << "appending just 500 elements (this can take quite a while)\n";
    then = std::chrono::high_resolution_clock::now();
    for (int i=0; i < 500; ++i)
        int_list.append(i);
    now = std::chrono::high_resolution_clock::now();

    std::cout << "appending took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count()
              << " milliseconds\n";


    // A faster way to append a lot of elements, using insert_after
    std::cout << "appending 10,000,000 elements using insert_after\n";
    then = std::chrono::high_resolution_clock::now();
    auto tail_node = int_list.tail();
    for (int i=0; i < 10000000; i++)
        tail_node = int_list.insert_after(i, tail_node);
    now = std::chrono::high_resolution_clock::now();

    std::cout << "appending via insert_after took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count()
              << " milliseconds\n";

    // erase all items in the list.
    then = std::chrono::high_resolution_clock::now();
    int_list.erase();
    now = std::chrono::high_resolution_clock::now();

    std::cout << "destroying 20,000,500 elements took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count()
              << " milliseconds\n";
}

int main()
{
    test_singly_linked_list();
    std::cout << "\n\n";
    test_doubly_linked_list();
}
