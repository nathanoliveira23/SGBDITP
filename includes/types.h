/**********************************************
 * Types (arquivo de cabeçalho)
 *
 * Compilador: gcc
 *
 * Descrição: Definição de tipos que serão 
 *            utilizados por todo o programa.
 *
 **********************************************/

#ifndef TYPES_H
#define TYPES_H

typedef enum { INT, FLOAT, CHAR, STRING, PK } DATATYPE;

typedef struct column       COLUMN;
typedef union col_datatype  COL_DATATYPE;
typedef struct table        SQL_TABLE;

typedef unsigned int        uint;

#endif
