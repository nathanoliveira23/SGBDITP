#ifndef SQL_TABLE_H
#define SQL_TABLE_H

#include <stddef.h>
#include <stdbool.h>
#include "types.h"

#define STRLEN 50

union col_datatype {
    uint        *pk;
    char        *char_datatype;
    char        **string_datatype;
    int         *int_datatype;
    float       *float_datatype;
    bool        *bool_datatype;
};

struct column {
    char            cname[STRLEN];
    bool            is_PK;
    size_t          nlines;
    size_t          storage;
    DATATYPE        typeof_column;
    COL_DATATYPE    data_type;
};

struct table {
    char    tname[STRLEN];
    size_t  ncols;
    size_t  cols_storage;
    bool    has_PK;
    COLUMN  *column;
};

#endif
