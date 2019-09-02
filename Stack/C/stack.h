/// \file   stack.h
/// \brief  Structure definition and function declarations for a stack in C.
/// \author Jeffrey K. Bienstadt
/// \copyright  Copyright (c) 2019 Jeffrey K. Bienstadt

#ifndef INC_STACK
#define INC_STACK

/// \brief  A simple stack of integers.
typedef struct stack
{
    int capacity;   ///< stack capacity
    int top;        ///< current position of the top of the stack
    int *data;      ///< contents of the stack
} stack;

stack *stack_create(int capacity);
void stack_delete(stack *stack);
void stack_push(stack *stack, int value);
void stack_pop(stack *stack);
int stack_top(const stack *stack);
int stack_size(const stack *stack);
int stack_is_empty(const stack *stack);

#endif  // INC_STACK
