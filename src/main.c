#include <stdlib.h>
#include <stdio.h>
#include "../includes/database.h"
#include "../includes/sql_stmts.h"
#include "../includes/banner.h"
#include "../includes//sql_mgmt.h"

DATABASE* db;

int main(void)
{
    SQL_TABLE* tb;
    char tbname[STRLEN], pkname[STRLEN];
    int ncols;
    uint data;

    printf("Informe o nome da tabela, a quantidade de colunas e o nome da coluna PK: ");
    scanf("%s %d %s", tbname, &ncols, pkname);

    tb = create_table(tbname, ncols, pkname);
    
    add_table(db, tb);

    printf("Informe o nome da coluna e o valor que deseja inserir: ");
    scanf("%s %d", pkname, &data);

    insert_into(db, tbname, pkname, &data);
    /*
    system("clear");
    db = initialize(10);

    int opt;

    do {    
        banner();

        printf("O que deseja fazer?\n\n");
        printf("\t[1] Criar uma tabela.\n");
        printf("\t[2] Listar todas as tabelas existentes.\n");
        printf("\t[3] Adicionar coluna(s) em uma tabela.\n");
        printf("\t[4] Listar colunas de uma tabela.\n");
        printf("\t[5] Adicionar valores em uma tabela.\n");
        printf("\t[6] Listar dados de uma tabela.\n");
        printf("\t[7] Pesquisar valores em uma tabela.\n");
        printf("\t[8] Remover uma tupla/linha de uma coluna.\n");
        printf("\t[9] Remover uma tabela.\n");
        printf("\t[0] Sair do menu\n\n\n");
        printf(">>> Selecione sua opçao: ");

        scanf("%d", &opt);

        switch (opt) {
            case 0:
                exit(0);
                break;
            case 1:
                system("clear");
                create_table_mgmt();
                break;
            case 2:
                system("clear");
                list_all_tables_mgmt();
                break;
            case 3:
                system("clear");
                create_column_mgmt();
                break;
            case 4:
                system("clear");
                list_all_table_data_mgmt();
                break;
            case 5:
                system("clear");
                insert_into_mgmt();
                break;
            default:
                printf("Opção invalida!");
        }
    }
    while (opt != 0);
    */
    return 0;
}
