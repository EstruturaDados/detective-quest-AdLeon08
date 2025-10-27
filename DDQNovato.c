/*  
-------------------------------------------------------------
    Desafio Detective Quest - Estruturas de Dados e Investigação
    NÍVEL NOVATO
    Aluno: Aderlon Barbosa Pessoa
    Matéria: Estrutura de Dados
-------------------------------------------------------------
    Descrição:
    Neste nível inicial, o objetivo é criar a base do jogo Detective Quest.
    Aqui, vamos montar uma Árvore Binária simples que representa os cômodos
    de uma mansão misteriosa. Cada nó da árvore é uma sala, e o jogador pode
    navegar entre os cômodos escolhendo seguir para a esquerda ou direita.

    O jogador começa no "Hall de Entrada" e pode explorar até chegar
    a um nó-folha, onde o caminho termina. Esse exercício serve para
    compreender o conceito de árvores binárias e percursos interativos.
-------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>

// Estrutura de dados que representa cada sala da mansão
typedef struct Sala {
    char nome[50];               // Nome do cômodo (por exemplo: "Biblioteca", "Cozinha")
    struct Sala *esquerda;       // Ponteiro para a sala à esquerda
    struct Sala *direita;        // Ponteiro para a sala à direita
} Sala;

/* 
Função: criarSala
Descrição: 
Cria dinamicamente uma nova sala na memória e define o nome dela.
Essa função ajuda a construir os nós da árvore binária.
*/
Sala* criarSala(char nome[]) {
    Sala* nova = (Sala*) malloc(sizeof(Sala)); // Aloca memória para uma nova sala
    if (nova == NULL) {
        printf("Erro ao alocar memória para a sala!\n");
        exit(1); // Encerra o programa se a memória não pôde ser alocada
    }

    // Copia o nome da sala para o campo 'nome' da estrutura
    strcpy(nova->nome, nome);
    nova->esquerda = NULL; // Inicialmente, a sala não tem conexão à esquerda
    nova->direita = NULL;  // Nem à direita
    return nova;           // Retorna o ponteiro da sala recém-criada
}

/*
Função: explorarSalas
Descrição:
Permite que o jogador explore a mansão interativamente.
Cada sala oferece ao jogador a escolha de ir para a esquerda, direita ou sair.
A exploração termina quando o jogador encontra uma sala sem caminhos (folha)
ou escolhe sair manualmente.
*/
void explorarSalas(Sala* atual) {
    char opcao;

    while (1) {
        printf("\nVocê está em: %s\n", atual->nome);
        printf("Escolha um caminho:\n");
        printf("[e] Ir para a esquerda\n");
        printf("[d] Ir para a direita\n");
        printf("[s] Sair da exploração\n");
        printf(">> ");
        scanf(" %c", &opcao); // O espaço antes de %c evita problemas com o buffer

        if (opcao == 's') {
            printf("\nVocê decidiu parar a exploração. Até a próxima, detetive!\n");
            break;
        }
        else if (opcao == 'e') {
            if (atual->esquerda != NULL) {
                atual = atual->esquerda; // Move para o caminho à esquerda
            } else {
                printf("\nNão há caminho à esquerda. Você chegou ao fim deste lado!\n");
            }
        }
        else if (opcao == 'd') {
            if (atual->direita != NULL) {
                atual = atual->direita; // Move para o caminho à direita
            } else {
                printf("\nNão há caminho à direita. Você chegou ao fim deste lado!\n");
            }
        }
        else {
            printf("\nOpção inválida! Tente novamente.\n");
        }

        // Se o jogador chegou a uma sala sem caminhos, a exploração termina
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("\nVocê chegou ao fim do caminho na sala: %s\n", atual->nome);
            printf("Mistério encerrado por aqui...\n");
            break;
        }
    }
}

/*
Função principal: main
Descrição:
Cria manualmente a estrutura da árvore binária com as salas da mansão.
Em seguida, inicia a exploração chamando a função explorarSalas().
*/
int main() {
    // Criação das salas (nós da árvore binária)
    Sala* hall = criarSala("Hall de Entrada");
    Sala* biblioteca = criarSala("Biblioteca Misteriosa");
    Sala* cozinha = criarSala("Cozinha Antiga");
    Sala* jardim = criarSala("Jardim Abandonado");
    Sala* porao = criarSala("Porão Escuro");

    // Conectando os cômodos (montando a árvore)
    hall->esquerda = biblioteca;  // Caminho à esquerda leva à biblioteca
    hall->direita = cozinha;      // Caminho à direita leva à cozinha
    biblioteca->esquerda = jardim; // Da biblioteca, à esquerda, há o jardim
    biblioteca->direita = porao;   // Da biblioteca, à direita, o porão

    // Inicia a exploração a partir do Hall de Entrada
    explorarSalas(hall);

    // Libera memória ao final (boa prática!)
    free(jardim);
    free(porao);
    free(biblioteca);
    free(cozinha);
    free(hall);

    return 0;
}

