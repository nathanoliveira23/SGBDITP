/***********************************************************
 * substring (arquivo de cabeçalho)
 *
 * Compilador: GNU/gcc
 *
 * Descrição: Define funções que verificam se determinado
 *            texto esta presente no texto original.
 *
 ***********************************************************/

#ifndef SUBSTRING_H
#define SUBSTRING_H

/*
 * Esta função recebe como entrada duas strings
 * e verifica se a segunda string está presente na 
 * primeira.
 *
 */
bool is_include(char* str, char* sstr);

#endif
