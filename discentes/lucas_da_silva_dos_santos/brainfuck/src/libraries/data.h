#ifndef DATA_H
#define DATA_H

#include <stdbool.h>

typedef struct data_s{
    bool status;
    char* data_type;
    void* data;
} data_t;

void destroy_data(data_t*, bool);

#endif