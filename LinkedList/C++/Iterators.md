# Enhancing the Linked List Iterator
This implementation uses a simple iterator to abstract away the underlying details of the Linked List. This iterator allows the list to be traversed using the C++ range-based `for` statement but is not compatible with the C++ standard library algorithms such as `std::find`. The minimal extra code to make them compatible with these algorithms doesn't contribute much to the fundamental understanding of a Linked List so it was not included in the implementation.

To enhance the Linked List to be compatible with the standard library algorithms, in `LinkedList.h` simply `#include <iterator>` at the top of the file, below the include guard, then add the following `using` declarations to the public interface of the `ListIterator` class:
```C++
    // These using declarations are required for our iterator to be usable
    // with the standard library algorithms such as std::find.
    using iterator_category = std::forward_iterator_tag;
	using value_type = T;
	using difference_type = ptrdiff_t;
	using pointer = value_type*;
	using reference = value_type&;
```
