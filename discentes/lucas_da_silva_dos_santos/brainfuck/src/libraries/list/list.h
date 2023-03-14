#ifndef LIST_H
#define LIST_H
#include <stdbool.h>
#include "../data.h"
#include "../node/node.h"

typedef enum direction_e {
    left = 0,
    rigth = 1,
} direction_t;

typedef struct list_s list_t;

list_t* create_list();

data_t get_from_list(list_t*, uint64_t);
bool add_to_list(list_t*, const char*, size_t, void*);

void destroy_list(list_t*);

#endif