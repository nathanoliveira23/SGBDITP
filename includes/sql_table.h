#ifndef SQL_TABLE_H
#define SQL_TABLE_H

#include <stddef.h>
#include <stdbool.h>

#define STRLEN 50

enum dt { INT, FLOAT, CHAR, STRING, BOOL };

typedef enum dt             DATATYPE;
typedef struct column       COLUMN;
typedef union col_datatype  COL_DATATYPE;
typedef struct table        SQL_TABLE;

union col_datatype {
    unsigned    *pk;
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
    bool    has_PK;
    COLUMN  *column;
};

#endif
