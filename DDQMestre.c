/*  
-------------------------------------------------------------
    Desafio Detective Quest - Estruturas de Dados e Investigação
    NÍVEL MESTRE
    Aluno: Aderlon Barbosa Pessoa
    Matéria: Estrutura de Dados
-------------------------------------------------------------
    Descrição:
    Neste nível final, o jogo Detective Quest ganha sua fase de dedução!
    Agora, além de explorar a mansão e coletar pistas, o jogador pode
    descobrir quais suspeitos estão relacionados a cada pista.

    Através de uma TABELA HASH, cada pista armazenada na árvore BST
    é associada a um suspeito. No final, o programa mostra:
      - Todas as associações pista → suspeito;
      - O suspeito mais citado (possível culpado).

    O objetivo é aplicar os conceitos de Hashing e integração de 
    múltiplas estruturas de dados (Árvore + Tabela Hash).
-------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ======= ESTRUTURA DE SALAS (mantida do nível Novato) =======
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// ======= ESTRUTURA DE PISTAS (mantida do nível Aventureiro) =======
typedef struct Pista {
    char nome[50];
    struct Pista *esquerda;
    struct Pista *direita;
} Pista;

// ======= ESTRUTURA DE TABELA HASH (nova neste nível) =======
typedef struct NodoHash {
    char pista[50];           // Nome da pista
    char suspeito[50];        // Suspeito relacionado à pista
    struct NodoHash* prox;    // Ponteiro para encadeamento (em caso de colisão)
} NodoHash;

#define TAM_TABELA 10   // Tamanho fixo da tabela hash (poderia ser maior em projetos reais)

/*
Função: funcaoHash
Descrição:
Calcula o índice de armazenamento com base na soma dos caracteres do nome da pista.
*/
int funcaoHash(char* chave) {
    int soma = 0;
    for (int i = 0; i < strlen(chave); i++) {
        soma += chave[i];
    }
    return soma % TAM_TABELA;  // Retorna o índice dentro do limite da tabela
}

/*
Função: inserirNaHash
Descrição:
Insere um par pista → suspeito na tabela hash. 
Usa encadeamento caso o índice já esteja ocupado.
*/
void inserirNaHash(NodoHash* tabela[], char* pista, char* suspeito) {
    int indice = funcaoHash(pista);

    NodoHash* novo = (NodoHash*) malloc(sizeof(NodoHash));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);
    novo->prox = NULL;

    // Caso o índice esteja vazio
    if (tabela[indice] == NULL) {
        tabela[indice] = novo;
    } 
    // Caso já exista algo no índice (colisão)
    else {
        NodoHash* atual = tabela[indice];
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo;
    }
}

/*
Função: exibirHash
Descrição:
Percorre a tabela hash e mostra todas as associações pista → suspeito.
*/
void exibirHash(NodoHash* tabela[]) {
    printf("\n=== Relações de Pistas e Suspeitos ===\n");
    for (int i = 0; i < TAM_TABELA; i++) {
        NodoHash* atual = tabela[i];
        while (atual != NULL) {
            printf("Pista: %-20s | Suspeito: %s\n", atual->pista, atual->suspeito);
            atual = atual->prox;
        }
    }
}

/*
Função: contarSuspeitos
Descrição:
Percorre toda a tabela hash e conta quantas vezes cada suspeito aparece.
Em seguida, mostra o suspeito mais citado.
*/
void contarSuspeitos(NodoHash* tabela[]) {
    char nomes[20][50];   // Vetor de nomes de suspeitos
    int contagens[20];    // Quantidade de vezes que aparecem
    int total = 0;

    // Inicializa contadores
    for (int i = 0; i < 20; i++) {
        contagens[i] = 0;
        strcpy(nomes[i], "");
    }

    // Percorre toda a tabela hash
    for (int i = 0; i < TAM_TABELA; i++) {
        NodoHash* atual = tabela[i];
        while (atual != NULL) {
            int encontrado = 0;
            // Verifica se o suspeito já está na lista
            for (int j = 0; j < total; j++) {
                if (strcmp(nomes[j], atual->suspeito) == 0) {
                    contagens[j]++;
                    encontrado = 1;
                    break;
                }
            }
            // Se for um suspeito novo
            if (!encontrado) {
                strcpy(nomes[total], atual->suspeito);
                contagens[total] = 1;
                total++;
            }
            atual = atual->prox;
        }
    }

    // Descobre o mais citado
    int max = 0;
    char suspeitoMaisCitado[50] = "";
    for (int i = 0; i < total; i++) {
        if (contagens[i] > max) {
            max = contagens[i];
            strcpy(suspeitoMaisCitado, nomes[i]);
        }
    }

    if (total > 0) {
        printf("\n🔎 Suspeito mais citado nas pistas: %s (%d menções)\n", suspeitoMaisCitado, max);
    } else {
        printf("\nNenhum suspeito foi encontrado nas pistas.\n");
    }
}

/*
Função: criarSala
Descrição:
Cria uma nova sala dinamicamente (igual aos níveis anteriores).
*/
Sala* criarSala(char nome[]) {
    Sala* nova = (Sala*) malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

/*
Função: criarPista
Descrição:
Cria uma nova pista (nó da árvore BST).
*/
Pista* criarPista(char nome[]) {
    Pista* nova = (Pista*) malloc(sizeof(Pista));
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

/*
Função: inserirPista
Descrição:
Insere uma pista na árvore BST de forma ordenada.
*/
Pista* inserirPista(Pista* raiz, char nome[]) {
    if (raiz == NULL) {
        return criarPista(nome);
    }
    int cmp = strcmp(nome, raiz->nome);
    if (cmp < 0)
        raiz->esquerda = inserirPista(raiz->esquerda, nome);
    else if (cmp > 0)
        raiz->direita = inserirPista(raiz->direita, nome);
    return raiz;
}

/*
Função: explorarSalas
Descrição:
Permite explorar a mansão e associar pistas a suspeitos automaticamente.
Cada pista encontrada será armazenada na BST e também registrada na hash.
*/
void explorarSalas(Sala* atual, Pista** arvorePistas, NodoHash* tabela[]) {
    char opcao;

    while (1) {
        printf("\nVocê está em: %s\n", atual->nome);
        printf("[e] Ir para a esquerda\n");
        printf("[d] Ir para a direita\n");
        printf("[p] Ver relações pista → suspeito\n");
        printf("[s] Sair da exploração\n");
        printf(">> ");
        scanf(" %c", &opcao);

        if (opcao == 's') {
            printf("\nVocê decidiu parar a exploração. Até a próxima, detetive!\n");
            break;
        }
        else if (opcao == 'p') {
            exibirHash(tabela);
        }
        else if (opcao == 'e') {
            if (atual->esquerda != NULL) {
                atual = atual->esquerda;

                // Pistas automáticas e associações
                if (strcmp(atual->nome, "Biblioteca Misteriosa") == 0) {
                    printf("\nVocê encontrou uma pista: 'Diário Rasgado'\n");
                    *arvorePistas = inserirPista(*arvorePistas, "Diário Rasgado");
                    inserirNaHash(tabela, "Diário Rasgado", "Sr. Blackwood");
                } else if (strcmp(atual->nome, "Jardim Abandonado") == 0) {
                    printf("\nVocê encontrou uma pista: 'Chave Enferrujada'\n");
                    *arvorePistas = inserirPista(*arvorePistas, "Chave Enferrujada");
                    inserirNaHash(tabela, "Chave Enferrujada", "Sra. Violet");
                }

            } else {
                printf("\nNão há caminho à esquerda.\n");
            }
        }
        else if (opcao == 'd') {
            if (atual->direita != NULL) {
                atual = atual->direita;

