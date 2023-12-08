#ifndef TOKENIZE_H
#define TOKENIZE_H

#include <stddef.h>

char** tokenize(char* str);
void free_tokens(char** tokens, size_t len);

#endif
