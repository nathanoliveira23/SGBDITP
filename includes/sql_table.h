/**************************************************
 *
 * SLQ_table (arquivo de cabeçlho)
 *
 * Compilador: gcc
 *
 * Descrição: Modelagem de uma tabela SQL que será
 *            armazenada em um banco de dados.
 *
 ***************************************************/

#ifndef SQL_TABLE_H
#define SQL_TABLE_H

#include <stddef.h>
#include <stdbool.h>
#include "types.h"

#define STRLEN 50

/*
 * Esta estrutura será utilizada para definir
 * um vetor para o tipo de dado definido para 
 * a coluna.
*/ 
union col_datatype {
    uint        *pk;
    char        *_char;
    char        **_string;
    int         *_int;
    float       *_float;
};

struct column {
    char            cname[STRLEN];      // Nome da coluna
    bool            is_PK;              // Indica se uma coluna é ou não chave primária
    size_t          nrows;              // Iterador que indica a próxima linha na qual um dado será inserido
    size_t          storage;            // Capacidade total de armazenameto de dados de uma coluna
    DATATYPE        typeof_column;      // Indica qual o tipo de dado de uma coluna (INT, FLOAT, CHAR, STRING, PK)
    COL_DATATYPE    data_type;          // Tipo de dado que a coluna armazenará
};

struct table {
    char    tname[STRLEN];              // Nome da tabela
    size_t  ncols;                      // Iterador que indicará a próxima posição que será inserida uma coluna
    size_t  cols_storage;               // Capacidade total de colunas em uma tabela
    COLUMN  *column;                    // Coleção de colunas
};

#endif
