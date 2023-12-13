/*************************************************************
 * SQL_mgmt (arquivo de cabeçlho)
 *
 * Compilador: GNU/gcc
 *
 * Descrição: Este arquivo define funções que intermedeiam
 *            a comunição entre a usuário e o banco de dados.
 *
 **************************************************************/


#ifndef SQL_MGMT_H
#define SQL_MGMT_H

/*
 * Esta função é responsável pela volta do usuário
 * ao menu de seleção.
 *
*/
void quit_session(void);


/*
 * Esta função é responsável por receber as entradas do usuário
 * para criação de uma tabela SQL e tratar eventuais erros 
 * cometidos pelo usuário.
 *
*/ 
void create_table_mgmt(void);



/*
 * Esta função é responsável por receber dados do usuário
 * para serem tratados e inseridos em uma tabela SQL.
 *
*/
void insert_into_mgmt(void);


/*
 * Esta função imprime para o usuário todos os dados que estão
 * presentes em uma tabela SQL.
 *
*/
void list_table_data_mgmt(void);


/*
 * Esta função é responsável por imprimir para o usuário
 * todas as tabelas existentes no banco de dados.
 *
*/ 
void list_all_tables_mgmt(void);


/*
 * Esta função é responsável por receber a condição de pesquisa
 * feita pelo usuário e retornar sua solicitação.
 *
*/
void select_where_mgmt(void);


/*
 * Esta função é responsável por deletar uma tupla de uma tabela
 * conforme a entrada do usuário.
 *
*/
void delete_line_mgmt(void);


/*
 * Esta função é responsável por deletar uma tabela de um banco de dados 
 * conforme a entrada do usuário.
 *
*/
void drop_table_mgmt(void);

#endif
