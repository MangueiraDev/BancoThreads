#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "queue.h"

void iniciar_fila(FilaTransacoes* fila) {
    fila->frente = 0;
    fila->tras = 0;
    fila->tamanho = 0;
    pthread_mutex_init(&fila->mutex, NULL);
    pthread_cond_init(&fila->cond_vazio, NULL);
    pthread_cond_init(&fila->cond_cheio, NULL);
}

int fila_vazia(FilaTransacoes* fila) {
    return fila->tamanho == 0;
}

int fila_cheia(FilaTransacoes* fila) {
    return fila->tamanho == TAM_FILA;
}

int adicionar_transacao(FilaTransacoes* fila, Transacao t) {
    pthread_mutex_lock(&fila->mutex);

    while (fila_cheia(fila)) {
        pthread_cond_wait(&fila->cond_cheio, &fila->mutex);
    }

    fila->itens[fila->tras] = t;
    fila->tras = (fila->tras + 1) % TAM_FILA;
    fila->tamanho++;

    pthread_cond_signal(&fila->cond_vazio);
    pthread_mutex_unlock(&fila->mutex);
    return 0;
}

int remover_transacao(FilaTransacoes* fila, Transacao* t) {
    pthread_mutex_lock(&fila->mutex);

    while (fila_vazia(fila)) {
        pthread_cond_wait(&fila->cond_vazio, &fila->mutex);
    }

    *t = fila->itens[fila->frente];
    fila->frente = (fila->frente + 1) % TAM_FILA;
    fila->tamanho--;

    pthread_cond_signal(&fila->cond_cheio);
    pthread_mutex_unlock(&fila->mutex);
    return 0;
}