#ifndef TYPES_H
#define TYPES_H

typedef enum { INT, FLOAT, CHAR, STRING, BOOL } DATATYPE;

typedef struct column       COLUMN;
typedef union col_datatype  COL_DATATYPE;
typedef struct table        SQL_TABLE;

typedef unsigned int        uint;

#endif
