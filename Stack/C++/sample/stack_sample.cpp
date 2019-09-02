#include <chrono>
#include <iostream>

#include "../Stack.h"

namespace {

// Helper function to display the size of the stack
inline void print_stack_size(Stack<int> &stack)
{
    std::cout << "Stack size is " << stack.size() << '\n';
}

// Helper function to display the value on the top of the stack,
// or a message if the stack is empty.
void print_stack_top(Stack<int> &stack)
{
    if (stack.is_empty())
        std::cout << "The stack is empty.\n";
    else
        std::cout << "Top of the stack has the value " << stack.top() << '\n';
}

// A small helper function for use in evaluate_postfix (below), that determines
// if a character represents a binary arithmetic operator.
inline bool is_bin_op(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

// Evaluate a postfix expression using a stack.
// This function demonstrates one use of a stack data structure.
// To keep things simple, only single-digit numbers are parsed.
void evaluate_postfix(const char *expression, int expected_result)
{
    std::cout << "Evaluating postfix expression \"" << expression << '\n';

    // create a new stack
    Stack<int> stack;

    while (*expression)
    {
        if (isdigit(*expression))
        {
            // convert the digit to a number and push onto the stack
            stack.push(*expression - '0');
            print_stack_top(stack);
        }
        else if (is_bin_op(*expression))
        {
            // pop off the top two items on the stack into variables rhs and lhs

            int rhs = stack.top();
            stack.pop();
            print_stack_top(stack);

            int lhs = stack.top();
            stack.pop();
            print_stack_top(stack);

            std::cout << "Evaluating " << lhs << ' ' << *expression << ' ' << rhs << '\n';

            // evaluate the operation and push the result onto the stack
            switch (*expression)
            {
                case '+':
                    stack.push(lhs + rhs);
                    print_stack_top(stack);
                    break;
                case '-':
                    stack.push(lhs - rhs);
                    print_stack_top(stack);
                    break;
                case '*':
                    stack.push(lhs * rhs);
                    print_stack_top(stack);
                    break;
                case '/':
                    stack.push(lhs / rhs);
                    print_stack_top(stack);
                    break;
            }
        }

        ++expression;
    }

    if (stack.size() == 1)
    {
        std::cout << "Looks good, stack has one item left, the calculated result.\n";

        int result = stack.top();
        stack.pop();

        std::cout << "Calculated result is " << result << ", ";
        if (result == expected_result)
            std::cout << "which is what we expected!\n";
        else
            std::cout << "but we were expecting " << expected_result << '\n';
    }
    else
    {
        std::cout << "Oops! Stack should have 1 item in it, but has "
                  << stack.size() << " instead!\n";
    }
}

} // end of anonymous namespace

int main()
{
    // create a new stack to store integers.
    // the stack is unbounded so it can contain as many elements as
    // available memory allows.
    Stack<int> stack;

    // show initial stack size
    print_stack_size(stack);

    // push some values onto the stack
    stack.push(42);
    stack.push(7);
    stack.push(1984);

    // print the value on the top of the stack
    print_stack_top(stack);

    // pop the previously pushed value off the stack
    stack.pop();
    print_stack_top(stack);
    std::cout << "Is top of stack now 7? " << (stack.top() == 7 ? "yes" : "no") << '\n';

    // pop off whatever elements are left on the stack
    while (stack.size())
        stack.pop();


    auto dthen = std::chrono::high_resolution_clock::now();
    
    {
        Stack<int>  stack2;

        std::cout << "pushing 10,000,000 elements onto the stack\n";
        auto then = std::chrono::high_resolution_clock::now();
        for (int i=0; i < 10000000; i++)
            stack2.push(i);
        auto now = std::chrono::high_resolution_clock::now();
        std::cout << "pushing took about "
                << std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count()
                << " milliseconds\n";

        printf("popping 10,000,000 elements off the stack\n");
        then = std::chrono::high_resolution_clock::now();
        for (int i=0; i < 10000000; i++)
            stack2.pop();
        now = std::chrono::high_resolution_clock::now();
        std::cout << "popping took about "
                << std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count()
                << " milliseconds\n";

        std::cout << "pushing 10,000,000 elements onto the stack\n";
        then = std::chrono::high_resolution_clock::now();
        for (int i=0; i < 10000000; i++)
            stack2.push(i);
        now = std::chrono::high_resolution_clock::now();
        std::cout << "pushing took about "
                << std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count()
                << " milliseconds\n";

        dthen = std::chrono::high_resolution_clock::now();
        std::cout << "destroying a stack with 10,000,000 elements\n";
    }
    auto dnow = std::chrono::high_resolution_clock::now();
    std::cout << "destruction took about "
              << std::chrono::duration_cast<std::chrono::milliseconds>(dnow - dthen).count()
              << " milliseconds\n";

    // evaluate a postfix expresion.
    evaluate_postfix("9 2 8 * + 3 - 2 /", 11);
}
