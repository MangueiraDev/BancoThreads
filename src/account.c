#include <stdio.h>
#include <pthread.h>
#include "account.h"

Conta contas[NUM_CONTAS];

void inicializar_contas() {
    for (int i = 0; i < NUM_CONTAS; i++) {
        contas[i].id = i;
        contas[i].saldo = 1000.0; // saldo inicial
        pthread_mutex_init(&contas[i].mutex, NULL);
    }
}

int depositar(int conta_id, float valor) {
    if (conta_id < 0 || conta_id >= NUM_CONTAS || valor < 0) return -1;

    pthread_mutex_lock(&contas[conta_id].mutex);
    contas[conta_id].saldo += valor;
    pthread_mutex_unlock(&contas[conta_id].mutex);
    return 0;
}

int sacar(int conta_id, float valor) {
    if (conta_id < 0 || conta_id >= NUM_CONTAS || valor < 0) return -1;

    pthread_mutex_lock(&contas[conta_id].mutex);
    if (contas[conta_id].saldo >= valor) {
        contas[conta_id].saldo -= valor;
        pthread_mutex_unlock(&contas[conta_id].mutex);
        return 0;
    } else {
        pthread_mutex_unlock(&contas[conta_id].mutex);
        return -1;
    }
}

int transferir(int origem_id, int destino_id, float valor) {
    if (origem_id < 0 || destino_id < 0 || origem_id >= NUM_CONTAS || destino_id >= NUM_CONTAS || valor < 0) return -1;

    int first = origem_id < destino_id ? origem_id : destino_id;
    int second = origem_id < destino_id ? destino_id : origem_id;

    pthread_mutex_lock(&contas[first].mutex);
    pthread_mutex_lock(&contas[second].mutex);

    if (contas[origem_id].saldo >= valor) {
        contas[origem_id].saldo -= valor;
        contas[destino_id].saldo += valor;
        pthread_mutex_unlock(&contas[second].mutex);
        pthread_mutex_unlock(&contas[first].mutex);
        return 0;
    } else {
        pthread_mutex_unlock(&contas[second].mutex);
        pthread_mutex_unlock(&contas[first].mutex);
        return -1;
    }
}

float obter_saldo(int conta_id) {
    float saldo = 0.0;
    if (conta_id < 0 || conta_id >= NUM_CONTAS) return saldo;

    pthread_mutex_lock(&contas[conta_id].mutex);
    saldo = contas[conta_id].saldo;
    pthread_mutex_unlock(&contas[conta_id].mutex);
    return saldo;
}