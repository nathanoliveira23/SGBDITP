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

DATABASE* db;

int main(void)
{
    system("clear");
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
                system("clear");
                create_table_mgmt();
                break;
            case 2:
                system("clear");
                list_all_tables_mgmt();
                break;
            case 3:
                system("clear");
                insert_into_mgmt();
                break;
            case 4:
                system("clear");
                list_table_data_mgmt();
                break;
            case 5:
                system("clear");
                select_where_mgmt();
                break;
            case 6:
                system("clear");
                delete_line_mgmt();
                break;
            case 7:
                system("clear");
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
