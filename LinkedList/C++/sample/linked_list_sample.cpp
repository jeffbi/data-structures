// Copyright (c) 2019 Jeffrey K. Bienstadt

#include <chrono>
#include <iostream>

#include "../LinkedList.h"

template<typename T>
void traverse_list(LinkedList<T> &list)
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

int main()
{
    LinkedList<int> list;

    traverse_list(list);

    list.append(42);
    traverse_list(list);

    auto it_b = list.begin();

    auto it = list.insert_after(it_b, 7);
    list.insert_after(it, 314);

    // We can use our simple iterators with the range-based for statement
    for (auto &v : list)
    {
        std::cout << v << '\n';
    }

    list.erase();

    std::chrono::high_resolution_clock::time_point dthen;

    {
        LinkedList<int> list2;

        std::cout << "prepending 10,000,000 elements\n";
        auto then = std::chrono::high_resolution_clock::now();
        // prepend 10 million elements to the front of the list
        for (int i=0; i < 10000000; ++i)
            list2.prepend(i);
        auto now = std::chrono::high_resolution_clock::now();

        std::cout << "prepending took "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count()
                  << " milliseconds\n";

        std::cout << "appending just 500 elements (this can take several minutes)\n";
        then = std::chrono::high_resolution_clock::now();
        for (int i=0; i < 500; ++i)
            list2.append(i);
        now = std::chrono::high_resolution_clock::now();

        std::cout << "appending took "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count()
                  << " milliseconds\n";


        // A faster way to append a lot of elements, using insert_after
        std::cout << "appending 10,000,000 elements using insert_after\n";
        then = std::chrono::high_resolution_clock::now();
        auto it = list2.tail();
        for (int i=0; i < 10000000; i++)
            it = list.insert_after(it, i);
        now = std::chrono::high_resolution_clock::now();

        std::cout << "appending via insert_after took "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count()
                  << " milliseconds\n";

        dthen = std::chrono::high_resolution_clock::now();
    }

    auto dnow = std::chrono::high_resolution_clock::now();

    std::cout << "destroying 20,000,500 elements took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(dnow - dthen).count()
              << " milliseconds\n";
}
