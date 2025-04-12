#pragma once

#include <stdbool.h>
#include <stddef.h>

typedef struct  stack{
    void **items;
    size_t capacity;
    size_t top;
    size_t count;
}stack_t;


stack_t *new_stack(size_t init_cap);
void stack_drop(stack_t *st);
bool stack_push(stack_t *st, void *item);
void *stack_pop(stack_t *st);
void *stack_peep( stack_t *st);
bool stack_is_empty(stack_t *st);
size_t stack_size(stack_t *st);