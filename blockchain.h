#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "block.h"

#define MAX_BLOCOS 100

typedef struct {
    Bloco blocos[MAX_BLOCOS];
    int qtdBlocos;
} Blockchain;

extern int dificuldade;
void inicializarBlockchain(Blockchain* blockchain);
void adicionarBloco(Blockchain* blockchain, Bloco bloco);
void salvarBlockchain(const Blockchain* blockchain, const char* arquivo);
void carregarBlockchain(Blockchain* blockchain, const char* arquivo);
void exibirBlockchain(const Blockchain* blockchain);
void simularAtaque(Blockchain* blockchain, const char* novaTransacao);
void verificarTransacao(const Blockchain* blockchain, int indiceBloco, const char* transacao);
void ajustarDificuldade(Blockchain* blockchain);
#endif