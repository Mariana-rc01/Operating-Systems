#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para os dados de uma pessoa
typedef struct {
    char nome[100]; // Suponha um nome com até 100 caracteres
    int idade;
} Pessoa;

// Função para adicionar uma nova pessoa ao arquivo binário
void adicionar_pessoa(const char *nome, int idade) {
    FILE *arquivo = fopen("pessoas.bin", "ab");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    Pessoa nova_pessoa;
    strcpy(nova_pessoa.nome, nome);
    nova_pessoa.idade = idade;

    fwrite(&nova_pessoa, sizeof(Pessoa), 1, arquivo);

    fclose(arquivo);
}

// Função para listar as N primeiras pessoas do arquivo binário
void listar_pessoas(int N) {
    FILE *arquivo = fopen("pessoas.bin", "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    Pessoa pessoa;
    int contador = 0;
    while (fread(&pessoa, sizeof(Pessoa), 1, arquivo) == 1 && contador < N) {
        printf("Nome: %s, Idade: %d\n", pessoa.nome, pessoa.idade);
        contador++;
    }

    fclose(arquivo);
}

// Função para atualizar a idade de uma pessoa no arquivo binário
void atualizar_idade(const char *nome, int nova_idade) {
    FILE *arquivo = fopen("pessoas.bin", "r+b");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    Pessoa pessoa;
    while (fread(&pessoa, sizeof(Pessoa), 1, arquivo) == 1) {
        if (strcmp(pessoa.nome, nome) == 0) {
            pessoa.idade = nova_idade;
            fseek(arquivo, -sizeof(Pessoa), SEEK_CUR); // Volta para a posição correta
            fwrite(&pessoa, sizeof(Pessoa), 1, arquivo);
            break;
        }
    }

    fclose(arquivo);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <opcao>\n", argv[0]);
        printf("Opcoes:\n");
        printf("-i <nome> <idade>: Adicionar uma nova pessoa\n");
        printf("-l <N>: Listar as N primeiras pessoas\n");
        printf("-u <nome> <nova_idade>: Atualizar a idade de uma pessoa\n");
        return 1;
    }

    if (strcmp(argv[1], "-i") == 0) {
        if (argc != 4) {
            printf("Uso: %s -i <nome> <idade>\n", argv[0]);
            return 1;
        }
        char *nome = argv[2];
        int idade = atoi(argv[3]);
        adicionar_pessoa(nome, idade);
    } else if (strcmp(argv[1], "-l") == 0) {
        if (argc != 3) {
            printf("Uso: %s -l <N>\n", argv[0]);
            return 1;
        }
        int N = atoi(argv[2]);
        listar_pessoas(N);
    } else if (strcmp(argv[1], "-u") == 0) {
        if (argc != 4) {
            printf("Uso: %s -u <nome> <nova_idade>\n", argv[0]);
            return 1;
        }
        char *nome = argv[2];
        int nova_idade = atoi(argv[3]);
        atualizar_idade(nome, nova_idade);
    } else {
        printf("Opcao invalida\n");
        return 1;
    }

    return 0;
}
