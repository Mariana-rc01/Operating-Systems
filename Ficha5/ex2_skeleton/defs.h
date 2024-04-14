
#define SERVER "fifo_server"
#define CLIENT "fifo_client"

typedef struct msg{
    int needle; // nº que queremos procurar
    int pid; // pid do processo (identificador)
    int occurrences; // resultado
} Msg;

// criámos do mesmo modelo "fifo_pid" ou "cliente_pid" -> protocolo
// no tp temos que justificar as nossas decisões
// fazemos client e server na mesma estrutura para manter tudo junto