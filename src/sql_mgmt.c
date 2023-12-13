/*************************************************************
 * SQL_mgmt (arquivo fonte)
 *
 * Compilador: GNU/gcc
 *
 * Descrição: Este arquivo define funções que intermedeiam
 *            a comunição entre a usuário e o banco de dados.
 *
 **************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/types.h"
#include "../includes/sql_mgmt.h"
#include "../includes/sql_stmts.h"
#include "../includes/sql_helpers.h"

extern DATABASE* db;

union data {
    int             idata;
    float           fdata;
    char            cdata;
    char            sdata[STRLEN];
    uint            pk_data; 
};

/*
 * Esta função é responsável pela volta do usuário
 * ao menu de seleção.
 *
*/
void quit_session()
{
    printf(">>> Pressione ENTER para voltar ao menu.\n");

    int exit = getchar();
    exit = getchar();
}

/*
 * Esta função é responsável por receber as entradas do usuário
 * para criação de uma tabela SQL e tratar eventuais erros 
 * cometidos pelo usuário.
 *
*/ 
void create_table_mgmt()
{
    SQL_TABLE* tb;
    COLUMN* col, *pkcolumn;

    char tbname[STRLEN], pkname[STRLEN], colname[STRLEN];
    size_t ncols, type;
    bool created, duplicated;

    printf(">>> Informe o nome e o numero de colunas da tabela: ");
    scanf("%s %zd", tbname, &ncols);

    duplicated = verify_duplicated_tables(db, tbname);

    if (duplicated) {
        printf("Ja existe uma tabela com o mesmo nome no bando de dados!\n\n");
        quit_session();
        system("clear");

        return;
    }

    tb = create_table(tbname, ncols);

    printf(">>> Informe o nome da coluna que sera definida com PK: ");
    scanf("%s", pkname);

    pkcolumn = create_pk_column(pkname);

    add_column(tb, *pkcolumn);

    printf("Sua tabela possui %d coluna(s) restante a ser inserida(s)\n\n", (int) tb->cols_storage - 1);

    printf("Estes sao os tipos de dados disponiveis para as colunas:\n");
    printf("\t[0] - INT\n");
    printf("\t[1] - FLOAT\n");
    printf("\t[2] - CHAR\n");
    printf("\t[3] - STRING\n");

    for (size_t i = 0; i < tb->cols_storage - 1; i++) {
        printf(">>> Informe o nome e o tipo de dado da coluna %d: ", (int) i + 2);
        scanf("%s %zd", colname, &type);

        col = create_column(colname, type);

        add_column(tb, *col);
    }

    created = add_table(db, *tb);

    if (created)
        printf("Sucesso! A tabela %s foi criada com exito!\n", tb->tname);
    else
        printf("Falha ao inserir a tabela no banco de dados.\n");

    printf("\n\n\n");

    quit_session();
    system("clear");
}

/*
 * Esta função é responsável por imprimir para o usuário
 * todas as tabelas existentes no banco de dados.
 *
*/ 
void list_all_tables_mgmt()
{
    size_t ntables = db->n_tables;

    if (ntables == 0) {
        printf("Voce nao possui tabelas armazenadas no banco de dados.\n");
        quit_session();
        system("clear");
        return;
    }

    printf(">>> Voce possui a(s) segunte(s) tabela(s) no seu banco de dado:\n\n");

    select_all_tables(db);

    printf("\n\n\n");

    quit_session();
    system("clear");
}


/*
 * Esta função é responsável por receber dados do usuário
 * para serem tratados e inseridos em uma tabela SQL.
 *
*/
void insert_into_mgmt()
{
    union data to_insert;

    SQL_TABLE* table;
    char tbname[STRLEN];
    DATATYPE type;

    printf(">>> Informe o nome da tabela: ");
    scanf("%s", tbname);

    table = find_table_by_name(db, tbname);

    for (size_t i = 0; i < table->ncols; i++) {
        type = table->column[i].typeof_column;

        if (type == PK) {
            printf("ATENCAO: A coluna %s e CHAVE PRIMARIA da tabela %s.\n", table->column[i].cname, tbname);
            printf(">>> Informe o valor que deseja inserir na coluna %s: ", table->column[i].cname);
            scanf("%u", &to_insert.pk_data);
            
            if (verify_PK(table, to_insert.pk_data)) {
                printf(">>> Esse valor ja foi definido com chave primaria.\n");
                quit_session();
                system("clear");

                return;
            }

            insert_into(table, i, &to_insert.pk_data);
            printf("\n");
        }
        else if (type == INT) {
            printf("ATENCAO: A coluna %s e do tipo INT.\n", table->column[i].cname);
            printf(">>> Informe o valor que deseja inserir na coluna %s: ", table->column[i].cname);
            scanf("%d", &to_insert.idata);
            
            insert_into(table, i, &to_insert.idata);
            printf("\n");
        }
        else if (type == FLOAT) {
            printf("ATENCAO: A coluna %s e do tipo FLOAT.\n", table->column[i].cname);
            printf(">>> Informe o valor que deseja inserir na coluna %s: ", table->column[i].cname);
            scanf("%f", &to_insert.fdata);
            
            insert_into(table, i, &to_insert.idata);
            printf("\n");
        }
        else if (type == CHAR) {
            printf("ATENCAO: A coluna %s e do tipo CHAR.\n", table->column[i].cname);
            printf(">>> Informe o valor que deseja inserir na coluna %s: ", table->column[i].cname);
            scanf(" %c", &to_insert.cdata);
            
            insert_into(table, i, &to_insert.idata);
            printf("\n");
        }
        else if (type == STRING) {
            printf("ATENCAO: A coluna %s e do tipo STRING.\n", table->column[i].cname);
            printf(">>> Informe o valor que deseja inserir na coluna %s: ", table->column[i].cname);
            getchar();
            fgets(to_insert.sdata, STRLEN, stdin);
            to_insert.sdata[strlen(to_insert.sdata) - 1] = '\0';
            
            strcpy(table->column[i].data_type._string[table->column[i].nrows++], to_insert.sdata);
            printf("\n");
        }
    }
    printf("\n\n\n");

    quit_session();
    system("clear");
}

/*
 * Esta função imprime para o usuário todos os dados que estão
 * presentes em uma tabela SQL.
 *
*/
void list_table_data_mgmt(void)
{
    char tbname[STRLEN];
    SQL_TABLE* tb;
    bool success;

    printf(">>> Informe o nome da tabela que deseja visualizar: ");
    scanf("%s", tbname);

    if (!exists_table(db, tbname)) {
        printf("Tabela informada não encontrada.");
        quit_session();
        system("clear");
        return;
    }

    success = select_table(db, tbname);
    
    if (!success) {
        printf("Erro ao acessar a tabela.\n");
        quit_session();
        system("clear");
        return;
    }

    printf("\n\n\n");

    quit_session();
    system("clear");
}

/*
 * Esta função é responsável por receber a condição de pesquisa
 * feita pelo usuário e retornar sua solicitação.
 *
*/
void select_where_mgmt(void)
{
    char tbname[STRLEN], colname[STRLEN], condition[STRLEN];

    printf(">>> Informe o nome da tabela que deseja acessar: ");
    scanf("%s", tbname);

    printf("\nVoce tem as seguintes operações para cada tipo de dado:\n\n");

    printf("\tINT: | = | > | < | >= | <= |\n");
    printf("\tEx: id >= 3\n\n");

    printf("\tFLOAT: | = | > | < | >= | <= |\n");
    printf("\tEx: preco > 5.90\n\n");

    printf("\tCHAR: | = |\n");
    printf("\tEx: letra = R\n\n");

    printf("\tSTRING: | = |\n");
    printf("\tEx: nome = fulano\n\n");

    printf(">>> Insira a condição desejada: ");
    getchar();
    fgets(condition, STRLEN, stdin);
    condition[strlen(condition) - 1] = '\0';

    select_where(db, tbname, condition);

    printf("\n\n\n");

    quit_session();
    system("clear");
}

/*
 * Esta função é responsável por deletar uma tupla de uma tabela
 * conforme a entrada do usuário.
 *
*/
void delete_line_mgmt(void)
{
    SQL_TABLE* table;
    char tbname[STRLEN];
    uint id;

    printf(">>> Informe a tabela que deseja remover a tupla: ");
    scanf("%s", tbname);

    printf(">>> Informe o valor da chave primaria de uma tupla: ");
    scanf("%u", &id);

    table = find_table_by_name(db, tbname);

    delete_line(table, id);

    printf("A tupla foi deletada com sucesso!");
    printf("\n\n\n");

    quit_session();
    system("clear");
}

/*
 * Esta função é responsável por deletar uma tabela de um banco de dados 
 * conforme a entrada do usuário.
 *
*/
void drop_table_mgmt()
{
    char tbname[STRLEN];

    printf(">>> Informe o nome da tabela que deseja remover do banco de dados: ");
    scanf("%s", tbname);

    drop_table(db, tbname);

    printf("\n");
    printf(">>> A tabela %s foi removida do banco de dados com sucesso!\n", tbname);

    printf("\n\n\n");

    quit_session();
    system("clear");
}
