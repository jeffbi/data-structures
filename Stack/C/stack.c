/// \file   stack.c
/// \brief  Implementation of a simple stack in C.
/// \author Jeffrey K. Bienstadt
/// \copyright  Copyright (c) 2022--2024 Jeffrey K. Bienstadt

#include <assert.h>
#include <stdlib.h>     // for malloc/free

#include "stack.h"

/// \brief  Create a new stack with the specified capacity
///
/// \param capacity The maximum size of this stack.
///
/// \return A pointer to a new stack, or NULL if memory could not be allocated.
stack *stack_create(size_t capacity)
{
    stack *new_stack = (stack *)malloc(sizeof(stack));
    if (new_stack == NULL)
        return NULL;

    new_stack->capacity = capacity;
    new_stack->top = (size_t)0;
    new_stack->data = (int *)malloc(capacity * sizeof(int));
    if (new_stack->data == NULL)
    {
        free(new_stack);
        return NULL;
    }

    return new_stack;
}

/// \brief  Delete a stack, freeing its memory.
///
/// \param stack    Pointer to the stack to be deleted.
void stack_delete(stack *stack)
{
    free(stack->data);
    free(stack);
}

/// \brief  Push a new item onto the top of the stack.
///
/// \param stack    Pointer to the stack.
/// \param value    Data item to be stored in the stack.
void stack_push(stack *stack, int value)
{
    assert(!stack_is_full(stack));

    stack->data[stack->top++] = value;
}

/// \brief  Pop an item off of the top of the stack.
///
/// \param stack    Pointer to the stack.
void stack_pop(stack *stack)
{
    assert(!stack_is_empty(stack));

    --stack->top;
}

/// \brief  Return the top item on the stack.
///
/// \param stack    Pointer to the stack.
///
/// \return The value of the item currently on the top of the stack.
int stack_top(const stack *stack)
{
    assert(!stack_is_empty(stack));

    return stack->data[stack->top-1];
}

/// \brief  Return the size of the stack.
///
/// \param stack    Pointer to the stack.
///
/// \return The number of items currently on the stack.
size_t stack_size(const stack *stack)
{
    return stack->top;
}

/// \brief  Return the capacity of the stack.
///
/// \param stack    Pointer to the stack.
///
/// \return The mazimum number of items that can be stored in the stack.
size_t stack_capacity(const stack *stack)
{
    return stack->capacity;
}

/// \brief  Determine if the stack is empty.
///
/// \param stack    Pointer to the stack.
///
/// \return Non-zero if the stack is empty, zero otherwise.
int stack_is_empty(const stack *stack)
{
    return stack->top == 0;
}

/// \brief  Determine if the stack is full.
///
/// \param stack    Pointer to the stack.
///
/// \return Non-zero if the stack is full, zero otherwise.
int stack_is_full(const stack *stack)
{
    return stack->top == stack->capacity;
}
