/**************************************************
 *
 * Database (arquivo de cabeçlho)
 *
 * Compilador: GNU/gcc
 *
 * Descrição: Modela uma strutura de banco de dados 
 *            para o armazenamento de tabelas SQL.
 *
 **************************************************/

#ifndef DATABASE_H
#define DATABASE_H

#include <stddef.h>
#include <stdbool.h>
#include "sql_table.h"

typedef struct database DATABASE;

struct database {
    SQL_TABLE*  table;      // Vetor de tabelas que serão armazenadas no banco de dados
    size_t      storage;    // Capacidade total de armazenamento de tabelas no bando de dados
    size_t      n_tables;   // Iterador que indica a próxima posição de inserção de uma tabela
};


/*
 * Esta função recebe um inteiro nao negativo
 * e retorna um endereço de memória para uma
 * estrutura de banco de dados.
 *
*/ 
DATABASE* initialize(size_t storage);


/*
 * Esta função recebe um ponteiro para um banco de dados
 * e uma tabela SQL e adiciona a tabela ao banco de dados.
 * A função retorna true e a operação foi bem sucedida ou,
 * caso contrário, retorna false.
 *
*/
bool add_table(DATABASE* db, SQL_TABLE tb);



/*
 * Esta função recebe um ponteiro para um banco de dados
 * e desaloca sua memória para evitar "memory leak"
 *
*/
void delete_database(DATABASE* db);

#endif
