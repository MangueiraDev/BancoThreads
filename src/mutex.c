#include <unistd.h>
#include <pthread.h>
#include "queue.h"
#include "account.h"
#include "utils.h"
#include <stdio.h>

void* servidor(void* arg) {
    Transacao t;
    while (1) {
        if (desenfileirar(&t) == 0) {
            printf("[Thread %p] ", (void*)pthread_self());
            imprimir_transacao(t);
            switch (t.tipo) {
                case DEPOSITO:
                    depositar(t.origem, t.valor);
                    break;
                case SAQUE:
                    sacar(t.origem, t.valor);
                    break;
                case TRANSFERENCIA:
                    transferir(t.origem, t.destino, t.valor);
                    break;
            }
        } else {
            usleep(100000);
        }
    }
    return NULL;
}