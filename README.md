#  Projeto Blockchain

Este projeto implementa um sistema de blockchain básico com as seguintes funcionalidades principais:
- **Criação do Bloco Gênesis**
- **Gestão de Transações**
- **Cálculo da Árvore de Merkle**
- **Prova de Trabalho (Mineração)**
- **Ajuste Dinâmico de Dificuldade**

É uma implementação simples, projetada para simular as funções principais de um sistema de blockchain, fornecendo uma base para construir projetos mais avançados de blockchain.

##  Principais Funcionalidades

- **Bloco Gênesis**: O primeiro bloco da blockchain, criado com um hash especial "zero".
- **Prova de Trabalho**: O processo de mineração onde cada bloco requer trabalho computacional para ser adicionado à blockchain.
- **Árvore de Merkle**: Uma estrutura de dados utilizada para verificar de forma eficiente a integridade das transações dentro de um bloco.
- **Ajuste Dinâmico de Dificuldade**: A dificuldade de mineração é ajustada dinamicamente para garantir que os blocos sejam minerados a uma taxa constante.
- **Simulação de Ataques**: Simula ataques na blockchain, alterando transações e recalculando os hashes.

##  Estrutura do Projeto

- **block.h / block.c**: Contém as definições e a lógica para gerenciar blocos individuais, incluindo a gestão de transações e o cálculo da árvore de Merkle.
- **blockchain.h / blockchain.c**: Gerencia a blockchain como um todo, incluindo a adição de blocos, salvamento/carregamento da blockchain e ajuste de dificuldade da mineração.
- **main.c**: O ponto de entrada principal para o aplicativo. Ele lida com a entrada do usuário, interage com a blockchain e controla o processo de mineração.

##  Como Funciona

### Estrutura do Bloco

Cada bloco na blockchain contém os seguintes componentes:
- `index`: Um identificador único para o bloco.
- `timestamp`: O horário em que o bloco foi criado.
- `previousHash`: Uma referência ao hash do bloco anterior.
- `merkleRoot`: O hash raiz da árvore de Merkle, que verifica a integridade de todas as transações dentro do bloco.
- `transactions`: Uma lista de transações armazenadas no bloco.
- `nonce`: Um valor utilizado no algoritmo de prova de trabalho para garantir a dificuldade da mineração.
- `hash`: O hash do bloco completo.

### Processo de Mineração (Prova de Trabalho)
- O processo de mineração envolve encontrar um `nonce` válido que resulta em um hash de bloco começando com um determinado número de zeros (a dificuldade atual). Este é um processo computacionalmente caro, garantindo segurança e descentralização.

### Ajuste de Dificuldade
- A cada poucos blocos, a dificuldade de mineração é ajustada. Se os blocos estão sendo minerados muito rapidamente, a dificuldade aumenta; se estão sendo minerados muito lentamente, a dificuldade diminui.

### Verificando Transações
- A blockchain usa uma árvore de Merkle para verificar de forma eficiente se uma transação pertence a um bloco. Isso é essencial para a escalabilidade em blockchains no mundo real.

##  Começando

### Pré-requisitos
Certifique-se de que você tenha o seguinte instalado:
- **OpenSSL**: Para funções criptográficas (hashing SHA-256).
- **Compilador C**: Para compilar e rodar o projeto.

### Compilando o Projeto

1. Clone este repositório.
2. Abra um terminal e navegue até o diretório do projeto.
3. Compile o projeto:

```bash
gcc -o blockchain main.c blockchain.c block.c -lssl -lcrypto
