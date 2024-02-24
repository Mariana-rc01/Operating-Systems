#ifndef PERSON_H
#define PERSON_H

typedef struct pessoa *PESSOA;

PESSOA create(char* nome, int idade);

void set_nome(PESSOA p, char* nome);

void set_idade(PESSOA p, int i);

char* get_nome(PESSOA p);

int get_idade(PESSOA p);

#endif
