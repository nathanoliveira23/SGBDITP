/*****************************************************
 * sql_stmts (arquivo fonte)
 *
 * Compilador: GNU/gcc
 *
 * Descrição: Define funções que buscam implementar
 *            instruções da linguagem SQL.
 *
 * ***************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/types.h"
#include "../includes/sql_stmts.h"
#include "../includes/database.h"
#include "../includes/sql_helpers.h"
#include "../includes/tokenize.h"
#include "../includes/substring.h"

/*
 * Esta função recebe um texto e um valor inteiro ncols 
 * tal que ncols >= 0 e retorna um endereço de memória 
 * para uma estrutura de tabela SQL.
*/
SQL_TABLE* create_table(const char *tbname, size_t ncols)
{
    SQL_TABLE* tb = malloc(sizeof(SQL_TABLE));

    strcpy(tb->tname, tbname);
    tb->ncols = 0;
    tb->cols_storage = ncols;
    tb->column = malloc(ncols * sizeof(COLUMN));

    return tb;
}

/* 
 * Esta função recebe um texto como entrada e devolve um
 * endereço de memoria para uma coluna definida como PRIMARY KEY,
 * ou seja, ela é responsável apenas pela criação de uma coluna
 * do tipo PK.
*/
COLUMN* create_pk_column(const char* pkname)
{
    COLUMN* pkcol = malloc(sizeof(COLUMN));

    strcpy(pkcol->cname, pkname);

    pkcol->is_PK = true;
    pkcol->storage = 10;
    pkcol->nrows = 0;
    pkcol->typeof_column = PK;

    pkcol->data_type.pk = calloc(pkcol->storage, sizeof(uint));
    
    return pkcol;
}

/*
 * Esta função recebe um texto e um inteiro type, tal que
 * 0 <= type <= 3, e devolve um endereço de memoria para uma coluna.
 * Diferente da função anterior, esta função é responsável por criar
 * as demais colunas de uma tabela SQL.
 * 
*/ 
COLUMN* create_column(const char* colname, DATATYPE type)
{
    COLUMN* new_column = malloc(sizeof(COLUMN));

    strcpy(new_column->cname, colname);

    new_column->nrows = 0;
    new_column->storage = 10;
    new_column->is_PK = false;

    switch (type) {
        case INT:
            new_column->typeof_column = INT;
            new_column->data_type._int = malloc(new_column->storage * sizeof(int));
            break;
        case FLOAT:
            new_column->typeof_column = FLOAT;
            new_column->data_type._float = malloc(new_column->storage * sizeof(float));
            break;
        case CHAR:
            new_column->typeof_column = CHAR;
            new_column->data_type._char = malloc(new_column->storage * sizeof(char));
            break;
        case STRING:
            new_column->typeof_column = STRING;
            new_column->data_type._string = malloc(new_column->storage * sizeof(char*));

            for (size_t i = 0; i < new_column->storage; i++)
                new_column->data_type._string[i] = malloc(STRLEN * sizeof(char));
            break;
    }

    return new_column;
}

/*
 * Esta função recebe um ponteiro para uma tabela SQL e para uma coluna
 * e insere a coluna na tabela definida na entrada.
 *
*/
void add_column(SQL_TABLE* table, COLUMN col)
{
    size_t index = table->ncols;

    table->column[index] = col;
    table->ncols++;
}


/*
 * Esta função recebe um ponteiro para uma tabela, um inteiro e um ponteiro
 * generico para o tipo de dado da coluna. Esta função é responsável por 
 * inserir valores em todas as colunas da tabela e retorna true se a operação
 * foi bem sucedida ou, caso contrário, retorna false.
 *
*/
bool insert_into(SQL_TABLE* tb, size_t index, void* data)
{
    DATATYPE type = tb->column[index].typeof_column;
    COL_DATATYPE col = tb->column[index].data_type;
    size_t *i = &tb->column[index].nrows;

    switch (type) {
        case PK:
            col.pk[*i] = *(uint*) data;
            (*i)++;
            break;
        case INT:
            col._int[*i] = *(int*) data;
            (*i)++;
            break;
        case FLOAT:
            col._float[*i] = *(float*) data;
            (*i)++;
            break;
        case CHAR:
            col._char[*i] = *(char*) data;
            (*i)++;
            break;
    }
    
    return true;
}

/*
 * Esta função recebe um ponteiro para o bando de dados e um texto como entradas.
 * Esta função é responsável por imprimir informações de uma tabela SQL.
 * A função retorna true se a operação foi bem sucedida ou, caso contrário,
 * retorna dalse
 *
*/
bool select_table(const DATABASE* db, const char* tbname)
{
    SQL_TABLE* table = find_table_by_name(db, tbname);

    if (!exists_table(db, tbname))
        return false;

    draw_table(table);

    return true;
}

/*
 * Esta função recebe um ponteiro para um banco de dados e três strings
 * e imprime uma tabela conforme a condição estabelecida na entrada.
 *
*/
void select_all_tables(const DATABASE* db)
{
    if (db->n_tables == 0)
        return;

    size_t ntables = db->n_tables;
    
    for (size_t i = 0; i < ntables; i++)
        draw_table_header(&db->table[i]);
}


/*
 * Esta função recebe um ponteiro para um banco de dados e três strings
 * e imprime uma tabela conforme a condição estabelecida na entrada.
 *
*/
void select_where(const DATABASE* db, const char* tbname, char* condition)
{
    if (!exists_table(db, tbname))
        return;

    SQL_TABLE* table = find_table_by_name(db, tbname);
    COLUMN* col;
    DATATYPE type;

    char** tokens = tokenize(condition);
        
    int toi = atoi(tokens[2]);
    float tof = atof(tokens[2]);
    char toc = tokens[2][0];

    col = get_column(db, table->tname, tokens[0]);

    if (!exists_column(table, col))
        return;

    type = col->typeof_column;

    switch (type) {
        case PK:
            if (strcmp(tokens[1], "=") == 0) {
                draw_table_header(table);
                for (size_t i = 0; i < col->nrows; i++)
                    if (col->data_type.pk[i] == toi)
                        draw_row(table, i);
            }
            else if (strcmp(tokens[1], ">") == 0) {
                draw_table_header(table);
                for (size_t i = 0; i < col->nrows; i++)
                    if (col->data_type.pk[i] > toi)
                        draw_row(table, i);
            }
            else if (strcmp(tokens[1], ">=") == 0) {
                draw_table_header(table);
                for (size_t i = 0; i < col->nrows; i++)
                    if (col->data_type.pk[i] >= toi)
                        draw_row(table, i);
            }
            else if (strcmp(tokens[1], "<=") == 0) {
                draw_table_header(table);
                for (size_t i = 0; i < col->nrows; i++)
                    if (col->data_type.pk[i] <= toi)
                        draw_row(table, i);
            }
            break;

        case INT:
            if (strcmp(tokens[1], "=") == 0) {
                draw_table_header(table);
                for (size_t i = 0; i < col->nrows; i++)
                    if (col->data_type._int[i] == toi)
                        draw_row(table, i);
            }
            else if (strcmp(tokens[1], ">") == 0) {
                draw_table_header(table);
                for (size_t i = 0; i < col->nrows; i++)
                    if (col->data_type._int[i] > toi)
                        draw_row(table, i);
            }
            else if (strcmp(tokens[1], ">=") == 0) {
                draw_table_header(table);
                for (size_t i = 0; i < col->nrows; i++)
                    if (col->data_type._int[i] >= toi)
                        draw_row(table, i);
            }
            else if (strcmp(tokens[1], "<=") == 0) {
                draw_table_header(table);
                for (size_t i = 0; i < col->nrows; i++)
                    if (col->data_type._int[i] <= toi)
                        draw_row(table, i);
            }
            break;

        case FLOAT:
            if (strcmp(tokens[1], "=") == 0) {
                draw_table_header(table);
                for (size_t i = 0; i < col->nrows; i++)
                    if (col->data_type._float[i] == tof)
                        draw_row(table, i);
            }
            else if (strcmp(tokens[1], ">") == 0) {
                draw_table_header(table);
                for (size_t i = 0; i < col->nrows; i++)
                    if (col->data_type._float[i] > tof)
                        draw_row(table, i);
            }
            else if (strcmp(tokens[1], ">=") == 0) {
                draw_table_header(table);
                for (size_t i = 0; i < col->nrows; i++)
                    if (col->data_type._float[i] >= tof)
                        draw_row(table, i);
            }
            else if (strcmp(tokens[1], "<=") == 0) {
                draw_table_header(table);
                for (size_t i = 0; i < col->nrows; i++)
                    if (col->data_type._float[i] <= tof) 
                        draw_row(table, i);
            }
            break;

        case CHAR:
            if (strcmp(tokens[1], "=") == 0) {
                draw_table_header(table);
                for (size_t i = 0; i < col->nrows; i++) 
                    if (col->data_type._char[i] == toc) 
                        draw_row(table, i);
            }
            break;

        case STRING:
            if (strcmp(tokens[1], "=") == 0) {
                draw_table_header(table);
                for (size_t i = 0; i < col->nrows; i++)
                    if (is_include(col->data_type._string[i], tokens[2]))
                        draw_row(table, i);
            }
            break;
    }

    free_tokens(tokens);
}


/*
 * Esta função recebe um ponteiro para uma tabela e um inteiro pk tal que pk >= 0.
 * A função é responsável pela deleção de uma tupla de uma tabela SQL com base na chave primária
 * informada pelo usuário.
 *
*/ 
void delete_line(SQL_TABLE* table, uint id)
{
    DATATYPE type;
    size_t index = 0;
    size_t nrows = table->column[0].nrows;

    for (size_t i = 0; i < nrows; i++) {
        if (table->column[0].data_type.pk[i] == id) {
            index = i;
            break;
        }
    }
    
    for (size_t i = 0; i < table->ncols; i++) {
        type = table->column[i].typeof_column;

        for (size_t j = index; j < nrows; j++) 
            if (type == PK)
                table->column[i].data_type.pk[j] = table->column[i].data_type.pk[j + 1];
            else if (type == INT)
                table->column[i].data_type._int[j] = table->column[i].data_type._int[j + 1];
            else if (type == FLOAT)
                table->column[i].data_type._float[j] = table->column[i].data_type._float[j + 1];
            else if (type == CHAR)
                table->column[i].data_type._char[j] = table->column[i].data_type._char[j + 1];
            else if (type == STRING)
                strcpy(table->column[i].data_type._string[j], table->column[i].data_type._string[j + 1]);

        table->column[i].nrows--;
    }
}


/*
 * Esta função recebe um ponteiro para o banco de dados e um texto e é 
 * responsável por remover uma tabela de um banco de dados.
 * A função retorna true se a operação foi bem sucedida ou, caso contrário,
 * retorna false.
 *
*/ 
bool drop_table(DATABASE *db, const char* tbname)
{
    if (!exists_table(db, tbname))
        return false;

    SQL_TABLE* table = find_table_by_name(db, tbname);
    unsigned index = 0;

    for (size_t i = 0; i < db->n_tables; i++) {
        const char* temp_tb_name = db->table[i].tname;

        if (strcmp(table->tname, temp_tb_name) == 0) {
            index = i;
            break;
        }
    }

    for (size_t j = index; j < db->n_tables; j++) {
        db->table[j] = db->table[j + 1];
    }

    db->n_tables -= 1;
    remove_table(table);

    return true;
}
