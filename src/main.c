/***********************************************************************************
 * Discente: Ronald Nathan Silva de Oliveira    Matrícula: 20230032325
 *
 * Instituição: Universidade Federal do Rio Grande do Norte /
 *              Institudo Metrópole Digital - IMD
 *
 * Disciplina: Introdução as Técnicas de Programação
 *
 * Projeto: SGBDITP
 *
 * Descrição: Este projeto tem como finalidade a consolidação dos
 *            conhecimentos em logica de programação utilizando
 *            a linguagem C. Nesse projeto, é desenvolvido um
 *            SGBD em memória de modo que suas funcionalidades 
 *            se assemelhem, de maneira simples, a um software 
 *            SGBD convencional.
 *
 ***********************************************************************************/


#include <stdlib.h>
#include <stdio.h>
#include "../includes/database.h"
#include "../includes/banner.h"
#include "../includes/sql_mgmt.h"
#include "../includes/clear_screen.h"

DATABASE* db;

int main(void)
{
    clear_screen();
    db = initialize(10);

    int opt;

    do {    
        banner();

        printf(">>> O que deseja fazer?\n\n");
        printf("\t[1] Criar uma tabela.\n");
        printf("\t[2] Listar todas as tabelas existentes.\n");
        printf("\t[3] Inserir valor em uma tabela.\n");
        printf("\t[4] Listar dados de uma tabela.\n");
        printf("\t[5] Pesquisar valor em uma tabela.\n");
        printf("\t[6] Remover uma tupla de uma tabela.\n");
        printf("\t[7] Remover uma tabela.\n");
        printf("\t[0] Sair do menu\n\n\n");
        printf(">>> Selecione sua opçao: ");

        scanf("%d", &opt);

        switch (opt) {
            case 0:
                exit(0);
                break;
            case 1:
                clear_screen();
                create_table_mgmt();
                break;
            case 2:
                clear_screen();
                list_all_tables_mgmt();
                break;
            case 3:
                clear_screen();
                insert_into_mgmt();
                break;
            case 4:
                clear_screen();
                list_table_data_mgmt();
                break;
            case 5:
                clear_screen();
                select_where_mgmt();
                break;
            case 6:
                clear_screen();
                delete_line_mgmt();
                break;
            case 7:
                clear_screen();
                drop_table_mgmt();
                break;
            default:
                printf("Opção invalida!");
        }
    }
    while (opt != 0);

    delete_database(db);

    return 0;
}
