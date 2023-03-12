#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define FILE_NOT_FOUND "file not found!"

int main(int argc, char const *argv[])
{
    if(argc < 2){
        fprintf(stderr, "[arguments error] %s\n", FILE_NOT_FOUND);
        return 1;
    }

    FILE* file_pointer = fopen(argv[1], "r");
    if (file_pointer == NULL)
    {
        int errnum = errno;
        fprintf(stderr, "[error opening file] %s\n", strerror(errnum));
        return 1;
    }
    
    fclose(file_pointer);

    return 0;
}
