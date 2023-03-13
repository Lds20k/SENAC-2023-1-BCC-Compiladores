#include <stdlib.h>
#include "data.h"

void destroy_data(data_t* item){
    if(item->data != NULL){
        free(item->data);
        item->data = NULL;
    }
    
    if(item->data_type != NULL){
        free(item->data_type);
    }

    item->data = NULL;
    item->data_type = NULL;
}