// Copyright (c) 2019-2021 Jeffrey K. Bienstadt

#include <chrono>
#include <iostream>

#include "../SingleLinkedList.h"

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

void test_singly_linked_list()
{
    // We can use our linked list with whatever type we need.
    SingleLinkedList<double> list;

    struct AB
    {
        int a;
        int b;
    };
    SingleLinkedList<AB> ab_list;

    traverse_list(list);

    list.append(98.6);
    
    traverse_list(list);

    // Append a couple of AB objects to our list of AB structures.
    ab_list.append({42, 9});
    ab_list.append({63, 80});


    // Use an iterator to insert new elements.
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
        std::cout << "Faild to find 42!\n";
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
}
