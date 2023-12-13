/*****************************************************
 * sql_stmts (arquivo de cabeçlho)
 *
 * Compilador: GNU/gcc
 *
 * Descrição: Define funções que buscam implementar
 *            instruções da linguagem SQL.
 *
 * ***************************************************/


#ifndef SQL_STMST_H
#define SQL_STMST_H

#include "database.h"
#include "sql_table.h"
#include "types.h"


/*
 * Esta função recebe um texto e um valor inteiro ncols 
 * tal que ncols >= 0 e retorna um endereço de memória 
 * para uma estrutura de tabela SQL.
*/
SQL_TABLE* create_table(const char* tbname, size_t ncols);


/* 
 * Esta função recebe um texto como entrada e devolve um
 * endereço de memoria para uma coluna definida como PRIMARY KEY,
 * ou seja, ela é responsável apenas pela criação de uma coluna
 * do tipo PK.
*/
COLUMN* create_pk_column(const char* pkname);


/*
 * Esta função recebe um texto e um inteiro type, tal que
 * 0 <= type <= 3, e devolve um endereço de memoria para uma coluna.
 * Diferente da função anterior, esta função é responsável por criar
 * as demais colunas de uma tabela SQL.
 * 
*/ 
COLUMN* create_column(const char* colname, DATATYPE type);


/*
 * Esta função recebe um ponteiro para uma tabela SQL e para uma coluna
 * e insere a coluna na tabela definida na entrada.
 *
*/
void add_column(SQL_TABLE* table, COLUMN col);


/*
 * Esta função recebe um ponteiro para uma tabela, um inteiro e um ponteiro
 * generico para o tipo de dado da coluna. Esta função é responsável por 
 * inserir valores em todas as colunas da tabela e retorna true se a operação
 * foi bem sucedida ou, caso contrário, retorna false.
 *
*/
bool insert_into(SQL_TABLE* tb, size_t index, void *data);


/*
 * Esta função recebe um ponteiro para o bando de dados e um texto como entradas.
 * Esta função é responsável por imprimir informações de uma tabela SQL.
 * A função retorna true se a operação foi bem sucedida ou, caso contrário,
 * retorna dalse
 *
*/
bool select_table(const DATABASE* db, const char* tbname);


/*
 * Esta função recebe um ponteiro para um banco de dados e é responsável por 
 * listar todas a tabelas existentes.
 *
*/ 
void select_all_tables(const DATABASE* db);


/*
 * Esta função recebe um ponteiro para um banco de dados e três strings
 * e imprime uma tabela conforme a condição estabelecida na entrada.
 *
*/
void select_where(const DATABASE* db, const char* tbname, char* condition);


/*
 * Esta função recebe um ponteiro para uma tabela e um inteiro pk tal que pk >= 0.
 * A função é responsável pela deleção de uma tupla de uma tabela SQL com base na chave primária
 * informada pelo usuário.
 *
*/ 
void delete_line(SQL_TABLE* table, uint pk);


/*
 * Esta função recebe um ponteiro para o banco de dados e um texto e é 
 * responsável por remover uma tabela de um banco de dados.
 * A função retorna true se a operação foi bem sucedida ou, caso contrário,
 * retorna false.
 *
*/ 
bool drop_table(DATABASE* db, const char* tbname);

#endif
