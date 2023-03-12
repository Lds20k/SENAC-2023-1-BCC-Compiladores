#ifndef LIST_H
#define LIST_H
#include <stdbool.h>
#include "../node/node.h"

typedef struct stack_s
{
    node_t* root;
} stack_t;

typedef struct data_s
{
    void* data_t;
    char* data_type;
} data_t;


stack_t* create_stack();

bool stack_is_empty(stack_t*);
void add_to_stack(stack_t*, const char*, void*);
data_t* pop_from_stack(stack_t*);


#endif