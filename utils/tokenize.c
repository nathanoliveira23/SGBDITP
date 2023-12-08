#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "../includes/tokenize.h"

char** tokenize(char* str)
{
    size_t len = 2;
    char** tokens = malloc(len * sizeof(char*));
    char* token;

    for (int i = 0; i < len; i++)
        tokens[i] = calloc(50, sizeof(char));
    
    token = strtok(str, " ");

    size_t index = 0;
    while (token != NULL) {
        tokens[index++] = token;
        token = strtok(NULL, " ");
    }

    return tokens;
}

void free_tokens(char** tokens, size_t len)
{
    for (size_t i = 0; i < len; i++)
        free(tokens[i]);

    free(tokens);
}
