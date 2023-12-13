/*********************************************************
 * clear_screen (arquivo fonte)
 *
 * Compilador: GNU/gcc
 *
 * Descrição: Define uma função de "limpeza" de caracteres
 *            do terminal.
 *
 ********************************************************/

#include <stdlib.h>
#include "../includes/clear_screen.h"

void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
