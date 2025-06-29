#include "fila.h"
#include "banco.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void iniciar_fila(FilaMonitor* fila) {
    fila->frente = 0;
    fila->tras = 0;
    fila->tamanho = 0;
    pthread_mutex_init(&fila->mutex, NULL);
    pthread_cond_init(&fila->cond_vazio, NULL);
    pthread_cond_init(&fila->cond_cheio, NULL);
}

void destruir_fila(FilaMonitor* fila) {
    pthread_mutex_destroy(&fila->mutex);
    pthread_cond_destroy(&fila->cond_vazio);
    pthread_cond_destroy(&fila->cond_cheio);
}

void produzir(FilaMonitor* fila, Operacao op) {
    pthread_mutex_lock(&fila->mutex);

    while (fila->tamanho == TAM_MAX) {
        printf("[Aviso] A fila está cheia! Produtor esperando...\n");
        pthread_cond_wait(&fila->cond_cheio, &fila->mutex);
    }

    fila->itens[fila->tras] = op;
    fila->tras = (fila->tras + 1) % TAM_MAX;
    fila->tamanho++;

    printf("[Produtor] Enfileirou operação tipo %d valor %.2f\n", op.tipo, op.valor);

    pthread_cond_signal(&fila->cond_vazio);
    pthread_mutex_unlock(&fila->mutex);
}

void consumir(FilaMonitor* fila) {
    pthread_mutex_lock(&fila->mutex);

    while (fila->tamanho == 0) {
        pthread_cond_wait(&fila->cond_vazio, &fila->mutex);
    }

    Operacao op = fila->itens[fila->frente];
    fila->frente = (fila->frente + 1) % TAM_MAX;
    fila->tamanho--;

    pthread_cond_signal(&fila->cond_cheio);
    pthread_mutex_unlock(&fila->mutex);

    switch (op.tipo) {
        case DEPOSITO:
            depositar(op.valor);
            printf("[Depósito] +%.2f\n", op.valor);
            break;
        case SAQUE:
            if (sacar(op.valor))
                printf("[Saque] -%.2f\n", op.valor);
            else
                printf("[Saque] saldo insuficiente para -%.2f\n", op.valor);
            break;
        case CONSULTA:
            printf("[Consulta] Saldo atual: %.2f\n", consultar());
            break;
        default:
            printf("[Erro] Tipo de operação inválido\n");
    }
}
