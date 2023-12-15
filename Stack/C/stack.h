/// \file   stack.h
/// \brief  Structure definition and function declarations for a stack in C.
/// \author Jeffrey K. Bienstadt
/// \copyright  Copyright (c) 2022--2024 Jeffrey K. Bienstadt

#ifndef INC_STACK
#define INC_STACK

/// \brief  A simple stack of integers.
typedef struct stack
{
    size_t  capacity;   ///< stack capacity
    size_t  top;        ///< current position of the top of the stack
    int    *data;       ///< contents of the stack
} stack;

stack *stack_create(size_t capacity);
void stack_delete(stack *stack);
void stack_push(stack *stack, int value);
void stack_pop(stack *stack);
int stack_top(const stack *stack);
size_t stack_size(const stack *stack);
size_t stack_capacity(const stack *stack);
int stack_is_empty(const stack *stack);
int stack_is_full(const stack *stack);

#endif  // INC_STACK
