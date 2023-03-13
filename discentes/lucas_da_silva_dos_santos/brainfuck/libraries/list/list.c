#include <stdlib.h>
#include <string.h>
#include "list.h"

typedef struct list_s
{
    uint64_t count;
    node_t* start;
    node_t* end; 
} list_t;

#define LIST_T_SIZE sizeof(list_t)

list_t* create_list(){
    list_t* new_list = malloc(LIST_T_SIZE);
    if (new_list == NULL) return NULL;
    memset(new_list, 0, LIST_T_SIZE);

    return new_list;
}

data_t get_from_list(list_t* list, uint64_t position){
    if(position >= list->count){
        data_t item = {false, NULL, NULL};
        return item;
    } 

    node_t* current = list->start;
    for (uint64_t i = 0; i < position; i++)
        current = &(current->edges[0]);
    
    data_t item = {0};
    item.status = true;

    item.data = current->data;
    item.data_type = current->data_type;

    return item;
}

bool add_to_list(list_t* list, const char* data_type, size_t data_size, void* data){
    list->count++;

    node_t* new_node = create_node();
    if (new_node == NULL) return false;

    new_node->data_size = data_size;

    new_node->data_type = malloc(strlen(data_type));
    if(new_node->data_type == NULL){
        destroy_node(new_node);
        return false;
    }
    strcpy(new_node->data_type, data_type);

    new_node->data = malloc(data_size);
    if(new_node->data == NULL){
        destroy_node(new_node);
        return false;
    }
    memcpy(new_node->data, data, data_size);

    if (list->start == NULL){
        list->start = list->end = new_node;
    } else {
        node_t* node = list->end;
        node->edges_size = 1;
        node->edges = new_node;
        list->end = new_node;
    }

    return true;
}

void destroy_list(list_t* list){
    if (list->start != NULL){
        node_t* node = list->start;
        list->start = (node->edges_size > 0) ? &(node->edges[0]) : NULL;

        destroy_node(node);
        destroy_list(list);
    } else free(list);
}