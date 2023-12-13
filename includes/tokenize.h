/*********************************************************
 * tokenize (arquivo de cabeçalho)
 *
 * Compilador: GNU/gcc
 *
 * Descrição: Contém definições de funções utilitarias
 *            de manipulação de strings que auxiliam no
 *            tratamento de entradas do usuário.
 *
 *********************************************************/

#ifndef TOKENIZE_H
#define TOKENIZE_H

#include <stddef.h>

#define N_TOKENS    3
#define TOKEN_SIZE 20
/*
 * Esta função recebe um texto e o fragmenta em 
 * tokens que serão armazenados em um vetor de strings.
 * Seu objetivo é auxiliar na busca de uma tabela através
 * de uma condição introduzida pelo usuário para que cada 
 * seja tratada pelas instruções SQL.
 *
 */
char** tokenize(char* str);


/*
 * Esta função recebe um vetor de strings 
 * desaloca a memória alocada pela função tokenize.
 *
 */
void free_tokens(char** tokens);

#endif
