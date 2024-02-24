#include "person.h"

#include <stdlib.h>
#include <string.h>

struct pessoa {
    char* nome;
    int idade;
};

PESSOA create(char* nome, int idade){
    PESSOA p = malloc(sizeof(struct pessoa));
    p->nome = strdup(nome);
    p->idade = idade;
    return p;
}

void set_nome(PESSOA p, char* nome) {
    p->nome = strdup(nome);
}

void set_idade(PESSOA p, int i) {
    p->idade = i;
}

char* get_nome(PESSOA p){
    return strdup(p->nome);
}

int get_idade(PESSOA p){
    return p->idade;
}
