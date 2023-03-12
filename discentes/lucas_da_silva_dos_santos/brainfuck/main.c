#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define FILE_ARGUMENT_MANDATORY "File argument is mandatory!"

int main(int argc, char const *argv[])
{
    if(argc < 2){
        fprintf(stderr, "[arguments error] %s\n", FILE_ARGUMENT_MANDATORY);
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
