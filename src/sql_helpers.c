#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "../includes/sql_helpers.h"


bool exists_table(const DATABASE* db, const char* tbname)
{
    char* temp_name;
    bool exists;

    for (size_t i = 0; i < db->n_tables; i++) {
        temp_name = db->table[i].tname;
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

    for (size_t i = 0; i < tb->ncols; i++) {
        temp_col_name = tb->column[i].cname;
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
        found = strcmp(db->table[i].tname, tbname) == 0;

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

    if (!exists_column(db, tb->tname, colname))
        return NULL;

    COLUMN* col_target;
    bool found;

    for (size_t i = 0; i < tb->ncols; i++) {
        found = strcmp(tb->column[i].cname, colname) == 0;

        if (found) {
            col_target = &(tb->column[i]);
            break;
        }
    }

    return col_target;
}

COLUMN* get_column(const DATABASE* db, const char* tbname, const char* colname)
{
    if (!exists_table(db, tbname))
        return NULL;

    SQL_TABLE* table = find_table_by_name(db, tbname);
    COLUMN* column;

    if (!exists_column(db, table->tname, colname))
        return NULL;

    column = find_column_by_name(db, table->tname, colname);

    return column;
}

COLUMN* get_all_columns(const DATABASE* db, const char* tbname)
{
    if (!exists_table(db, tbname))
        return NULL;

    SQL_TABLE* table = find_table_by_name(db, tbname);
    COLUMN* columns = malloc(table->ncols * sizeof(COLUMN));

    for (size_t i = 0; i < table->ncols; i++)
        columns[i] = table->column[i];

    return columns;
}

/*
void print_column_data(COLUMN* col, size_t index)
{
    DATATYPE col_datatype = col->typeof_column;

    if (col_datatype == INT)
        printf("%d\n", col->data_type.int_datatype[index]);
    else if (col_datatype == FLOAT)
        printf("%.2f\n", col->data_type.float_datatype[index]);
    else if (col_datatype == CHAR)
        printf("%c\n", col->data_type.char_datatype[index]);
    else if (col_datatype == BOOL)
        printf("%d\n", col->data_type.bool_datatype[index]);
    else if (col_datatype == STRING)
        printf("%s\n", col->data_type.string_datatype[index]);
}
*/
