#ifndef NODE_H
#define NODE_H
#include <inttypes.h>

typedef struct node_s
{
    char* data_type;
    void* data;
    uint64_t edges_size;
    node_t* edges;
} node_t;

node_t* create_node(void);
void destroy_node(node_t*);

#endif