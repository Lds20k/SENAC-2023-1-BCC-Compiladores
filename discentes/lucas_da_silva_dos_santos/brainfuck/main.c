#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include "libraries/stack/stack.h"

#define FILE_ARGUMENT_MANDATORY "File argument is mandatory!"
#define BRACKET_LEFT_BEHIND "Some bracket pair, '[' or ']', was left behind"
#define BRACKET_NOT_OPENED "Some bracket was not opened"

bool is_loop(const char character, stack_t* verify_loop){
    if(character == '['){
        add_to_stack(verify_loop, "string", sizeof(char) * 5, "loop");
        return true;
    }

    data_t item = pop_from_stack(verify_loop);
    destroy_data(&item);    
    return item.status;
}

extern inline bool is_bracket(const char character){
    return character == '[' || character == ']';
}

extern inline bool is_valid_character(const char character){
    // Valid character
    // 43| 44| 45| 46 | brackets
    // + | , | - |  . | [      ]
    return (character > 42 && character < 47) || is_bracket(character);
}

char* validate_syntax(FILE* file_pointer){
    char character = '\0';
    stack_t* verify_loop = create_stack();
    while((character = fgetc(file_pointer)) != EOF){
        if(is_bracket(character)){
            if(!is_loop(character, verify_loop))
            {
                destroy_stack(verify_loop);
                return BRACKET_NOT_OPENED;
            }
        }
    }
    
    if (!stack_is_empty(verify_loop)){
        destroy_stack(verify_loop);
        return BRACKET_LEFT_BEHIND;
    }

    destroy_stack(verify_loop);
    return NULL;
}

int main(int argc, char const *argv[])
{
    if(argc < 2){
        fprintf(stderr, "[arguments error] %s\n", FILE_ARGUMENT_MANDATORY);
        return 1;
    }

    FILE* file_pointer = fopen(argv[1], "r");
    if(file_pointer == NULL){
        int errnum = errno;
        fprintf(stderr, "[error opening file] %s\n", strerror(errnum));
        return 1;
    }
    
    const char* error = validate_syntax(file_pointer);
    if(error != NULL){
        fprintf(stderr, "[interpreter error] %s\n", error);
        return 1;
    }

    fclose(file_pointer);
    return 0;
}
