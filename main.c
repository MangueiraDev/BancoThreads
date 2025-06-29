#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "banco.h"
#include <stdlib.h>
#include <time.h>

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
} FilaOperacoes;


void iniciar_fila(FilaOperacoes* fila) {
    fila->frente = 0;
    fila->tras = 0;
    fila->tamanho = 0;
}

int fila_vazia(FilaOperacoes* fila) {
    return fila->tamanho == 0;
}

int fila_cheia(FilaOperacoes* fila) {
    return fila->tamanho == TAM_MAX;
}

int enfileirar(FilaOperacoes* fila, Operacao op) {
    if (fila_cheia(fila)) return 0;
    fila->itens[fila->tras] = op;
    fila->tras = (fila->tras + 1) % TAM_MAX;
    fila->tamanho++;
    return 1;
}

int desenfileirar(FilaOperacoes* fila, Operacao* op) {
    if (fila_vazia(fila)) return 0;
    *op = fila->itens[fila->frente];
    fila->frente = (fila->frente + 1) % TAM_MAX;
    fila->tamanho--;
    return 1;
}


FilaOperacoes fila;
pthread_mutex_t mutex_fila;
pthread_cond_t cond_vazio, cond_cheio;


void* consumidor(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex_fila);

        while (fila_vazia(&fila)) {
            pthread_cond_wait(&cond_vazio, &mutex_fila);
        }

        Operacao op;
        desenfileirar(&fila, &op);

        pthread_cond_signal(&cond_cheio);
        pthread_mutex_unlock(&mutex_fila);

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
                printf("[Consulta] Saldo: %.2f\n", consultar());
                break;
        }
        usleep(500000);
    }
    return NULL;
}
Operacao gerar_operacao_aleatoria() {
    Operacao op;
    int tipo = rand() % 3; // 0,1,2

    op.tipo = (TipoOperacao)tipo;

    switch (op.tipo) {
        case DEPOSITO:
            op.valor = (float)(rand() % 500 + 1); // valor entre 1 e 500
            break;
        case SAQUE:
            op.valor = (float)(rand() % 500 + 1);
            break;
        case CONSULTA:
            op.valor = 0.0f;
            break;
    }
    return op;
}
void* produtor(void* arg) {
    while (1) {

        pthread_mutex_lock(&mutex_fila);
        while (fila_cheia(&fila)) {
            printf("[Aviso] A fila está cheia! Produtor esperando...\n");
            pthread_cond_wait(&cond_cheio, &mutex_fila);
        }
        Operacao op = gerar_operacao_aleatoria();
        enfileirar(&fila, op);
        printf("[Produtor] Enfileirou operação tipo %d valor %.2f\n", op.tipo, op.valor);

        pthread_cond_signal(&cond_vazio);
        pthread_mutex_unlock(&mutex_fila);

        usleep(500000); 
    }
    return NULL;
}


int main() {
    srand(time(NULL));

    inicializar_banco();
    iniciar_fila(&fila);

    pthread_mutex_init(&mutex_fila, NULL);
    pthread_cond_init(&cond_vazio, NULL);
    pthread_cond_init(&cond_cheio, NULL);

    pthread_t tid_consumidor, tid_produtor1, tid_produtor2;
    pthread_create(&tid_consumidor, NULL, consumidor, NULL);
    pthread_create(&tid_produtor1, NULL, produtor, NULL);
    pthread_create(&tid_produtor2, NULL, produtor, NULL);

    pthread_join(tid_consumidor, NULL);
    pthread_join(tid_produtor1, NULL);
    pthread_join(tid_produtor2, NULL);


    return 0;
}

