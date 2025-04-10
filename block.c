#include "block.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>




void inicializarBloco(Bloco* bloco, const char* hashAnterior, int ind) {
    bloco->indice = ind;
    time_t agora = time(NULL);
    strftime(bloco->timestamp, sizeof(bloco->timestamp), "%Y-%m-%d %H:%M:%S", localtime(&agora));
    strcpy(bloco->hashAnterior, hashAnterior);
    bloco->qtdTransacoes = 0;
    bloco->nonce = 0;
    calcularRaizMerkle(bloco);
}

void adicionarTransacao(Bloco* bloco, const char* transacao) {
    if (bloco->qtdTransacoes < MAX_TRANSACOES) {
        strcpy(bloco->transacoes[bloco->qtdTransacoes++], transacao);
        calcularRaizMerkle(bloco);
    } else {
        printf("Bloco cheio! Não é possível adicionar mais transações.\n");
    }
}

void calcularRaizMerkle(Bloco* bloco) {
    // Se o bloco não contém transações, define a raiz da Merkle Tree como "0"
    if (bloco->qtdTransacoes == 0) {
        strcpy(bloco->raizMerkle, "0");
        return;
    }

    // Criamos um array para armazenar os hashes das transações
    char hashes[MAX_TRANSACOES][EVP_MAX_MD_SIZE * 2 + 1];
    int numHashes = bloco->qtdTransacoes;  // Número total de transações

    // Passo 1: Gerar os hashes SHA-256 de cada transação e armazená-los no array
    for (int i = 0; i < numHashes; i++) {                                                             //  <--       Parte 1 (criacao de hashes individuais)
        calcularHashSHA256(bloco->transacoes[i], hashes[i]); // Gera o hash de cada transação
    }

    // Passo 2: Construir a árvore de Merkle reduzindo os hashes até restar um único hash
    while (numHashes > 1) {
        int novaQtd = 0; // Contador para o novo nível de hashes gerados

        for (int i = 0; i < numHashes; i += 2) { // Percorre os hashes de dois em dois
            char combinado[EVP_MAX_MD_SIZE * 4 + 1] = {0}; // Buffer para armazenar a concatenação de dois hashes

            if (i + 1 < numHashes) {
                // Se houver um par, concatena os dois hashes adjacentes
                snprintf(combinado, sizeof(combinado), "%s%s", hashes[i], hashes[i + 1]);                             // <-- Parte 2 (combinar pares de hashes recursivamente)
            } else {
                // Se houver um número ímpar de hashes, duplica o último hash para manter a árvore balanceada
                snprintf(combinado, sizeof(combinado), "%s%s", hashes[i], hashes[i]);
            }

            // Calcula o hash do novo nível e armazena no próximo nível da árvore
            calcularHashSHA256(combinado, hashes[novaQtd]);                                                         // <-- Parte 2 Um novo hash eh gerado
            novaQtd++; // Incrementa a contagem de novos hashes formados
        }
        numHashes = novaQtd; // Atualiza a quantidade de hashes restantes no nível
    }

    // O último hash restante é a **Merkle Root**, que é armazenada no bloco
    strcpy(bloco->raizMerkle, hashes[0]);                                          // <-- Parte 3 o processo sera repetido ate restar 1 ultimo hash q sera a raiz da arvore merkle
}


void provaDeTrabalho(Bloco* bloco) {
    char dadosBloco[1024];
    do {
        bloco->nonce++;
        sprintf(dadosBloco, "%d%s%s%s%d", bloco->indice, bloco->timestamp, bloco->hashAnterior, bloco->raizMerkle, bloco->nonce);
        calcularHashSHA256(dadosBloco, bloco->hash);
    } while (strncmp(bloco->hash, "0000", 4) != 0);
}

void calcularHashSHA256(const char* entrada, char hash[EVP_MAX_MD_SIZE * 2 + 1]) {
    EVP_MD_CTX* contexto = EVP_MD_CTX_new();
    const EVP_MD* algoritmo = EVP_sha256();
    unsigned char hashBinario[EVP_MAX_MD_SIZE];
    unsigned int tamanhoHash = 0;

    if (contexto) {
        if (EVP_DigestInit_ex(contexto, algoritmo, NULL)) {
            if (EVP_DigestUpdate(contexto, entrada, strlen(entrada))) {
                if (EVP_DigestFinal_ex(contexto, hashBinario, &tamanhoHash)) {
                    for (unsigned int i = 0; i < tamanhoHash; i++) {
                        sprintf(hash + (i * 2), "%02x", hashBinario[i]);
                    }
                    hash[tamanhoHash * 2] = '\0';
                }
            }
        }
        EVP_MD_CTX_free(contexto);
    }
}