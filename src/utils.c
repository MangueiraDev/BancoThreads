#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

Transacao criar_transacao_interativa() {
    Transacao t;
    int tipo;
    printf("\nTipo de transação: [0] Depósito  [1] Saque  [2] Transferência\nEscolha: ");
    scanf("%d", &tipo);
    t.tipo = tipo;

    if (tipo == 0) {
        printf("Conta destino (0 a 9): ");
        scanf("%d", &t.destino);
        printf("Valor: ");
        scanf("%f", &t.valor);
    } else if (tipo == 1) {
        printf("Conta origem (0 a 9): ");
        scanf("%d", &t.origem);
        printf("Valor: ");
        scanf("%f", &t.valor);
    } else if (tipo == 2) {
        printf("Conta origem (0 a 9): ");
        scanf("%d", &t.origem);
        printf("Conta destino (0 a 9): ");
        scanf("%d", &t.destino);
        printf("Valor: ");
        scanf("%f", &t.valor);
    } else {
        printf("Tipo inválido. Criando transação nula.\n");
        t.tipo = -1;
    }

    return t;
}

void log_transacao(Transacao t) {
    const char* tipos[] = { "Depósito", "Saque", "Transferência" };
    printf("[LOG] Tipo: %s | ", tipos[t.tipo]);
    if (t.tipo == 0) {
        printf("Destino: %d | Valor: %.2f\n", t.destino, t.valor);
    } else if (t.tipo == 1) {
        printf("Origem: %d | Valor: %.2f\n", t.origem, t.valor);
    } else if (t.tipo == 2) {
        printf("Origem: %d -> Destino: %d | Valor: %.2f\n", t.origem, t.destino, t.valor);
    }
}

void fim_das_transacoes() {
    printf("\n[FIM] Nenhuma transação restante. Encerrando.\n");
}