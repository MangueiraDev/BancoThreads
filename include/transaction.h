#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <pthread.h>

typedef enum {
    DEPOSITO,
    SAQUE,
    TRANSFERENCIA
} TipoTransacao;

typedef struct {
    TipoTransacao tipo;
    int conta_origem;
    int conta_destino;
    double valor;
} Transacao;

#endif // TRANSACTION_H