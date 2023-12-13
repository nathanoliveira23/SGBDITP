/*********************************************************
 * tokenize (arquivo fonte)
 *
 * Compilador: GNU/gcc
 *
 * Descrição: Contém definições de funções utilitarias
 *            de manipulação de strings que auxiliam no
 *            tratamento de entradas do usuário.
 *
 *********************************************************/

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "../includes/tokenize.h"

/*
 * Esta função recebe um texto e o fragmenta em 
 * tokens que serão armazenados em um vetor de strings.
 * Seu objetivo é auxiliar na busca de uma tabela através
 * de uma condição introduzida pelo usuário para que cada 
 * seja tratada pelas instruções SQL.
 *
 * A função aloca uma matriz de 3 posições pois a entrada
 * é composta por 3 strings: Nome da tabela, operador e valor.
 *
 * Segue o exemplo de uso abaixo
 *
 * Exemplo de entrada:
 *
 *      str = "id > 5"
 *
 * Saída: ["id", ">", "5"]
 *
 */
char** tokenize(char* str)
{
    char** tokens = malloc(N_TOKENS * sizeof(char*));
    char* token;

    for (int i = 0; i < N_TOKENS; i++)
        tokens[i] = malloc(TOKEN_SIZE * sizeof(char));
    
    token = strtok(str, " ");

    size_t index = 0;
    while (token != NULL) {
        strcpy(tokens[index++], token);
        token = strtok(NULL, " ");
    }

    return tokens;
}


/*
 * Esta função recebe um vetor de strings 
 * desaloca a memória alocada pela função tokenize.
 *
 */
void free_tokens(char** tokens)
{
    for (size_t i = 0; i < N_TOKENS; i++)
        free(tokens[i]);

    free(tokens);
}
