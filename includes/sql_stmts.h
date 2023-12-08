#ifndef SQL_STMST_H
#define SQL_STMST_H

#include "database.h"
#include "sql_table.h"

SQL_TABLE*  create_table(const char tb_name[STRLEN], size_t ncols);
COLUMN*     create_column(const char* colname, DATATYPE type, bool isPK);
void        add_column(SQL_TABLE* table, COLUMN* col);
void        insert_into(DATABASE* db, const char tbname[STRLEN], const char colname[STRLEN], void* data);
void        select_table(const DATABASE* db, const char* tbname);
void        select_all_tables(const DATABASE* db);
void        select_where(const DATABASE* db, const char* tbname, const char* colname, char* condition);
void        drop_table(DATABASE* db, const char* tbname);

#endif
