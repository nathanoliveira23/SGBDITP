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

void add_column(DATABASE* db, char tbname[STRLEN], char colname[STRLEN], DATATYPE dt, bool isPK)
{
    SQL_TABLE* tb_target;
    bool found_table;

    for (size_t i = 0; i < db->n_tables; i++) {
        found_table = strcmp(db->table[i].tb_name, tbname) == 0;

        if (found_table) {
            tb_target = &(db->table[i]);
            break;
        }
    }

    strcpy(tb_target->column->col_name, colname);

    tb_target->column->is_PK = false;
    tb_target->column->col_lines = 0;

    switch (dt) {
        case INT:
            if (isPK)
                tb_target->column->is_PK = true;

            tb_target->column->data_type.int_datatype = calloc(10, sizeof(int));

            break;
        case FLOAT:
            tb_target->column->data_type.float_datatype = calloc(10, sizeof(float));
            break;
        case CHAR:
            tb_target->column->data_type.char_datatype = calloc(10, sizeof(char));
            break;
        case STRING:
            tb_target->column->data_type.string_datatype = calloc(10, sizeof(char*));

            for (size_t i = 0; i < 10; i++)
                tb_target->column->data_type.string_datatype[i] = calloc(STRLEN, sizeof(char));
            break;
        case BOOL:
            tb_target->column->data_type.bool_datatype = calloc(10, sizeof(bool));
            break;
        default:
            puts("Unknown data type.");
    }
    
    db->table->tb_cols++;

    // adicionar tabela ao banco de dados
}
