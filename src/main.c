#include <stdio.h>
#include <string.h>
#include "../includes/database.h"
#include "../includes/sql_stmts.h"

int main(void)
{
    DATABASE* db = initialize(10);
    SQL_TABLE* tb;

    char title[STRLEN], colname[STRLEN];
    int n, type, data;
    char cdata, str[STRLEN];

    printf("Informe o nome e o numero de colunas da tabela: ");
    scanf("%s %d", title, &n);

    tb = create_table(title, n);

    add_table(db, tb);

    for (int i = 0; i < n; i++) {
        printf("Informe o nome e o tipo dado da coluna %d: ", i+1);
        scanf("%s %d", colname, &type);

        add_column(db, title, colname, type, true);

    }

    printf("Informe o nome da coluna que deseja inserir dados e o dado correspondente: ");
    scanf("%s %s", colname, str);

    insert_into(db, title, colname, &str);

    //select_all_tables(db);
    select_table(db, title);

    return 0;
}
