# SOBRE O PROJETO:
    - Este projeto visa a consolidação dos conhecimento de logica de programação e linguagem C.
    - O objetivo do projeto foi desevolver um simples Sistema Gerenciado de Banco de Dados (SGBD)
      no qual algumas de suas funcionalidade buscam se assemelhar a de um SGBD convecional.

    - O projeto pode ser encontrado no seguinte link do github: https://github.com/nathanoliveira23/SGBDITP
    - Vídeo de apresentação do projeto: 


# O QUE FOI FEITO:
    - Todas as funcionalidades desejadas na cartilha do projeto foi implemetada.
    - Ou seja, o SGBD é capaz de:
        
        1- Criar tabelas SQL;
        2- Listar tabelas criadas no banco de dados;
        3- Adicionar dados nas tabelas;
        4- Listar todos os dados contidos na tabela;
        5- Pesquisar valores na tabela conforme a condição do usuário;
        6- Apagar uma tupla da tabela;
        7- Apagar uma tabela do banco de dados;


# O QUE NÃO FOI FEITO:
    - A única implementação não realizada foi o armazenamento de dados em arquivos.
    - O programa salva tabelas e dados em memória durante toda a execução da aplicação.


# O QUE FARIA DIFERENTE:
    - Uma das mudanças pretendidas é a implementação de relacionameto de tabelas 
      através do uso de ponteiros na linguagem C.


# COMO COMPILAR O PROJETO:
    - Este projeto foi desenvolvido utilizando o compilador GNU/gcc.
    - Para executar esta aplicação é necessário que:

        1- LINUX:
            - Como a maioria das distribuições linux possuem o compilador GNU/gcc instalado,
              basta entrar na pasta do projeto e, no terminal, digitar o comando "make".

        2- WINDOWS:
            - Para executar esta aplicação no Windows, é necessário ter instalado o compilador
              "MinGW" e, assim como linux, basta entrar na pasta do projeto e digitar o comando
              "make" no PowerShell ou Prompt de Comando.
    
    - Não é necessária a instalação de bibliotecas externas, pois o projeto foi desenvolvido
      utilizando bibliotecas e funções padrões da linguagem C.


