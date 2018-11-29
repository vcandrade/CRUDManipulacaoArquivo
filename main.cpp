
/* 
 * File:   main.cpp
 * Author: Vinicius
 *
 * Created on 29 de Novembro de 2018, 18:36
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Pessoa {
    char nome [30];
    char endereco [50];
    int idade;
    bool status;
};

void cadastrar() {

    Pessoa pessoa;
    FILE *arquivo;

    system("clear");

    if ((arquivo = fopen("BancoDados.txt", "ab")) == NULL) {

        printf("Erro ao abrir o arquivo.\n");

        printf("Pressione ENTER para continuar...");
        getchar();

        exit(1);
    }

    setbuf(stdin, NULL);

    printf("<<<NOVO CADASTRO>>>\n\n");
    printf("Nome: ");
    gets(pessoa.nome);
    printf("Endereco: ");
    gets(pessoa.endereco);
    printf("Idade: ");
    scanf("%d", &pessoa.idade);
    pessoa.status = true;

    if (fwrite(&pessoa, sizeof (struct Pessoa), 1, arquivo) == 1) {

        printf("\nCadastro realizado com sucesso.\n");

    } else {

        printf("\nErro ao efetuar o cadastro.\n");
    }

    fclose(arquivo);

    printf("\nPressione ENTER para continuar...");
    setbuf(stdin, NULL);
    getchar();
}

void visualizarListaCompleta() {

    Pessoa pessoa;
    FILE *arquivo;

    system("clear");

    printf("<<<LISTA COMPLETA>>>\n");

    if ((arquivo = fopen("BancoDados.txt", "rb")) == NULL) {

        printf("Erro ao abrir o arquivo.\n");

        printf("Pressione ENTER para continuar...");
        getchar();

        exit(1);
    }

    while (!feof(arquivo)) {

        if (fread(&pessoa, sizeof (struct Pessoa), 1, arquivo) == 1) {

            if (pessoa.status) {

                printf("\nNome: %s", pessoa.nome);
                printf("\nEndereco: %s", pessoa.endereco);
                printf("\nIdade: %d\n", pessoa.idade);
            }
        }
    }

    fclose(arquivo);

    printf("\nPressione ENTER para continuar...");
    setbuf(stdin, NULL);
    getchar();
}

void buscarPessoa() {

    FILE *arquivo;
    Pessoa pessoa;
    char pesquisa[50];
    bool verificacao = false;
    char *substring;

    system("clear");

    printf("<<<BUSCA PERSONALIZADA>>>\n");

    if ((arquivo = fopen("BancoDados.txt", "r+b")) == NULL) {

        printf("Erro ao abrir o arquivo.\n");

        printf("Pressione ENTER para continuar...");
        getchar();

        exit(1);
    }

    setbuf(stdin, NULL);

    printf("\nPesquisar: ");
    gets(pesquisa);

    while (!feof(arquivo)) {

        if (fread(&pessoa, sizeof (struct Pessoa), 1, arquivo) == 1) {

            substring = strstr(strupr(pessoa.nome), strupr(pesquisa));

            if (substring != NULL && pessoa.status) {

                printf("\nNome: %s", pessoa.nome);
                printf("\nEndereco: %s", pessoa.endereco);
                printf("\nIdade: %d\n", pessoa.idade);
                verificacao = true;
            }
        }
    }

    if (!verificacao) {

        printf("\nCadastro inexistente.\n");
    }

    fclose(arquivo);

    printf("\nPressione ENTER para continuar...");
    setbuf(stdin, NULL);
    getchar();
}

void atualizarRegistro() {

    FILE *arquivo;
    Pessoa pessoa;
    char pesquisa[50];
    bool verificacao = false;
    char *substring;
    int cont = 0;
    char opcao;

    system("clear");

    printf("<<<ATUALIZAR REGISTRO>>>\n");

    if ((arquivo = fopen("BancoDados.txt", "r+b")) == NULL) {

        printf("Erro ao abrir o arquivo.\n");
        system("pause");
        exit(1);
    }

    setbuf(stdin, NULL);

    printf("\nPesquisar: ");
    gets(pesquisa);

    while (!feof(arquivo)) {

        if (fread(&pessoa, sizeof (struct Pessoa), 1, arquivo) == 1) {

            substring = strstr(strupr(pessoa.nome), strupr(pesquisa));

            if (substring != NULL && pessoa.status) {

                printf("\nNome: %s", pessoa.nome);
                printf("\nEndereco: %s", pessoa.endereco);
                printf("\nIdade: %d\n", pessoa.idade);
                verificacao = true;
                break;
            }

        }
        cont++;
    }

    if (!verificacao) {

        printf("\nCadastro inexistente.\n");

    } else {

        printf("\nDeseja atualizar o cadastro? (s/n) ");
        scanf("%s", &opcao);

        if (opcao == 's') {

            printf("\n<<<ATUALIZACAO DE DADOS>>>\n\n");
            printf("Nome: ");
            setbuf(stdin, NULL);
            gets(pessoa.nome);
            printf("Endereco: ");
            gets(pessoa.endereco);
            printf("Idade: ");
            scanf("%d", &pessoa.idade);

            fseek(arquivo, sizeof (struct Pessoa) * cont, SEEK_SET);
            fwrite(&pessoa, sizeof (struct Pessoa), 1, arquivo);

            printf("\nRegistro atualizado com sucesso.\n");
        }
    }

    fclose(arquivo);

    printf("\nPressione ENTER para continuar...");
    setbuf(stdin, NULL);
    getchar();
}

void removerRegistro() {

    FILE *arquivo;
    Pessoa pessoa;
    char pesquisa[50];
    bool verificacao = false;
    char *substring;
    int cont = 0;
    char opcao;
    
    system("clear");

    printf("<<<REMOVER REGISTRO>>>\n");

    if ((arquivo = fopen("BancoDados.txt", "r+b")) == NULL) {

        printf("Erro ao abrir o arquivo.\n");
        system("pause");
        exit(1);
    }

    setbuf(stdin, NULL);
    
    printf("\nPesquisar: ");
    gets(pesquisa);

    while (!feof(arquivo)) {

        if (fread(&pessoa, sizeof (struct Pessoa), 1, arquivo) == 1) {

            if (pessoa.status) {

                substring = strstr(strupr(pessoa.nome), strupr(pesquisa));

                if (substring != NULL) {

                    printf("\nNome: %s", pessoa.nome);
                    printf("\nEndereco: %s", pessoa.endereco);
                    printf("\nIdade: %d\n", pessoa.idade);
                    verificacao = true;
                    break;
                }
            }
        }
        cont++;
    }

    if (!verificacao) {

        printf("\nCadastro inexistente.\n");

    } else {

        printf("\nDeseja realmente excluir este registro? (s/n) ");
        scanf("%s", &opcao);

        if (opcao == 's') {

            pessoa.status = false;

            fseek(arquivo, sizeof (struct Pessoa) * cont, SEEK_SET);
            fwrite(&pessoa, sizeof (struct Pessoa), 1, arquivo);

            printf("\nRegistro excluido com sucesso.\n");
        }
    }

    fclose(arquivo);

    printf("\nPressione ENTER para continuar...");
    setbuf(stdin, NULL);
    getchar();
}

int main(int argc, char** argv) {

    int opcao = 0;

    do {
        
        system("clear");

        printf("<<<MENU PRINCIPAL>>>\n\n");
        printf("1 - Novo Cadastro\n");
        printf("2 - Visualizar Todos\n");
        printf("3 - Buscar por Nome\n");
        printf("4 - Atualizar Cadastro\n");
        printf("5 - Excluir Cadastro\n");
        printf("6 - SAIR\n\n");

        setbuf(stdin, NULL);
        
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar();
                break;

            case 2:
                visualizarListaCompleta();
                break;

            case 3:
                buscarPessoa();
                break;

            case 4:
                atualizarRegistro();
                break;

            case 5:
                removerRegistro();
                break;

            case 6:
                continue;

            default:
                printf("\nOpcao invalida.\n");
                printf("\nPressione ENTER para continuar...");
                setbuf(stdin, NULL);
                getchar();
                break;
        }
    } while (opcao != 6);

    return 0;
}

