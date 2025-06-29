#include <pthread.h>
#include "banco.h"

static float saldo = 1000.0f;
static pthread_mutex_t mutex_saldo;

void inicializar_banco() {
    pthread_mutex_init(&mutex_saldo, NULL);
    saldo = 1000.0f;
}

void depositar(float valor) {
    pthread_mutex_lock(&mutex_saldo);
    saldo += valor;
    pthread_mutex_unlock(&mutex_saldo);
}

int sacar(float valor) {
    int sucesso = 0;
    pthread_mutex_lock(&mutex_saldo);
    if (saldo >= valor) {
        saldo -= valor;
        sucesso = 1;
    }
    pthread_mutex_unlock(&mutex_saldo);
    return sucesso;
}

float consultar() {
    float s;
    pthread_mutex_lock(&mutex_saldo);
    s = saldo;
    pthread_mutex_unlock(&mutex_saldo);
    return s;
}
