#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/sql_stmts.h"
#include "../includes/database.h"

SQL_TABLE* create_table(const char tbname[STRLEN], size_t ncols)
{
    SQL_TABLE* tb = malloc(sizeof(SQL_TABLE));

    strcpy(tb->tb_name, tbname);
    tb->tb_cols = 0;
    tb->has_PK = false;
    tb->column = malloc(ncols * sizeof(COLUMN));

    return tb;
}

bool exists_table(const DATABASE* db, const char* tbname)
{
    char* temp_name;
    bool exists;

    for (size_t i = 0; i < db->n_tables; i++) {
        temp_name = db->table[i].tb_name;
        exists = strcmp(temp_name, tbname) == 0;

        if (exists)
            return true;
    }

    return false;
}

bool exists_column(const DATABASE *db, const char *tbname, const char *colname)
{
    if (!exists_table(db, tbname))
        return false;

    SQL_TABLE* tb = find_table_by_name(db, tbname);
    char* temp_col_name;
    bool exists;

    for (size_t i = 0; i < tb->tb_cols; i++) {
        temp_col_name = tb->column[i].col_name;
        exists = strcmp(temp_col_name, colname);

        if (exists)
            return true;
    }

    return false;
}

SQL_TABLE* find_table_by_name(const DATABASE* db, const char* tbname)
{
    if (!exists_table(db, tbname))
        return NULL;

    SQL_TABLE* tb_target;
    bool found;

    for (size_t i = 0; i < db->n_tables; i++) {
        found = strcmp(db->table[i].tb_name, tbname) == 0;

        if (found) {
            tb_target = &(db->table[i]);
            break;
        }
    }

    return tb_target;
}

COLUMN* find_column_by_name(const DATABASE *db, const char* tbname, const char *colname)
{
    if (!exists_table(db, tbname))
        return NULL;

    SQL_TABLE* tb = find_table_by_name(db, tbname);

    if (!exists_column(db, tb->tb_name, colname))
        return NULL;

    COLUMN* col_target;
    bool found;

    for (size_t i = 0; i < tb->tb_cols; i++) {
        found = strcmp(tb->column[i].col_name, colname) == 0;

        if (found) {
            col_target = &(tb->column[i]);
            break;
        }
    }

    return col_target;
}

void add_column(DATABASE* db, const char tbname[STRLEN], const char colname[STRLEN], DATATYPE dt, bool isPK)
{
    SQL_TABLE* tb_target = find_table_by_name(db, tbname);

    strcpy(tb_target->column->col_name, colname);

    tb_target->column->is_PK = false;
    tb_target->column->col_lines = 0;

    switch (dt) {
        case INT:
            if (isPK) {
                tb_target->column->is_PK = true;
                tb_target->has_PK = true;
            }
            
            tb_target->column->typeof_column = INT;
            tb_target->column->data_type.int_datatype = calloc(10, sizeof(int));

            break;
        case FLOAT:
            tb_target->column->typeof_column = FLOAT; 
            tb_target->column->data_type.float_datatype = calloc(10, sizeof(float));
            break;
        case CHAR:
            tb_target->column->typeof_column = CHAR;
            tb_target->column->data_type.char_datatype = calloc(10, sizeof(char));
            break;
        case STRING:
            tb_target->column->typeof_column = STRING;
            tb_target->column->data_type.string_datatype = calloc(10, sizeof(char*));

            for (size_t i = 0; i < 10; i++)
                tb_target->column->data_type.string_datatype[i] = calloc(STRLEN, sizeof(char));
            break;
        case BOOL:
            tb_target->column->typeof_column = BOOL;
            tb_target->column->data_type.bool_datatype = calloc(10, sizeof(bool));
            break;
        default:
            puts("Unknown data type.");
    }
    
    db->table->tb_cols++;
}

void insert_into(DATABASE *db, const char *tbname, const char *colname, void *data)
{
    SQL_TABLE* tb = find_table_by_name(db, tbname);
    COLUMN* col = find_column_by_name(db, tbname, colname);

    switch (col->typeof_column) {
        case INT:
            col->data_type.int_datatype[col->col_lines++] = *(int*) data;
            break;
        case FLOAT:
            col->data_type.float_datatype[col->col_lines++] = *(float*) data;
            break;
        case CHAR:
            col->data_type.char_datatype[col->col_lines++] = *(char*) data;
            break;
        case STRING:
            col->data_type.string_datatype[col->col_lines++] = *(char**) data;
            break;
        case BOOL:
            col->data_type.bool_datatype[col->col_lines++] = *(bool*) data;
            break;
        default:
            printf("Este tipo de dado e incompativel com a coluna %s.\n", col->col_name);
    }
}

void select_table(const DATABASE *db, const char *tbname)
{
    SQL_TABLE* table = find_table_by_name(db, tbname);

    for (size_t i = 0; i < table->tb_cols; i++) {
        printf("Coluna %s:\n", table->column[i].col_name);

        for (size_t j = 0; j < 10; j++) {
            switch (table->column[i].typeof_column) {
                case INT:
                    printf("%d ", table->column[i].data_type.int_datatype[j]);
                    break;
                case FLOAT:
                    printf("%.2f ", table->column[i].data_type.float_datatype[j]);
                    break;
                case CHAR:
                    printf("%c ", table->column[i].data_type.char_datatype[j]);
                    break;
                case STRING:
                    printf("%s ", table->column[i].data_type.string_datatype[j]);
                    break;
                case BOOL:
                    printf("%d ", table->column[i].data_type.bool_datatype[j]);
                    break;
            }
        }
    }
}

void select_all_tables(const DATABASE *db)
{
    printf("Tabelas existentes: ");
    for (size_t i = 0; i < db->n_tables; i++)
        printf("%s | ", db->table[i].tb_name);

    putchar('\n');
}

void drop_table(DATABASE *db, const char* tbname)
{
    SQL_TABLE* table = find_table_by_name(db, tbname);
    unsigned index = 0;

    for (size_t i = 0; i < db->n_tables; i++) {
        const char* temp_tb_name = db->table[i].tb_name;

        if (strcmp(table->tb_name, temp_tb_name) == 0) {
            index = i;
            break;
        }
    }

    for (size_t i = 0; i < db->n_tables; i++)
        db->table[i] = db->table[i + 1];

    db->n_tables -= 1;
}
