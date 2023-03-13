#include <stdlib.h>
#include <string.h>
#include "stack.h"

typedef struct stack_s{
    node_t* root;
} stack_t;

#define STACK_T_SIZE sizeof(stack_t)

stack_t* create_stack(){
    stack_t* new_stack = (stack_t*) malloc(STACK_T_SIZE);
    if (new_stack == NULL) return NULL;
    memset(new_stack, 0, STACK_T_SIZE);

    return new_stack;
}

bool add_to_stack(stack_t* stack, const char* data_type, size_t data_size, void* data){
    node_t* node = create_node();
    if (node == NULL) return false;

    node->data_size = data_size;
    
    node->data_type = malloc(strlen(data_type));
    if(node->data_type == NULL){
        destroy_node(node);
        return false;
    }
    strcpy(node->data_type, data_type);
    
    node->data = malloc(data_size);
    if(node->data == NULL){
        destroy_node(node);
        return false;
    }
    memcpy(node->data, data, data_size);
    
    if (stack->root == NULL){
        stack->root = node;
    } else {
        node->edges_size++;
        node->edges = stack->root;
        stack->root = node;
    }

    return true;
}

data_t pop_from_stack(stack_t* stack){
    if(stack->root == NULL){
        data_t empty_data = {false, NULL, NULL};
        return empty_data;
    }

    node_t* node = stack->root;
    data_t item = {true, NULL, NULL};

    item.data = malloc(node->data_size);
    if(item.data == NULL){
        destroy_node(node);
        return item;
    }
    memcpy(item.data, node->data, node->data_size);

    item.data_type = malloc(strlen(node->data_type));
    if(item.data_type == NULL){
        destroy_node(node);
        free(item.data);
        item.data = NULL;
        return item;
    }
    strcpy(item.data_type, node->data_type);

    stack->root = (node->edges_size > 0) ? &(node->edges[0]) : NULL;
    destroy_node(node);

    return item;
}

bool stack_is_empty(stack_t* stack){
    return stack->root == NULL;
}

void destroy_stack(stack_t* stack){
    if (stack->root != NULL){
        node_t* node = stack->root;
        stack->root = (node->edges_size > 0) ? &(node->edges[0]) : NULL;

        destroy_node(node);
        destroy_stack(stack);
    } else free(stack);
}