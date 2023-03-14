#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include "libraries/data.h"
#include "libraries/stack/stack.h"
#include "libraries/list/list.h"

#define FILE_ARGUMENT_MANDATORY "File argument is mandatory!"
#define BRACKET_LEFT_BEHIND "Some bracket pair, '[' or ']', was left behind"
#define BRACKET_NOT_OPENED "Some bracket was not opened"
#define LACK_OF_MEMORY "Lack of memory"
#define SEGMENTATION_FAULT "Segmentation fault"

typedef struct loop_s{
    long position;
    int8_t* cell;
} loop_t;


bool is_loop(const char character, stack_t* verify_loop){
    if(character == '['){
        add_to_stack(verify_loop, "char*", sizeof(char) * 5, "loop");
        return true;
    }

    data_t item = pop_from_stack(verify_loop);
    bool status = item.status;
    destroy_data(&item, true);
    return status;
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
    if(verify_loop == NULL) return LACK_OF_MEMORY;

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
    fseek(file_pointer, 0, SEEK_SET);
    return NULL;
}

char* execute(FILE* file_pointer){
    char character = '\0';
    uint64_t current_position = 0;

    list_t* memory = create_list();
    if(memory == NULL) return LACK_OF_MEMORY;

    stack_t* stack = create_stack();
    if(stack == NULL){
        destroy_list(memory);
        return LACK_OF_MEMORY;
    }

    int a = 0;
    if(!add_to_list(memory, "int8_t", sizeof(int8_t), &a)){
        destroy_list(memory);
        destroy_stack(stack);
        return LACK_OF_MEMORY;
    }

    data_t item = {0};
    item = get_from_list(memory, current_position);
    while((character = fgetc(file_pointer)) != EOF){
        switch (character){
            case '+':
                *(int8_t*)item.data += 1;
                break;
            case '-':
                *(int8_t*)item.data -= 1;
                break;
            case '.':
                printf("%c", *(char*)item.data);
                break;
            case ',':
                *(int8_t*)item.data = (int8_t)getchar();
                break;
            case '>':
                current_position++;
                item = get_from_list(memory, current_position);
                if (!item.status){
                    if(!add_to_list(memory, "int8_t", sizeof(int8_t), &a)){
                        destroy_list(memory);
                        destroy_stack(stack);
                        return LACK_OF_MEMORY;
                    }
                    item = get_from_list(memory, current_position);
                }
                break;
            case '<':
                if (current_position <= 0){
                    destroy_list(memory);
                    destroy_stack(stack);
                    return SEGMENTATION_FAULT;
                }
                current_position--;
                item = get_from_list(memory, current_position);
                break;
            case '[': {
                loop_t loop_start = {0};
                loop_start.position = ftell(file_pointer);
                loop_start.cell = (int8_t*)item.data;
                add_to_stack(stack, "loop_t", sizeof(loop_t), &loop_start);
                break;
            }
            case ']': {
                data_t item = pop_from_stack(stack);
                loop_t* loop_end = (loop_t*)item.data;
                if(*loop_end->cell > 0){
                    add_to_stack(stack, "loop_t", sizeof(loop_t), loop_end);
                    fseek(file_pointer, loop_end->position, SEEK_SET);
                }
                destroy_data(&item, true);
                break;
            }
        }
    }

    destroy_list(memory);
    destroy_stack(stack);
    destroy_data(&item, false);
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
    
    const char* interpreter_error = validate_syntax(file_pointer);
    if(interpreter_error != NULL){
        fprintf(stderr, "[interpreter error] %s\n", interpreter_error);
        return 1;
    }

    const char* execution_error = execute(file_pointer);
    if(execution_error != NULL){
        fprintf(stderr, "[execution error] %s\n", execution_error);
        return 1;
    }

    fclose(file_pointer);
    return 0;
}
