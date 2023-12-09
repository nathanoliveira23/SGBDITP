#ifndef SQL_TABLE_H
#define SQL_TABLE_H

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include "types.h"

#define STRLEN 50

union col_datatype {
    void**  data;
    char**  str_data;
};

struct column {
    char            cname[STRLEN];
    bool            is_PK;
    size_t          nlines;
    size_t          storage;
    DATATYPE        typeof_column;
    FILE*           data;
    //COL_DATATYPE    data_type;
};

struct table {
    char    tname[STRLEN];
    size_t  ncols;
    size_t  cols_storage;
    COLUMN  *column;
};

#endif
