#ifndef FILA_H
#define FILA_H

#include <pthread.h>

#define TAM_MAX 10

typedef enum {
    DEPOSITO,
    SAQUE,
    CONSULTA
} TipoOperacao;

typedef struct {
    TipoOperacao tipo;
    float valor;
} Operacao;

typedef struct {
    Operacao itens[TAM_MAX];
    int frente;
    int tras;
    int tamanho;

    pthread_mutex_t mutex;
    pthread_cond_t cond_vazio;
    pthread_cond_t cond_cheio;
} FilaMonitor;

void iniciar_fila(FilaMonitor* fila);
int fila_vazia(FilaMonitor* fila);
int fila_cheia(FilaMonitor* fila);
int enfileirar(FilaMonitor* fila, Operacao op);
int desenfileirar(FilaMonitor* fila, Operacao* op);
void produzir(FilaMonitor* fila, Operacao op);
void consumir(FilaMonitor* fila);

#endif // FILA_H
