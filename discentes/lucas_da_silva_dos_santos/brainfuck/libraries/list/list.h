#ifndef LIST_H
#define LIST_H
#include "../node/node.h"

typedef enum direction_e {
    left = 0,
    rigth = 1,
} direction_t;

typedef struct list_s
{
    node_t* start;
    node_t* end; 
} list_t;

node_t* get(list_t, uint64_t);
node_t* add(list_t);
#endif