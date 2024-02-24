#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "person.h"

// Função para listar as N primeiras pessoas do arquivo binário
void listar_pessoas(int N) {
    FILE *arquivo = fopen("pessoas.bin", "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    PESSOA pessoa;
    int contador = 0;
    while (fread(&pessoa, sizeof(PESSOA), 1, arquivo) == 1 && contador < N) {
        printf("Nome: %s, Idade: %d\n", get_nome(pessoa), get_idade(pessoa));
        contador++;
    }

    fclose(arquivo);
}

int main(int argc, char* argv[]){

    FILE* arquivo = fopen("registos.bin","wb");
    if (arquivo == NULL){
        perror("Erro ao abrir o ficheiro binário\n");
        return 1;
    }

    PESSOA pessoas[4] = {
        create("Mariana",22),
        create("Hugo",21),
        create("Margarida",0),
        create("Maria",0)
    };

    for (int i = 0; i < 4; i++){
        if (fwrite(&pessoas[i], sizeof(PESSOA),1,arquivo) != 1) {
            perror("Erro ao escrever no ficheiro\n");
            fclose(arquivo);
            return 1;
        }
    }

    if (argc < 3) {
        printf("Usage:\n");
        printf("Add new person: ./pessoas -i [name] [age]\n");
        printf("List N persons: ./pessoas -l [N]\n");
        printf("Change person age: ./pessoas -u [name] [age]\n");
        printf("Change person age (v2): ./pessoas -o [position] [age]\n");
        return 1;
    }

    if (strcmp(argv[1],"-i") == 0){
        int idade = atoi(argv[3]);
        PESSOA pessoaA = create(strdup(argv[2]),idade);
        fwrite(&pessoaA, sizeof(PESSOA),1,arquivo);
    }

    if (strcmp(argv[1],"-l") == 0){
        listar_pessoas(10);
    }

    if (strcmp(argv[1],"-u") == 0){
        // TO DO
    }

    if (strcmp(argv[1],"-o") == 0){
        // TO DO
    }

    return 0;
}
