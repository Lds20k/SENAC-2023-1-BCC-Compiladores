#ifndef LIST_H
#define LIST_H
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


stack_t create_stack();

void add(stack_t*, const char*, void*);
data_t pop(stack_t*);


#endif