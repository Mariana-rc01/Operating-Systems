#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct pessoa {
    char nome[30];
    int idade;
} Pessoa;

int main(int argc, char* argv[]){

    if (argc < 3 || argc > 4){
        printf("Usage:\n");
        printf("Add new person: ./pessoas -i [name] [age]\n");
        printf("List N persons: ./pessoas -l [N]\n");
        printf("Change person age: ./pessoas -u [name] [age]\n");
        printf("Change person age (v2): ./pessoas -o [position] [age]\n");
        return 1;
    }

    if (strcmp(argv[1],"-i") == 0){
        int file = open("registos.bin", O_CREAT | O_APPEND | O_RDWR, 0640);
        int idade = atoi(argv[3]);
        Pessoa pessoa;
        strcpy(pessoa.nome, argv[2]);
        pessoa.idade = idade;
        
        int bytes = write(file,&pessoa,sizeof(Pessoa));

        if (bytes < 0){
            perror("Error on write");
            return 1;
        }

        // Exercício 4
        printf("Registo efetuado na posição %ld\n", lseek(file, 0, SEEK_END) / sizeof(Pessoa));
    }

    if (strcmp(argv[1],"-l") == 0){
        int file = open("registos.bin", O_RDONLY);
        Pessoa pessoa;
        while (read(file, &pessoa, sizeof(Pessoa)) > 0){
            printf("Nome: %s; Idade: %d\n",pessoa.nome, pessoa.idade);
        }
    }

    if (strcmp(argv[1],"-u") == 0){
        int file = open("registos.bin", O_CREAT | O_RDWR, 0640);
        Pessoa pessoa;
        while (read(file, &pessoa,sizeof(Pessoa)) > 0){
            if (strcmp(pessoa.nome, argv[2]) == 0){
                pessoa.idade = atoi(argv[3]);
                lseek(file, -sizeof(Pessoa),SEEK_CUR);
                write(file, &pessoa, sizeof(Pessoa));
            }
        }
    }

    if (strcmp(argv[1],"-o") == 0){
        int file = open("registos.bin", O_CREAT | O_RDWR, 0640);
    
        Pessoa pessoa;

        lseek(file, (atoi(argv[2])-1)*sizeof(Pessoa),SEEK_SET);

        read(file, &pessoa, sizeof(Pessoa));
        pessoa.idade = atoi(argv[3]);

        lseek(file, -sizeof(Pessoa), SEEK_CUR);
        write(file, &pessoa, sizeof(Pessoa));

    }

    return 0;
}
