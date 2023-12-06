#ifndef SQL_HELPERS_H
#define SQL_HELPERS_H

#include <stddef.h>
#include "database.h"
#include "sql_table.h"

SQL_TABLE*  find_table_by_name(const DATABASE* db, const char* tbname);
COLUMN*     find_column_by_name(const DATABASE* db, const char* tbname, const char* colname);
bool        exists_table(const DATABASE* db, const char* tbname);
bool        exists_column(const DATABASE* db, const char* tbname, const char* colname);
COLUMN*     get_column(const DATABASE* db, const char* tbname, const char* colname);
COLUMN*     get_all_columns(const DATABASE* db, const char* tbname);
void        print_column_data(COLUMN* col, size_t index);

#endif
