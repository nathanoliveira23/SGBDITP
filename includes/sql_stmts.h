#ifndef SQL_STMST_H
#define SQL_STMST_H

#include "database.h"
#include "sql_table.h"

SQL_TABLE*  create_table(const char* tb_name, size_t ncols, const char* pkname);
COLUMN*     create_PK_column(const char* pkname);
COLUMN*     create_column(const char* colname, DATATYPE type);
void        add_column(SQL_TABLE* table, COLUMN* col);
void        insert_into(DATABASE* db, const char tbname[STRLEN], const char colname[STRLEN], void* data);
void        select_table(const DATABASE* db, const char* tbname);
void        select_all_tables(const DATABASE* db);
void        select_where(const DATABASE* db, const char* tbname, const char* colname, char* condition);
void        drop_table(DATABASE* db, const char* tbname);

#endif
