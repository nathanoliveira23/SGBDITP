#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/sql_stmts.h"
#include "../includes/database.h"
#include "../includes/sql_helpers.h"
#include "../includes/tokenize.h"

SQL_TABLE* create_table(const char *tbname, const char* pkcol)
{
    SQL_TABLE* tb = malloc(sizeof(SQL_TABLE));

    strcpy(tb->tname, tbname);
    tb->ncols = 0;
    tb->cols_storage = 10;
    tb->has_PK = false;
    tb->column = malloc(tb->cols_storage * sizeof(COLUMN));

    return tb;
}

COLUMN* create_column(const char* colname, DATATYPE type, bool isPK)
{
    COLUMN* new_column = malloc(sizeof(COLUMN));

    strcpy(new_column->cname, colname);

    new_column->nlines = 0;
    new_column->storage = 10;
    new_column->is_PK = isPK;

    switch (type) {
        case INT:
            new_column->typeof_column = INT;
            new_column->data_type.int_datatype = malloc(new_column->storage * sizeof(int));
            break;
        case FLOAT:
            new_column->typeof_column = FLOAT;
            new_column->data_type.float_datatype = malloc(new_column->storage * sizeof(float));
            break;
        case CHAR:
            new_column->typeof_column = CHAR;
            new_column->data_type.char_datatype = malloc(new_column->storage * sizeof(char));
            break;
        case STRING:
            new_column->typeof_column = STRING;
            new_column->data_type.string_datatype = malloc(new_column->storage * sizeof(char*));

            for (size_t i = 0; i < new_column->storage; i++)
                new_column->data_type.string_datatype[i] = malloc(STRLEN * sizeof(char));
            break;
        case BOOL:
            new_column->typeof_column = BOOL;
            new_column->data_type.bool_datatype = malloc(new_column->storage * sizeof(bool));
            break;
    }

    return new_column;
}

void add_column(SQL_TABLE* table, COLUMN* col)
{
    size_t index = table->ncols;

    table->column[index] = *col;
    table->ncols++;
}


void insert_intoV2(COLUMN* col, void* data)
{
    DATATYPE type = col->typeof_column;

    switch (type) {
        case INT:
            col->data_type.int_datatype[col->nlines++] = *(int*) data;
            break;
    }
}

void insert_into(DATABASE *db, const char *tbname, const char *colname, void *data)
{
    SQL_TABLE* tb = find_table_by_name(db, tbname);
    COLUMN* col = find_column_by_name(db, tb->tname, colname);

    if (col->is_PK) {
        col->data_type.pk[col->nlines++] = *(uint*) data;
        return;
    }

    switch (col->typeof_column) {
        case INT:
            col->data_type.int_datatype[col->nlines++] = *(int*) data;
            break;
        case FLOAT:
            col->data_type.float_datatype[col->nlines++] = *(float*) data;
            break;
        case CHAR:
            col->data_type.char_datatype[col->nlines++] = *(char*) data;
            break;
        case STRING:
            strcpy(col->data_type.string_datatype[col->nlines++], *(char**) data);
            break;
        case BOOL:
            col->data_type.bool_datatype[col->nlines++] = *(bool*) data;
            break;
        default:
            printf("Este tipo de dado e incompativel com a coluna %s.\n", col->cname);
    }
}

void select_table(const DATABASE *db, const char *tbname)
{
    SQL_TABLE* table = find_table_by_name(db, tbname);

    if (!exists_table(db, tbname))
        return;

    printf("%s\n", table->tname);

    for (size_t i = 0; i < table->ncols; i++) {
        if (table->column[i].is_PK)
            strcat(table->column[i].cname, "*");

        printf("Coluna %s ", table->column[i].cname);

        for (size_t j = 0; j < table->column->nlines; j++) 
            print_column_data(&(table->column[i]), j);
    }
}

void select_all_tables(const DATABASE *db)
{
    printf("Tabelas existentes: ");
    for (size_t i = 0; i < db->n_tables; i++) {
        if (db->table[i].has_PK) 
            strcat(db->table[i].tname,  "*");

        printf("%s | ", db->table[i].tname);
    }

    putchar('\n');
}


void select_where(const DATABASE* db, const char* tbname, const char* colname, char* condition)
{
    if (!exists_table(db, tbname))
        return;

    SQL_TABLE* table = find_table_by_name(db, tbname);
    COLUMN* target_column = get_column(db, table->tname, colname);
    DATATYPE col_datatype = target_column->typeof_column;
    
    char** tokens = tokenize(condition);

    int int_test = atoi(tokens[1]);
    float float_test = atof(tokens[1]);
    char char_test = tokens[1][0];

    switch (col_datatype) {
        case INT:
            if (strcmp(tokens[0], ">") == 0) {
                for (size_t i = 0; i < table->ncols; i++) {
                    printf("%s | ", table->tname);

                    for (size_t j = 0; j < target_column->nlines; i++) {
                        if (target_column->data_type.int_datatype[j] > int_test) {
                            printf("%s | ", table->column[i].cname);
                            print_column_data(target_column, j);
                        }
                    }
                }
            }
            else if (strcmp(tokens[0], "<") == 0) {
                for (size_t i = 0; i < table->ncols; i++) {
                    printf("%s | ", table->tname);

                    for (size_t j = 0; j < target_column->nlines; i++) {
                        if (target_column->data_type.int_datatype[j] < int_test) {
                            printf("%s | ", table->column[i].cname);
                            print_column_data(target_column, j);
                        }
                    }
                }
            }
            else if (strcmp(tokens[0], "=") == 0) {
                for (size_t i = 0; i < table->ncols; i++) {
                    printf("%s | ", table->tname);

                    for (size_t j = 0; j < target_column->nlines; i++) {
                        if (target_column->data_type.int_datatype[j] == int_test) {
                            printf("%s | ", table->column[i].cname);
                            print_column_data(target_column, j);
                        }
                    }
                }
            }
            else if (strcmp(tokens[0], ">=") == 0) {
                for (size_t i = 0; i < table->ncols; i++) {
                    printf("%s | ", table->tname);

                    for (size_t j = 0; j < target_column->nlines; i++) {
                        if (target_column->data_type.int_datatype[j] >= int_test) {
                            printf("%s | ", table->column[i].cname);
                            print_column_data(target_column, j);
                        }
                    }
                }
            }
            else if (strcmp(tokens[0], "<=") == 0) {
                for (size_t i = 0; i < table->ncols; i++) {
                    printf("%s | ", table->tname);

                    for (size_t j = 0; j < target_column->nlines; i++) {
                        if (target_column->data_type.int_datatype[j] <= int_test) {
                            printf("%s | ", table->column[i].cname);
                            print_column_data(target_column, j);
                        }
                    }
                }
            }
            break;
        case FLOAT:
            if (strcmp(tokens[0], ">") == 0) {
                for (size_t i = 0; i < table->ncols; i++) {
                    printf("%s | ", table->tname);

                    for (size_t j = 0; j < target_column->nlines; i++) {
                        if (target_column->data_type.float_datatype[j] > float_test) {
                            printf("%s | ", table->column[i].cname);
                            print_column_data(target_column, j);
                        }
                    }
                }
            }
            else if (strcmp(tokens[0], "<") == 0) {
                for (size_t i = 0; i < table->ncols; i++) {
                    printf("%s | ", table->tname);

                    for (size_t j = 0; j < target_column->nlines; i++) {
                        if (target_column->data_type.float_datatype[j] < float_test) {
                            printf("%s | ", table->column[i].cname);
                            print_column_data(target_column, j);
                        }
                    }
                }
            }
            else if (strcmp(tokens[0], "=") == 0) {
                for (size_t i = 0; i < table->ncols; i++) {
                    printf("%s | ", table->tname);

                    for (size_t j = 0; j < target_column->nlines; i++) {
                        if (target_column->data_type.float_datatype[j] == float_test) {
                            printf("%s | ", table->column[i].cname);
                            print_column_data(target_column, j);
                        }
                    }
                }
            }
            else if (strcmp(tokens[0], ">=") == 0) {
                for (size_t i = 0; i < table->ncols; i++) {
                    printf("%s | ", table->tname);

                    for (size_t j = 0; j < target_column->nlines; i++) {
                        if (target_column->data_type.float_datatype[j] >= float_test) {
                            printf("%s | ", table->column[i].cname);
                            print_column_data(target_column, j);
                        }
                    }
                }
            }
            else if (strcmp(tokens[0], "<=") == 0) {
                for (size_t i = 0; i < table->ncols; i++) {
                    printf("%s | ", table->tname);

                    for (size_t j = 0; j < target_column->nlines; i++) {
                        if (target_column->data_type.float_datatype[j] <= float_test) {
                            printf("%s | ", table->column[i].cname);
                            print_column_data(target_column, j);
                        }
                    }
                }
            }
            break;
        case CHAR:
            if (strcmp(tokens[0], "=") == 0) {
                for (size_t i = 0; i < table->ncols; i++) {
                    printf("%s | ", table->tname);

                    for (size_t j = 0; j < target_column->nlines; i++) {
                        if (target_column->data_type.char_datatype[j] == char_test) {
                            printf("%s | ", table->column[i].cname);
                            print_column_data(target_column, j);
                        }
                    }
                }
            }
            break;
        case STRING:
            if (strcmp(tokens[0], "=") == 0) {
                for (size_t i = 0; i < table->ncols; i++) {
                    printf("%s | ", table->tname);

                    for (size_t j = 0; j < target_column->nlines; i++) {
                        if (strcmp(target_column->data_type.string_datatype[j], tokens[1]) == 0) {
                            printf("%s | ", table->column[i].cname);
                            print_column_data(target_column, j);
                        }
                    }
                }
            }
            break;
        case BOOL:
            if (strcmp(tokens[0], "=") == 0) {
                for (size_t i = 0; i < table->ncols; i++) {
                    printf("%s | ", table->tname);

                    for (size_t j = 0; j < target_column->nlines; i++) {
                        if (target_column->data_type.bool_datatype[j] == int_test) {
                            printf("%s | ", table->column[i].cname);
                            print_column_data(target_column, j);
                        }
                    }
                }
            }
            break;
    }

    free_tokens(tokens, 2);
}

void drop_table(DATABASE *db, const char* tbname)
{
    if (!exists_table(db, tbname))
        return;

    SQL_TABLE* table = find_table_by_name(db, tbname);
    unsigned index = 0;

    for (size_t i = 0; i < db->n_tables; i++) {
        const char* temp_tb_name = db->table[i].tname;

        if (strcmp(table->tname, temp_tb_name) == 0) {
            index = i;
            break;
        }
    }

    for (size_t i = 0; i < db->n_tables; i++)
        db->table[i] = db->table[i + 1];

    db->n_tables -= 1;
}
