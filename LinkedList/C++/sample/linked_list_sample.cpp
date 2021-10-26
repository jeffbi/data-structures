// Copyright (c) 2019-2021 Jeffrey K. Bienstadt

#include <chrono>
#include <iostream>

#include "../SingleLinkedList.h"

template<typename T>
void traverse_list(T &list)
{
    std::cout << "Traversing linked list\n";

    int n = 0;
    for (auto &v : list)
    {
        std::cout << "Data = " << v << '\n';
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


    // Get an iterator for the first item in the list of doubles.
    auto it_beg = list.begin();

    // Print what the iterator refers to.
    std::cout << "Iterator has " << *it_beg << '\n';

    // Use an iterator to insert new elements.
    auto it_ins = list.insert_after(it_beg, 3.14);
    list.insert_after(it_ins, 2.71828);

    // Use the before-begin iterator to insert a new element before the head node
    list.insert_after(list.before_begin(), 1.414);
    traverse_list(list);
    // Also use it to remove the head node
    list.remove_after(list.before_begin());
    traverse_list(list);

    // We can use our simple iterators with the range-based for statement
    std::cout << "From range-based for loop:\n";
    for (auto &v : list)
        std::cout << v << '\n';

    // We can also manually traverse a list with iterators,
    // and use the iterator as a pointer to access an item's members
    std::cout << "Manual iteration:\n";
    for (auto iter = ab_list.begin(); iter != ab_list.end(); ++iter)
        std::cout << "member a: " << iter->a << ", member b: " << iter->b << '\n';

    list.clear();

    SingleLinkedList<int>   int_list;

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
    auto it_tail = int_list.tail();
    for (int i=0; i < 10000000; i++)
        it_tail = int_list.insert_after(it_tail, i);
    now = std::chrono::high_resolution_clock::now();

    std::cout << "appending via insert_after took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count()
              << " milliseconds\n";

    // erase all items in the list.
    then = std::chrono::high_resolution_clock::now();
    int_list.clear();
    now = std::chrono::high_resolution_clock::now();

    std::cout << "destroying 20,000,500 elements took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count()
              << " milliseconds\n";

}

int main()
{
    test_singly_linked_list();
}
