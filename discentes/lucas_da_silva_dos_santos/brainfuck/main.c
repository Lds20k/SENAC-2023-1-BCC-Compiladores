#include <stdio.h>
#include <stdlib.h>

#define FILE_NOT_FOUND "file not found!"

int main(int argc, char const *argv[])
{
    if(argc < 2){
        fprintf(stderr, "error: %s\n", FILE_NOT_FOUND);
        return -1;
    }

    printf("%s\n", argv[1]);

    return 0;
}
