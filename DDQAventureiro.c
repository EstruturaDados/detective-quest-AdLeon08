/*  
-------------------------------------------------------------
    Desafio Detective Quest - Estruturas de Dados e Investigação
    NÍVEL AVENTUREIRO
    Aluno: Aderlon Barbosa Pessoa
    Matéria: Estrutura de Dados
-------------------------------------------------------------
    Descrição:
    este programa amplia o jogo para incluir a coleta e organização de pistas usando uma 
    Árvore de Busca Binária (BST). Agora, ao visitar certos cômodos,
    o jogador encontra pistas que são armazenadas em ordem alfabética.
    
    O jogador pode:
    - Explorar a mansão (como antes);
    - Encontrar pistas automaticamente em alguns cômodos;
    - Ver todas as pistas descobertas em ordem alfabética.
-------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de dados que representa cada sala da mansão (igual ao nível Novato)
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// Estrutura da Árvore de Busca Binária (para armazenar as pistas)
typedef struct Pista {
    char nome[50];           // Nome da pista (por exemplo: "Chave antiga", "Carta rasgada")
    struct Pista *esquerda;  // Ponteiro para pista menor (ordem alfabética)
    struct Pista *direita;   // Ponteiro para pista maior
} Pista;

/*
Função: criarSala
Descrição:
Cria e inicializa uma nova sala na memória dinâmica.
*/
Sala* criarSala(char nome[]) {
    Sala* nova = (Sala*) malloc(sizeof(Sala));
    if (nova == NULL) {
        printf("Erro ao alocar memória para a sala!\n");
        exit(1);
    }
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

/*
Função: criarPista
Descrição:
Cria uma nova pista e a devolve como um nó de árvore.
*/
Pista* criarPista(char nome[]) {
    Pista* nova = (Pista*) malloc(sizeof(Pista));
    if (nova == NULL) {
        printf("Erro ao alocar memória para a pista!\n");
        exit(1);
    }
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

/*
Função: inserirPista
Descrição:
Insere uma nova pista na árvore de busca binária de forma ordenada (alfabética).
Não insere duplicadas.
*/
Pista* inserirPista(Pista* raiz, char nome[]) {
    if (raiz == NULL) {
        return criarPista(nome);
    }

    int cmp = strcmp(nome, raiz->nome);
    if (cmp < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, nome);
    } else if (cmp > 0) {
        raiz->direita = inserirPista(raiz->direita, nome);
    } else {
        printf("Pista '%s' já foi encontrada anteriormente!\n", nome);
    }
    return raiz;
}

/*
Função: buscarPista
Descrição:
Procura uma pista específica pelo nome dentro da BST.
Retorna 1 se encontrada, 0 se não.
*/
int buscarPista(Pista* raiz, char nome[]) {
    if (raiz == NULL)
        return 0;

    int cmp = strcmp(nome, raiz->nome);
    if (cmp == 0)
        return 1;
    else if (cmp < 0)
        return buscarPista(raiz->esquerda, nome);
    else
        return buscarPista(raiz->direita, nome);
}

/*
Função: exibirPistasEmOrdem
Descrição:
Percorre a árvore de pistas em ordem alfabética (esquerda, raiz, direita)
e exibe todas as pistas coletadas.
*/
void exibirPistasEmOrdem(Pista* raiz) {
    if (raiz != NULL) {
        exibirPistasEmOrdem(raiz->esquerda);
        printf("- %s\n", raiz->nome);
        exibirPistasEmOrdem(raiz->direita);
    }
}

/*
Função: explorarSalas
Descrição:
Permite explorar a mansão, igual ao nível Novato, mas agora com pistas.
Alguns cômodos contêm pistas que são automaticamente adicionadas à árvore.
*/
void explorarSalas(Sala* atual, Pista** arvorePistas) {
    char opcao;

    while (1) {
        printf("\nVocê está em: %s\n", atual->nome);
        printf("Escolha uma ação:\n");
        printf("[e] Ir para a esquerda\n");
        printf("[d] Ir para a direita\n");
        printf("[p] Ver pistas encontradas\n");
        printf("[s] Sair da exploração\n");
        printf(">> ");
        scanf(" %c", &opcao);

        if (opcao == 's') {
            printf("\nVocê decidiu parar a exploração. Até a próxima, detetive!\n");
            break;
        }
        else if (opcao == 'p') {
            printf("\n📜 Pistas coletadas até agora:\n");
            if (*arvorePistas == NULL)
                printf("(nenhuma pista encontrada ainda)\n");
            else
                exibirPistasEmOrdem(*arvorePistas);
        }
        else if (opcao == 'e') {
            if (atual->esquerda != NULL) {
                atual = atual->esquerda;

                // Adiciona uma pista automática dependendo da sala
                if (strcmp(atual->nome, "Biblioteca Misteriosa") == 0) {
                    printf("\nVocê encontrou uma pista: 'Diário Rasgado'\n");
                    *arvorePistas = inserirPista(*arvorePistas, "Diário Rasgado");
                } else if (strcmp(atual->nome, "Jardim Abandonado") == 0) {
                    printf("\nVocê encontrou uma pista: 'Chave Enferrujada'\n");
                    *arvorePistas = inserirPista(*arvorePistas, "Chave Enferrujada");
                }

            } else {
                printf("\nNão há caminho à esquerda. Fim deste lado!\n");
            }
        }
        else if (opcao == 'd') {
            if (atual->direita != NULL) {
                atual = atual->direita;

                // Adiciona uma pista automática dependendo da sala
                if (strcmp(atual->nome, "Cozinha Antiga") == 0) {
                    printf("\nVocê encontrou uma pista: 'Receita Queimada'\n");
                    *arvorePistas = inserirPista(*arvorePistas, "Receita Queimada");
                } else if (strcmp(atual->nome, "Porão Escuro") == 0) {
                    printf("\nVocê encontrou uma pista: 'Fotografia Antiga'\n");
                    *arvorePistas = inserirPista(*arvorePistas, "Fotografia Antiga");
                }

            } else {
                printf("\nNão há caminho à direita. Fim deste lado!\n");
            }
        }
        else {
            printf("\nOpção inválida! Tente novamente.\n");
        }

        // Fim do caminho (nó folha)
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("\nVocê chegou ao fim do caminho na sala: %s\n", atual->nome);
            break;
        }
    }
}

/*
Função principal: main
Descrição:
Cria a árvore de salas e inicia o sistema de exploração e pistas.
*/
int main() {
    // Criação das salas (reaproveitando o mapa do Nível Novato)
    Sala* hall = criarSala("Hall de Entrada");
    Sala* biblioteca = criarSala("Biblioteca Misteriosa");
    Sala* cozinha = criarSala("Cozinha Antiga");
    Sala* jardim = criarSala("Jardim Abandonado");
    Sala* porao = criarSala("Porão Escuro");

    // Montagem da árvore binária de salas
    hall->esquerda = biblioteca;
    hall->direita = cozinha;
    biblioteca->esquerda = jardim;
    biblioteca->direita = porao;

    // Ponteiro inicial da árvore de pistas
    Pista* arvorePistas = NULL;

    // Inicia a exploração da mansão
    explorarSalas(hall, &arvorePistas);

    // Exibe todas as pistas encontradas antes de encerrar
    printf("\n=== Pistas Finais Descobertas ===\n");
    if (arvorePistas == NULL)
        printf("(nenhuma pista encontrada)\n");
    else
        exibirPistasEmOrdem(arvorePistas);

    // Libera memória (boa prática)
    free(jardim);
    free(porao);
    free(biblioteca);
    free(cozinha);
    free(hall);

    // Aqui não fazemos a liberação da BST de pistas para simplificar o nível intermediário.
    // Em um nível mais avançado, faríamos uma função recursiva para liberar os nós.

    return 0;
}

