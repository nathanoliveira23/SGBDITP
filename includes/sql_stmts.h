#ifndef SQL_STMST_H
#define SQL_STMST_H

#include "database.h"
#include "sql_table.h"

SQL_TABLE* find_table_by_name(const DATABASE* db, const char* tbname);
COLUMN* find_column_by_name(const DATABASE* db, const char* tbname, const char* colname);
bool exists_table(const DATABASE* db, const char* tbname);
bool exists_column(const DATABASE* db, const char* tbname, const char* colname);

SQL_TABLE* create_table(const char tb_name[STRLEN], size_t ncols);
void add_column(DATABASE* db, const char tbname[STRLEN], const char colname[STRLEN], DATATYPE dt, bool isPK);
void insert_into(DATABASE* db, const char tbname[STRLEN], const char colname[STRLEN], void* data);
void select_table(const DATABASE* db, const char* tbname);
void select_all_tables(const DATABASE* db);
void drop_table(DATABASE* db, const char* tbname);

#endif
