/**************************************************
 *
 * Database (arquivo fonte)
 *
 * Compilador: GNU/gcc
 *
 * Descrição: Modela uma strutura de banco de dados 
 *            para o armazenamento de tabelas SQL.
 *
 **************************************************/

#include <stdlib.h>
#include "../includes/database.h"

/*
 * Esta função recebe um inteiro nao negativo
 * e retorna um endereço de memória para uma
 * estrutura de banco de dados.
 *
*/ 
DATABASE* initialize(size_t storage)
{
    DATABASE* db = malloc(sizeof(DATABASE));

    db->storage = storage;
    db->n_tables = 0;
    db->table = malloc(storage * sizeof(SQL_TABLE));

    return db;
}

/*
 * Esta função recebe um ponteiro para um banco de dados
 * e uma tabela SQL e adiciona a tabela ao banco de dados.
 * A função retorna true e a operação foi bem sucedida ou,
 * caso contrário, retorna false.
 *
*/
bool add_table(DATABASE* db, SQL_TABLE tb)
{
    if (db->n_tables < db->storage) {
        db->table[db->n_tables++] = tb;
        return true;
    }
    else {
        db->storage *= 2;
        db->table = realloc(db->table, db->storage);
        db->table[db->n_tables++] = tb;
        return true;
    }

    return false;
}

/*
 * Esta função recebe um ponteiro para um banco de dados
 * e desaloca sua memória para evitar "memory leak"
 *
*/
void delete_database(DATABASE *db)
{
    for (size_t i = 0; i < db->n_tables; i++)
        free(&db->table[i]);
    free(db);
}

