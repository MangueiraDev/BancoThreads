#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <pthread.h>

#define NUM_CONTAS 10

typedef struct {
    int id;
    float saldo;
    pthread_mutex_t mutex;
} Conta;

extern Conta contas[NUM_CONTAS];

void inicializar_contas();

int depositar(int conta_id, float valor);
int sacar(int conta_id, float valor);
int transferir(int origem_id, int destino_id, float valor);
float obter_saldo(int conta_id);

#endif