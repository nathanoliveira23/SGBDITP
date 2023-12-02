#ifndef SQL_STMST_H
#define SQL_STMST_H

#include "database.h"
#include "sql_table.h"

SQL_TABLE* create_table(char tb_name[STRLEN], size_t ncols);
void add_column(DATABASE* db, char tbname[STRLEN], char colname[STRLEN], DATATYPE dt, bool isPK);
void insert_into(DATABASE* db, char tbname[STRLEN], char colname[STRLEN], void* data);
void select_all_tables(const DATABASE* db);

#endif
