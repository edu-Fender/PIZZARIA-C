#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <unistd.h>
#include <ctype.h>

#define pause system("pause")
#define cls system("cls")
#define s sleep(1)

int login(); void cadastro(); void pizzas(); void drinks(); void pizzers(); void feedback(); void logo();

int loged = 0; //loged = 0 -> variavel que indica para o compilador se o usuario esta logado e em qual nivel (0 -> off, 1 -> admin, 2 -> basico)

int main(){ //funcao principal

    setlocale(LC_ALL, "PORTUGUESE");
    system("COLOR F");

    int choice;

    if (loged == 0){ //Caso o usuario esteja off (loged = 0), chama a funcao login(), que retorna 1 ou 2 dependendo do nivel de acesso do usuario
        loged = login();
    }

    if (loged == 1){

        logo();
        printf("\t Bem vindo ADMIN, o que deseja fazer?\n\n\t 1 - Gerenciar usu�rios\n\t 2 - Financeiro\n\t 3 - Sair");
        printf("\n\n\t Digite 0 para voltar: ");
        fflush(stdin); scanf("%d", &choice);

        switch(choice){
            case 0:
                loged = 0;
                main();
                break;
            case 1:
                cadastro();
                break;
            case 2:
            	cls;
            	printf("EM DESENVOLVIMENTO\n");
            	break;
            case 3:
                cls; printf("\n\t Obrigado por escolher a \x1b[33mJETA\x1b[0ms, volte sempre!! \n\n"); s; logo(1); sleep(3); exit(0);
            default:
                printf("\n\t POR FAVOR, ESCOLHA UMA DAS OP��ES ACIMA!\n\n");
                pause; main();
        }
    }

    if (loged == 2){

		logo();
		printf("\t Bem vindo! O que deseja fazer?\n\n");
		printf("\t  1 - Cadastrar Pizzas\n\t  2 - Cadastrar Bebidas\n\t  3 - Cadastrar Pizzaiolos\n\t  4 - Reclama��es/Elogios\n\t  5 - Informa��es do Sistema\n\t  6 - Sair");
		printf("\n\n\t Digite 0 para voltar: ");
        fflush(stdin); scanf("%d", &choice);

        switch(choice){
            case 0:
                loged = 0;
                main();
                break;
            case 1:
                pizzas();
                break;
            case 2:
                drinks();
                break;
            case 3:
                pizzers();
                break;
            case 4:
                feedback();
                break;
            case 5: //pequena animacao baseada em temporizador (s)
                cls; s; printf("\n\tSistema UNIPESTANA.\n\t"); s; printf("version.: 2.0.3\n\n\t"); s; printf("Cr�ditos:\n\t"); s; printf("- \x1b[31mJ\x1b[0muan Pablo\n\t");
                s; printf("- \x1b[31mE\x1b[0mduardo Franco\n\t"); s; printf("- \x1b[31mT\x1b[0males Carneiro\n\t"); s; printf("- \x1b[31mA\x1b[0mndr� Fermino\n\n\t"); s; printf("\x1b[31mJETA\x1b[0ms");
                s; printf(" Software,"); s; printf(" all rights reserved."); s; printf(" SANTOS - 2019\n\t"); s; printf("Obrigado por escolher o \x1b[31mJETA\x1b[0ms, volte sempre!! \n\n"); s; logo(1);
                pause; main();
                break;
            case 6:
                cls; printf("\n\t Obrigado por escolher a \x1b[33mJETA\x1b[0ms, volte sempre!! \n\n"); s; logo(1); sleep(3); exit(0);
            default:
                printf("\n\t POR FAVOR, ESCOLHA UMA DAS OP��ES ACIMA!\n\n");
                pause; main();
        }
    return 0;
    }
}

int login(){ //retorna 1 ou 2 dependendo do nivel de acesso do usario (caso usuario valido)

    logo();
    fflush(stdin);
    char user[20], pass[20];

    char *line = NULL;
    size_t len = 0;
    int check = 0;

    printf("\t >>LOGIN<<");
    printf("\n\n\t Digite seu usuario: ");
    scanf(" %s", user);
    printf("\t Digite sua senha: ");
    scanf(" %s", pass);

    if (strcmp(user, "admin") == 0 && strcmp(pass, "12345") == 0){ //checa se o input do usuario bate com usuario e senha predefinida, retorna 1 caso sim (nivel maximo de acesso)
        return 1;
    }

    FILE*file = fopen("DATABASE//DATABASE.txt", "r");

    while (getline(&line, &len, file) != -1){ //loop para checar o arquivo txt linha a linha

        if (check == 1){ //caso chek = 1 (vide linha 160), checa a proxima linha que sera a senha
            if (strlen(pass) == strlen(line)-1 && strncmp (line,pass,(strlen(line))-1) == 0){ //checa se a senha bate, retorna 2 caso sim (nivel basico de acesso)
                return 2;
            }
            else{
                printf("\n\t SENHA INV�LIDA. TENTE NOVAMENTE.\n\n");
                pause; main();
            }
        }
        if (strlen(user) == strlen(line)-1 && strncmp(line,user,(strlen(line)-1)) == 0){ //checa se o usuario esta presente em alguma linha do txt, se sim, atribui a variavel chek = 1 (a proxima linha do loop sera a senha)
            check = 1;
        }
    }

    fclose(file);
    printf("\n\t USU�RIO INV�LIDO. TENTE NOVAMENTE.\n\n");
    pause; main();
}

void cadastro(){ //cadastra os usuarios em um arquivo txt (user e senha)

    logo();
    int choice;
    char user[20], pass[20], line [20];

    FILE*file = fopen("DATABASE\\DATABASE.txt", "a+");

    printf ("\t O que deseja fazer?\n\n\t 1 - Cadastrar usu�rio\n\t 2 - Visualizar lista de usuarios cadastrados\n\t 3 - Resetar lista de usu�rios (CUIDADO)");
    printf("\n\n\t Digite 0 para voltar: ");
    fflush(stdin); scanf("%d", &choice);

    switch(choice){

        case 0:
            main();
            break;
        case 1:
            cls; printf("\t >>CADASTRO DE USU�RIOS<<");
            printf("\n\n\t Digite o login: ");
            scanf("%s", user);
            printf("\t Digite a senha: ");
            scanf("%s", pass);

            fprintf(file, "%s\n", user);
            fprintf(file, "%s\n\n", pass);
            printf("\n\t USU�RIO CADASTRADO COM SUCESSO!\n\n");
            fclose(file);
            pause; cadastro();
            break;
        case 2:
            cls;
            if (file != NULL){
                fseek (file, 0, SEEK_END); //fseek: checa se o txt esta vazio
                if (ftell(file) == 0){
                    printf("\n\t NENHUM USUARIO CADASTRADO!\n\n");
                    pause; cadastro();fflush(stdin);
                }
                fseek (file, 0, SEEK_SET);
                printf("\n");
                while (fgets(line, 20, file) != NULL)
                    printf("\t%s", line);
            }
            pause; cadastro();
            break;
        case 3:
            cls;
            fopen("DATABASE\\DATABASE.TXT", "w"); //reseta a lista ao abrir o arquivo em modo "w" (write)
            fprintf(file, "%s\n\n", "//");
            printf("\n\t LISTA DE USU�RIOS RESETADA COM SUCESSO!\n\n");
            fclose(file);
            pause; cadastro();
            break;

        default:
            printf("\n\t POR FAVOR, ESCOLHA UMA DAS OP��ES ACIMA!\n\n");
            pause; cadastro();
    }
}

void pizzas(){ //cadastra pizzas

    logo();
    int choice;
    char pizza[20], price[20], line[20];

    printf ("\t O que deseja fazer?\n\n\t 1 - Cadastrar pizza\n\t 2 - Visualizar Card�pio de pizzas\n\t 3 - Resetar Card�pio (CUIDADO)");
    printf("\n\n\t Digite 0 para voltar: ");
    fflush(stdin); scanf("%d", &choice);

    FILE*file = fopen("DATABASE\\PIZZA.txt", "a+");

    switch(choice){
        case 0:
            main();
            break;
        case 1:
            cls; printf("\n\t >>CADASTRO DE PIZZA<<");
            printf("\n\n\t Digite o nome da pizza: ");
            scanf("%s", pizza);
            printf("\t Digite o pre�o da pizza: R$");
            scanf("%s", price);

            fprintf(file, "%s\n", pizza);
            fprintf(file, "%s\n\n", price);
            printf("\n\t PIZZA CADASTRADA COM SUCESSO!\n\n");
            fclose(file);
            pause; pizzas();
            break;

        case 2:
            cls;
            if (file != NULL){
                fseek (file, 0, SEEK_END); //fseek: checa se o txt esta vazio
                if (ftell(file) == 0){
                    printf("\n\t NENHUMA PIZZA CADASTRADA!\n\n");
                    pause; pizzas();
                }
                fseek (file, 0, SEEK_SET);
                printf("\n");
                while (fgets(line, 20, file) != NULL)
                    printf("\t%s", line);
            }
            pause; pizzas();
            break;

        case 3:
            cls;
            fopen("DATABASE\\PIZZA.TXT", "w"); //reseta a lista ao abrir o arquivo em modo "w" (write)
            printf("\n\t LISTA DE PIZZAS RESETADA COM SUCESSO!\n\n");
            fclose(file);
            pause; pizzas();
            break;

        default:
            printf("\n\t POR FAVOR, ESCOLHA UMA DAS OP��ES ACIMA!\n\n");
            pause; pizzas();
    }
}

void drinks(){ //cadastra bebidas

    logo();
    int choice;
    char drink[20], price[20], line[20];

    printf ("\t O que deseja fazer?\n\n\t 1 - Cadastrar bebida\n\t 2 - Visualizar Card�pio de bebidas\n\t 3 - Resetar Card�pio (CUIDADO)");
    printf("\n\n\t Digite 0 para voltar: ");
    fflush(stdin); scanf("%d", &choice);

    FILE*file = fopen("DATABASE\\DRINK.txt", "a+");

    switch(choice){
        case 0:
            main();
            break;
        case 1:
            cls; printf("\n\t >>CADASTRO DE BEBIDA<<");
            printf("\n\n\t Digite o nome da bebida: ");
            scanf("%s", drink);
            printf("\t Digite o pre�o da bebida: R$");
            scanf("%s", price);

            fprintf(file, "%s\n", drink);
            fprintf(file, "%s\n\n", price);
            printf("\n\t BEBIDA CADASTRADA COM SUCESSO!\n\n");
            pause; drinks();
            break;

        case 2:
            cls;
            if (file != NULL){
                fseek (file, 0, SEEK_END); //fseek: checa se o txt esta vazio
                if (ftell(file) == 0){
                    printf("\n\t NENHUMA BEBIDA CADASTRADA!\n\n");
                    pause; drinks();
                }
                fseek (file, 0, SEEK_SET);
                printf("\n");
                while (fgets(line, 20, file) != NULL)
                    printf("\t %s", line);
            }
            pause; drinks();
            break;

        case 3:
            cls;
            fopen("DATABASE\\DRINK.TXT", "w"); //reseta a lista ao abrir o arquivo em modo "w" (write)
            printf("\n\t LISTA DE BEBIDAS RESETADA COM SUCESSO!\n\n");
            fclose(file);
            pause; drinks();
            break;

        default:
            printf("\n\t POR FAVOR, ESCOLHA UMA DAS OP��ES ACIMA!\n\n");
            pause; drinks();
    }
}

void pizzers(){ //cadastra pizzaiolos

    logo();
    int choice;
    char pizzer[20], text[200], line[20];

    printf ("\t O que deseja fazer?\n\n\t 1 - Cadastrar novo Pizzaiolo\n\t 2 - Visualizar Pizzaiolos\n\t 3 - Resetar lista de pizzaiolos (CUIDADO)");
    printf("\n\n\t Digite 0 para voltar: ");
    fflush(stdin); scanf("%d", &choice);

    FILE*file = fopen("DATABASE\\PIZZER.txt", "a+");

    switch(choice){

        case 0:
            main();
            break;
        case 1:
            cls; printf("\n\t >>CADASTRO DE PIZZAIOLO<<");
            printf("\n\n\t Digite o nome do pizzaiolo: ");
            scanf("%s", pizzer);
            printf("\t Informa��es adicionais: ");
            scanf("%s", text);

            fprintf(file, "Pizzaiolo: %s\n", pizzer);
            fprintf(file, "obs: %s\n\n", text);
            printf("\n\t PIZZAIOLO CADASTRADO COM SUCESSO!\n\n");
            fclose(file);
            pause; pizzers();
            break;

        case 2:
            cls;
            if (file != NULL){
                fseek (file, 0, SEEK_END); //fseek: checa se o txt esta vazio
                if (ftell(file) == 0){
                    printf("\t NENHUMM PIZZAIOLO CADASTRADO!\n\n");
                    pause; pizzers();
                }
                fseek (file, 0, SEEK_SET);
                printf("\n");
                while (fgets(line, 20, file) != NULL)
                    printf("\n\t %s", line);
            }
            pause; pizzers();
            break;

        case 3:
            cls;
            fopen("DATABASE\\PIZZER.TXT", "w"); //reseta a lista ao abrir o arquivo em modo "w" (write)
            printf("\n\t LISTA DE PIZZAIOLOS RESETADA COM SUCESSO!\n\n");
            fclose(file);
            pause; pizzers();
            break;

        case 4:
            main();
            break;

        default:
            printf("\n\t POR FAVOR, ESCOLHA UMA DAS OP��ES ACIMA!\n\n");
            pause; pizzers();
    }
}

void feedback(){ //cadastra sugestoes/reclamacoes

    logo();
    char text[200];
    FILE*file = fopen("DATABASE\\FEEDBACK.txt", "a+");
    cls; printf("\t Reclama��o/sugest�o:\n\n");
    scanf("\t%s", text);
    fprintf(file, "%s\n", text);
    printf("\n\t RECLAMA��O/SUGEST�O REGISTRADA COM SUCESSO.\n\n");
    fclose(file);
    pause; main();
}

void logo(int x){ //mostra o logo personalizado

    if (x != 1){cls;}
    char line[100];
    FILE*file = fopen("DATABASE//DRAW1.txt", "r");
        if (file != NULL){
            while (fgets(line, 100, file) != NULL)
                printf("\x1b[31m \t\t%s \x1b[0m", line);
        }
    char line2[100];
    FILE*file2 = fopen("DATABASE//DRAW2.txt", "r");
        if (file2 != NULL){
            while (fgets(line2, 100, file2) != NULL)
                printf("\x1b[33m \t\t%s \x1b[0m", line2);
        }
    printf("\n    -------- UNIPESTANA, copyright: \x1b[33mJETA\x1b[0ms Software Solutions! UNIDADE 1, SANTOS RANGEL --------\n\n\n");
}
