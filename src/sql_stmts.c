#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/sql_stmts.h"
#include "../includes/database.h"

SQL_TABLE* create_table(char tbname[STRLEN], size_t ncols)
{
    SQL_TABLE* tb = malloc(sizeof(SQL_TABLE));

    strcpy(tb->tb_name, tbname);
    tb->tb_cols = 0;
    tb->column = malloc(ncols * sizeof(COLUMN));

    return tb;
}

SQL_TABLE* find_table_by_name(const DATABASE* db, const char* tbname)
{
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
    SQL_TABLE* tb = find_table_by_name(db, tbname);
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

void add_column(DATABASE* db, char tbname[STRLEN], char colname[STRLEN], DATATYPE dt, bool isPK)
{
    SQL_TABLE* tb_target = find_table_by_name(db, tbname);

    strcpy(tb_target->column->col_name, colname);

    tb_target->column->is_PK = false;
    tb_target->column->col_lines = 0;

    switch (dt) {
        case INT:
            if (isPK)
                tb_target->column->is_PK = true;
            
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

void insert_into(DATABASE *db, char *tbname, char *colname, void *data)
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

void select_all_tables(const DATABASE *db)
{

}
