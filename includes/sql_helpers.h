/***********************************************
 * SQL_helpers  (arquivo de cabeçlho)
 *
 * Compilador: GNU/gcc
 *
 * Descrição: Este arquivo define funções que
 *            auxiliam as instruções SQL e o
 *            gerenciamento do banco de dados.
 *
 ************************************************/


#ifndef SQL_HELPERS_H
#define SQL_HELPERS_H

#include <stddef.h>
#include "database.h"
#include "sql_table.h"
#include "types.h"

/*
 * Esta função recebe um ponteiro para o banco de dados
 * e um texto e retorna um endereço de memoria para uma
 * tabela SQL contida no banco de dados.
 *
*/
SQL_TABLE* find_table_by_name(const DATABASE* db, const char* tbname);


/*
 * Esta função recebe um ponteiro para o banco de dados e
 * um texto e retorna true se exisite uma tabela no banco
 * de dados ou, caso contrario, retorna false.
 *
*/
bool exists_table(const DATABASE* db, const char* tbname);


/*
 * Esta função recebe um ponteiro para uma tabela e para uma
 * coluna e retorna se uma coluna existe na tabela
 *
*/
bool exists_column(SQL_TABLE* table, COLUMN* column);



/*
 * Esta função recebe um ponteiro para um banco de dados e dois textos
 * e retorna um endereço de memoria para uma coluna de uma tabela SQL.
 *
*/
COLUMN* get_column(const DATABASE* db, const char* tbname, const char* colname);


/*
 * Esta função recebe um ponteiro para um banco de dados e um texto.
 * Ela é reponsável por verificar se ja existe uma tabela no banco de dados
 * com o mesmo nome recebido pela entrada.
 * A função retorna true se uma tabela com o mesmo nome ja existe ou, caso
 * contrario, retorna false.
 *
*/
bool verify_duplicated_tables(const DATABASE* db, const char* tbname);


/*
 * esta função é responsável por verificar a existência de uma chave primária
 * duplicada em uma coluna de uma tabela.
 *
 */
bool verify_PK(SQL_TABLE* tb, uint PK);


/*
 * conjunto de funções responsaveis por
 * desenhar uma tabela sql e imprimir para
 * o usuário.
 *
*/
void draw_table_header(SQL_TABLE* tb);
void draw_horizontal_line(int ncols); 
void draw_table(SQL_TABLE* tb);
void draw_row(SQL_TABLE* tb, size_t index); 


/*
 * Esta função recebe um ponteiro para uma tabela SQL 
 * e a remove do banco de dados.
 *
*/
void remove_table(SQL_TABLE* table);

#endif
