#include <stdlib.h>
#include <string.h>
#include "node.h"

#define NODE_T_SIZE sizeof(node_t)

node_t* create_node(void){
    node_t* new_node = (node_t*) malloc(NODE_T_SIZE);
    if (new_node == NULL) return NULL;
    memset(new_node, 0, NODE_T_SIZE);

    return new_node;
}

void destroy_node(node_t* node){
    if (node->data_type != NULL) free(node->data_type);
    if (node->data != NULL) free(node->data);
    
    node->edges_size = 0;
    free(node);
}
