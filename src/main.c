// main.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "queue.h"
#include "account.h"
#include "utils.h"

#define NUM_CLIENTES 2
#define NUM_SERVIDORES 2

FilaTransacoes fila;

void* cliente_thread(void* arg) {
    for (int i = 0; i < 3; i++) {
        Transacao t = criar_transacao_interativa();
        adicionar_transacao(&fila, t);
    }
    return NULL;
}

void* servidor_thread(void* arg) {
    Transacao t;
    while (1) {
        if (remover_transacao(&fila, &t) == 0) {
            log_transacao(t);
            if (t.tipo == 0) depositar(t.destino, t.valor);
            else if (t.tipo == 1) sacar(t.origem, t.valor);
            else if (t.tipo == 2) transferir(t.origem, t.destino, t.valor);
        }
    }
    return NULL;
}

int main() {
    pthread_t clientes[NUM_CLIENTES];
    pthread_t servidores[NUM_SERVIDORES];

    inicializar_contas();
    iniciar_fila(&fila);

    for (int i = 0; i < NUM_CLIENTES; i++) {
        pthread_create(&clientes[i], NULL, cliente_thread, NULL);
    }

    for (int i = 0; i < NUM_SERVIDORES; i++) {
        pthread_create(&servidores[i], NULL, servidor_thread, NULL);
    }

    for (int i = 0; i < NUM_CLIENTES; i++) {
        pthread_join(clientes[i], NULL);
    }

    sleep(1);
    fim_das_transacoes();
    return 0;
}