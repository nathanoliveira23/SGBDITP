#include <stdlib.h>
#include "../includes/database.h"

DATABASE* initialize(size_t storage)
{
    DATABASE* db = malloc(sizeof(DATABASE));

    db->storage = storage;
    db->n_tables = 0;
    db->table = malloc(storage * sizeof(SQL_TABLE));

    return db;
}

bool add_table(DATABASE* db, SQL_TABLE* tb)
{
    if (db->n_tables < db->storage) {
        db->table[db->n_tables++] = *tb;
        return true;
    }
    else {
        db->storage *= 2;
        db->table = realloc(db->table, db->storage);
        db->table[db->n_tables++] = *tb;
        return true;
    }

    return false;
}
