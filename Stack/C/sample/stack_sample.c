
// Copyright (c) 2019 Jeffrey K. Bienstadt

#include <ctype.h>  // for isdigit, etc.
#include <stdio.h>
#include <time.h>

#include "../stack.h"

// Helper function to display the size of the stack
void print_stack_size(stack *stack)
{
    printf("Stack size is %d\n", stack_size(stack));
}

// Helper function to display the value on the top of the stack,
// or a message if the stack is empty.
void print_stack_top(stack *stack)
{
    if (stack_is_empty(stack))
        printf("The stack is empty.\n");
    else
        printf("Top of the stack has the value %d\n", stack_top(stack));
}

// A small helper function for use in evaluate_postfix (below), that determines
// if a character represents a binary arithmetic operator.
int is_bin_op(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

// Evaluate a postfix expression using a stack.
// This function demonstrates one use of a stack data structure.
// To keep things simple, only single-digit numbers are parsed.
void evaluate_postfix(const char *expression, int expected_result)
{
    printf("Evaluating postfix expression \"%s\"\n", expression);

    // create a new stack
    stack *stack = stack_create(20);

    while (*expression)
    {
        if (isdigit(*expression))
        {
            // convert the digit to a number and push onto the stack
            stack_push(stack, *expression - '0');
            print_stack_top(stack);
        }
        else if (is_bin_op(*expression))
        {
            // pop off the top two items on the stack into variables rhs and lhs

            int rhs = stack_top(stack);
            stack_pop(stack);
            print_stack_top(stack);

            int lhs = stack_top(stack);
            stack_pop(stack);
            print_stack_top(stack);

            printf("Evaluating %d %c %d\n", lhs, *expression, rhs);
            // evaluate the operation and push the result onto the stack
            switch (*expression)
            {
                case '+':
                    stack_push(stack, lhs + rhs);
                    print_stack_top(stack);
                    break;
                case '-':
                    stack_push(stack, lhs - rhs);
                    print_stack_top(stack);
                    break;
                case '*':
                    stack_push(stack, lhs * rhs);
                    print_stack_top(stack);
                    break;
                case '/':
                    stack_push(stack, lhs / rhs);
                    print_stack_top(stack);
                    break;
            }
        }

        ++expression;
    }

    if (stack_size(stack) == 1)
    {
        printf("Looks good, stack has one item left, the calculated result.\n");

        int result = stack_top(stack);
        stack_pop(stack);

        printf("Calculated result is %d, ", result);
        if (result == expected_result)
            printf("which is what we expected!\n");
        else
            printf("but we were expecting %d!\n", expected_result);
    }
    else
    {
        printf("Oops! Stack should have 1 item in it, but has %d instead!\n", stack_size(stack));
    }

    // delete the stack.
    stack_delete(stack);
}

int main(void)
{
    // create a new stack that can hold up to 10 integers
    stack *stack = stack_create(10);

    // show initial stack size
    print_stack_size(stack);

    // push some values onto the stack
    stack_push(stack, 42);
    stack_push(stack, 7);
    stack_push(stack, 1984);

    // print the value on the top of the stack
    print_stack_top(stack);

    // pop the previously pushed value off the stack
    stack_pop(stack);
    print_stack_top(stack);
    printf("Is top of stack now 7? %s\n", stack_top(stack) == 7 ? "yes" : "no");

    // delete this stack now that we're done with it.
    stack_delete(stack);

    // create a new stack that can hold 10,000,000 elements
    printf("Creating a 10,000,000 element stack.");
    stack = stack_create(10000000);
    if (stack == NULL)
    {
        printf("Failed to allocate a 10,000,000 element stack.");
        return -1;
    }

    time_t then;
    time_t now;

    printf("pushing 10,000,000 elements onto the stack\n");
    then = time(NULL);
    for (int i=0; i < 10000000; i++)
        stack_push(stack, i);
    now = time(NULL);
    printf("pushing took about %ld seconds\n", now - then);

    printf("popping 10,000,000 elements off the stack\n");
    then = time(NULL);
    for (int i=0; i < 10000000; i++)
        stack_pop(stack);
    now = time(NULL);
    printf("popping took about %ld seconds\n", now - then);

    printf("again pushing 10,000,000 elements onto the stack\n");
    then = time(NULL);
    for (int i=0; i < 10000000; i++)
        stack_push(stack, i);
    now = time(NULL);
    printf("pushing took about %ld seconds\n", now - then);

    printf("deleting a stack with 10,000,000 elements\n");
    then = time(NULL);
    stack_delete(stack);
    now = time(NULL);
    printf("deleting took about %ld seconds\n", now - then);


    // evaluate a postfix expresion.
    evaluate_postfix("9 2 8 * + 3 - 2 /", 11);
}