/***********************************************************
 * substring (arquivo fonte)
 *
 * Compilador: GNU/gcc
 *
 * Descrição: Define funções que verificam se determinado
 *            texto esta presente no texto original.
 *
 ***********************************************************/

#include <string.h>
#include <stdbool.h>
#include "../includes/substring.h"


/*
 * Esta função recebe como entrada duas strings
 * e verifica se a segunda string está presente na 
 * primeira.
 *
 */
bool is_include(char *str, char *sstr)
{
    return strstr(str, sstr);
}
