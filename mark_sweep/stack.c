#include "stack.h"
#include <stdlib.h>
#include <stdbool.h>

#define STACK_DEF_SIZE 16

stack_t *new_stack(size_t init_cap) {
    stack_t *st = malloc(sizeof(stack_t));
    if (!st) return NULL;

    st->capacity = (init_cap > 0) ? init_cap : STACK_DEF_SIZE;
    st->top = 0;
    st->count = 0;
    st->items = malloc(sizeof(void *) * st->capacity);
    
    if (!st->items) {
        free(st);
        return NULL;
/*************  ✨ Windsurf Command ⭐  *************/
/**
 * Frees all elements stored in the stack and then the stack itself.
 * 
 * This function iterates through each element in the stack, freeing
 * each one. After all elements are freed, it frees the memory used by
 * the stack's internal array, and finally the stack structure itself.
 * 
 * @param st Pointer to the stack to be freed. If this is NULL, the function
 *           does nothing.
 */

/*******  80fb0662-763d-4e46-a5e2-f6eaf4adcf96  *******/    }

    return st;
}

void stack_deep_drop(stack_t *st) {
    if (!st) return;

    for (size_t i = 0; i < st->top; i++) {
        free(st->items[i]);
    }

    free(st->items);
    free(st);
}

void stack_drop(stack_t *st) {
    if (!st) return;

    free(st->items);
    free(st);
}

bool stack_push(stack_t *st, void *item) {
    if (!st) return false;

    if (st->top >= st->capacity) {
        size_t new_cap = st->capacity * 2;
        void **tmp = realloc(st->items, sizeof(void *) * new_cap);
        if (!tmp) return false;

        st->items = tmp;
        st->capacity = new_cap;
    }

    st->items[st->top++] = item;
    st->count++;
    return true;
}

void *stack_pop(stack_t *st) {
    if (!st || st->top == 0) return NULL;

    st->count--;
    return st->items[--st->top];
}

void *stack_peep(stack_t *st) {
    if (!st || st->top == 0) return NULL;

    return st->items[st->top - 1];
}

bool stack_is_empty(stack_t *st) {
    return (!st || st->top == 0);
}

size_t stack_size(stack_t *st) {
    return st ? st->top : 0;
}
