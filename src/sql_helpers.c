/***********************************************
 * SQL_helpers  (arquivo fonte)
 *
 * Compilador: GNU/gcc
 *
 * Descrição: Este arquivo define funções que
 *            auxiliam as instruções SQL e o
 *            gerenciamento do banco de dados.
 *
 ************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "../includes/sql_helpers.h"

#define COLUMN_WIDTH 20

/*
 * Esta função recebe um ponteiro para o banco de dados e
 * um texto e retorna true se exisite uma tabela no banco
 * de dados ou, caso contrario, retorna false.
 *
*/
bool exists_table(const DATABASE* db, const char* tbname)
{
    size_t ntables = db->n_tables;
    char* temp_name;
    bool exists;

    for (size_t i = 0; i < ntables; i++) {
        temp_name = db->table[i].tname;
        exists = !strcmp(temp_name, tbname);

        if (exists)
            return true;
    }

    return false;
}

bool exists_column(SQL_TABLE* table, COLUMN* column)
{
    size_t ncols = table->ncols;
    bool found;

    for (size_t i = 0; i < ncols; i++) {
        found = !strcmp(table->column[i].cname, column->cname);

        if (found)
            return true;
    }
        
    return false;
}

/*
 * Esta função recebe um ponteiro para o banco de dados
 * e um texto e retorna um endereço de memoria para uma
 * tabela SQL contida no banco de dados.
 *
*/
SQL_TABLE* find_table_by_name(const DATABASE* db, const char* tbname)
{
    if (!exists_table(db, tbname))
        return NULL;

    size_t ntables = db->n_tables;
    bool found;

    for (size_t i = 0; i < ntables; i++) {
        found = !strcmp(db->table[i].tname, tbname);

        if (found)
            return &db->table[i];
    }

    return NULL;
}


/*
 * Esta função recebe um ponteiro para um banco de dados e dois textos
 * e retorna um endereço de memoria para uma coluna de uma tabela SQL.
 *
*/
COLUMN* get_column(const DATABASE* db, const char* tbname, const char* colname)
{
    if (!exists_table(db, tbname))
        return NULL;

    SQL_TABLE* table = find_table_by_name(db, tbname);
    size_t ncols = table->ncols;
    bool found;

    for (size_t i = 0; i < ncols; i++) {
        found = !strcmp(table->column[i].cname, colname);

        if (found)
            return &table->column[i];
    }

    return NULL;
}

/*
 * conjunto de funções responsaveis por
 * desenhar uma tabela sql e imprimir para
 * o usuário.
 *
*/
void draw_horizontal_line(int ncols) {
    int i;
    for (i = 0; i < ncols; i++) {
        printf("+");
        for (int j = 0; j < COLUMN_WIDTH + 2; j++) {
            printf("-");
        }
    }
    printf("+\n");
}

void draw_table_header(SQL_TABLE* tb) {
    draw_horizontal_line(tb->ncols);

    printf("| %-*s|\n", (int)tb->ncols * (COLUMN_WIDTH + 3) - 2, tb->tname);

    draw_horizontal_line(tb->ncols);

    printf("|");
    for (int i = 0; i < tb->ncols; i++) {
        printf(" %-*s |", COLUMN_WIDTH, tb->column[i].cname);
    }
    printf("\n");

    draw_horizontal_line(tb->ncols);
}

void draw_row(SQL_TABLE* tb, size_t index) {
    size_t ncols = tb->ncols;
    DATATYPE type;

    printf("|");
    for (int i = 0; i < ncols; i++) {
        type = tb->column[i].typeof_column;
        if (type == PK) 
            printf(" %-*u |", COLUMN_WIDTH, tb->column[i].data_type.pk[index]);
        else if (type == INT) 
            printf(" %-*d |", COLUMN_WIDTH, tb->column[i].data_type._int[index]);
        else if (type == FLOAT) 
            printf(" %-*.2f |", COLUMN_WIDTH, tb->column[i].data_type._float[index]);
        else if (type == CHAR) 
            printf(" %-*c |", COLUMN_WIDTH, tb->column[i].data_type._char[index]);
        else if (type == STRING) 
            printf(" %-*s |", COLUMN_WIDTH, tb->column[i].data_type._string[index]);
    }
    printf("\n");

    draw_horizontal_line(tb->ncols);
}

void draw_table(SQL_TABLE* tb)
{
    draw_table_header(tb);
    size_t rows = tb->column[0].nrows;
    
    for (int i = 0; i < rows; ++i)
        draw_row(tb, i);
}
/************************************************************************************/

/*
 * Esta função recebe um ponteiro para um banco de dados e um texto.
 * Ela é reponsável por verificar se ja existe uma tabela no banco de dados
 * com o mesmo nome recebido pela entrada.
 * A função retorna true se uma tabela com o mesmo nome ja existe ou, caso
 * contrario, retorna false.
 *
*/
bool verify_duplicated_tables(const DATABASE* db, const char *tbname)
{
    size_t ntables = db->n_tables;
    bool duplicated;

    for (size_t i = 0; i < ntables; i++) {
        duplicated = !strcmp(tbname, db->table[i].tname);

        if (duplicated)
            return true;
    }

    return false;
}

/*
 * esta função é responsável por verificar a existência de uma chave primária
 * duplicada em uma coluna de uma tabela.
 *
 */
bool verify_PK(SQL_TABLE* tb, uint PK)
{
    size_t nrows = tb->column[0].nrows;
    bool duplicated;

    for (size_t i = 0; i < nrows; i++) {
        duplicated = tb->column->data_type.pk[i] == PK;

        if (duplicated)
            return true;
    }

    return false;
}

/*
 * Esta função recebe um ponteiro para uma tabela SQL 
 * e a remove do banco de dados.
 *
*/
void remove_table(SQL_TABLE *table)
{
    size_t ncols = table->ncols;
    DATATYPE type;

    for (size_t i = 0; i < ncols; i++) {
        type = table->column[i].typeof_column;

        if (type == PK) {
            free(table->column[i].data_type.pk);
        }
        else if (type == INT) {
            free(table->column[i].data_type._int);
        }
        else if (type == FLOAT) {
            free(table->column[i].data_type._float);
        }
        else if (type == CHAR) {
            free(table->column[i].data_type._char);
        }
        else if (type == STRING) {
            for (size_t j = 0; j < table->column[i].nrows; j++)
                free(table->column[i].data_type._string[j]);

            free(table->column[i].data_type._string);
        }
    }

    free(table->column);

    free(table);
}
