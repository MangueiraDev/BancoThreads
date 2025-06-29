#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "fila.h"
#include "banco.h"

FilaMonitor fila;

Operacao gerar_operacao_aleatoria() {
    Operacao op;
    int tipo = rand() % 3;
    op.tipo = (TipoOperacao)tipo;

    switch (op.tipo) {
        case DEPOSITO:
            op.valor = (float)(rand() % 500 + 1);
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
        Operacao op = gerar_operacao_aleatoria();
        produzir(&fila, op);
        usleep(500000); 
    }
    return NULL;
}

void* consumidor(void* arg) {
    while (1) {
        consumir(&fila);
        usleep(500000);
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    inicializar_banco();

    iniciar_fila(&fila);

    pthread_t tid_produtor1, tid_produtor2, tid_consumidor;

    pthread_create(&tid_produtor1, NULL, produtor, NULL);
    pthread_create(&tid_produtor2, NULL, produtor, NULL);
    pthread_create(&tid_consumidor, NULL, consumidor, NULL);

    pthread_join(tid_produtor1, NULL);
    pthread_join(tid_produtor2, NULL);
    pthread_join(tid_consumidor, NULL);

    return 0;
}
