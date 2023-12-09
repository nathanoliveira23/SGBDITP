#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../includes/sql_mgmt.h"
#include "../includes/sql_stmts.h"
#include "../includes/sql_helpers.h"

extern DATABASE* db;
/*
void create_table_mgmt()
{
    SQL_TABLE* tb;

    char tbname[STRLEN];
    int ncols;
    bool created;

    printf(">>> Informe o nome e o numero de colunas da tabela: ");
    scanf("%s %d", tbname, &ncols);

    tb = create_table(tbname, ncols);
    created = add_table(db, tb);

    if (created)
        printf("Sucesso! A tabela %s foi criada com exito!\n", tb->tname);
    else
        printf("Falha ao inserir a tabela no banco de dados.\n");

    printf("\n\n\n");

    free(tb);
}

void list_all_tables_mgmt()
{
    printf("Voce possui a(s) segunte(s) tabela(s) no seu banco de dado:\n\n");
    select_all_tables(db);

    printf("\n\n\n");
}

void create_column_mgmt()
{
    COLUMN* col, *all_columns;
    SQL_TABLE* tb;
    int type;
    char colname[STRLEN], tbname[STRLEN];

    printf("Estes sao os tipos de dados disponiveis para as colunas:\n");
    printf("\t[0] - INT\n");
    printf("\t[1] - FLOAT\n");
    printf("\t[2] - CHAR\n");
    printf("\t[3] - STRING\n");
    printf("\t[4] - BOLL\n\n\n");

    printf(">>> Informe o nome da tabela que deseja criar colunas: ");
    scanf("%s", tbname);

    tb = find_table_by_name(db, tbname);

    if (tb != NULL) {
        printf("A tabela %s foi encontrada no banco de dados e possui capacidade para %d colunas.\n\n", tb->tname, (int) tb->cols_storage);
    }

    for (size_t i = 0; i < tb->cols_storage; i++) {
        printf(">>> Insira o nome da coluna %d e seu tipo de dado: ", (int) i + 1);
        scanf("%s %d", colname, &type);

        col = create_column(colname, type, false); // Gerenciar chave primaria

        add_column(tb, col);
    }

    printf("\n\n\n");                                                 
}

void list_all_table_data_mgmt(void)
{
    COLUMN* columns;
    char tbname[STRLEN];

    printf(">>> Informe o nome da tabela que deseja vizualizar: ");
    scanf("%s", tbname);

    columns = get_all_columns(db, tbname);

    if (columns == NULL)
        printf("Tabela nao encontrada.\n");

    printf("As colunas sao: \n");
    for (size_t i = 0; i < 2; i++) {
        printf("%s | ", columns[i].cname);
    }

    printf("\n\n\n");
}

void insert_into_mgmt()
{
    char tbname[STRLEN], colname[STRLEN];
    int data;

    printf(">>> Insira o nome da tabela: ");
    scanf("%s", tbname);

    printf(">>> Insira o nome da coluna e seu valor: ");
    scanf("%s %d", colname, &data);

    insert_into(db, tbname, colname, &data);
}
*/
