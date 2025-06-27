#ifndef UTILS_H
#define UTILS_H

#include "transaction.h"

// Gera uma transação aleatória (modo automático, se necessário)
Transacao gerar_transacao_aleatoria();

// Permite o usuário criar a transação via input
Transacao criar_transacao_interativa();

// Mostra no terminal os detalhes da transação
void log_transacao(Transacao t);

// Notifica que não haverá mais transações
void fim_das_transacoes();

#endif