#ifndef QUEUE_H
#define QUEUE_H

#include <pthread.h>
#include "transaction.h"

#define TAM_FILA 100

typedef struct {
    Transacao itens[TAM_FILA];
    int frente;
    int tras;
    int tamanho;

    pthread_mutex_t mutex;
    pthread_cond_t cond_vazio;
    pthread_cond_t cond_cheio;
} FilaTransacoes;

void iniciar_fila(FilaTransacoes* fila);
int adicionar_transacao(FilaTransacoes* fila, Transacao t);
int remover_transacao(FilaTransacoes* fila, Transacao* t);
int fila_vazia(FilaTransacoes* fila);
int fila_cheia(FilaTransacoes* fila);

#endif