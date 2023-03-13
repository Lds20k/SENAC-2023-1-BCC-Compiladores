#ifndef STACK_H
#define STACK_H
#include <stdbool.h>
#include "../data.h"
#include "../node/node.h"

typedef struct stack_s stack_t;

stack_t* create_stack();

bool add_to_stack(stack_t*, const char*, size_t, void*);
data_t pop_from_stack(stack_t*);

bool stack_is_empty(stack_t*);
void destroy_stack(stack_t*);

#endif