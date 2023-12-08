#ifndef DATABASE_H
#define DATABASE_H

#include <stddef.h>
#include <stdbool.h>
#include "sql_table.h"

typedef struct database DATABASE;

struct database {
    SQL_TABLE*  table;
    size_t      storage;
    size_t      n_tables;
};

DATABASE*   initialize(size_t storage);
bool        add_table(DATABASE* db, SQL_TABLE* tb);

#endif
