#ifndef AVLLEX_H
#define AVLLEX_H
#define MAX_INDICES 100

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
using namespace std;

struct NodeLEX {
    char key[50];  // Critério de ordenação (origem, destino, preço convertido para string)
    int indices[MAX_INDICES];  // Armazena os índices dos voos
    int numIndices;  // Quantidade de índices armazenados
    NodeLEX *leftChild;  // Ponteiro para o filho esquerdo
    NodeLEX *rightChild;  // Ponteiro para o filho direito
    int height;  // Altura do nó na árvore

    // Construtor do nó
    NodeLEX(const char* k, int idx) : leftChild(nullptr), rightChild(nullptr), height(1), numIndices(1) {
        strcpy(key, k);  // Copia a chave para o nó
        indices[0] = idx;  // Armazena o índice do voo
    }
};

struct AVLLEX {
    NodeLEX *root = nullptr;  // Raiz da árvore AVL

    // Função para obter a altura de um nó
    int getHeightLEX(NodeLEX *NodeLEX);

    // Função para obter o fator de balanceamento de um nó
    int getBalanceLEX(NodeLEX *NodeLEX);

    // Rotação à direita
    NodeLEX* rotateRightLEX(NodeLEX* y);

    // Rotação à esquerda
    NodeLEX* rotateLeftLEX(NodeLEX* x);

    // Função para inserir um nó na árvore AVL
    NodeLEX* insertLEX(NodeLEX* NodeLEX, const char* key, int idx);

    // Função para inserir uma nova chave na árvore AVL
    void insertLEX(const char* key, int idx);

    // Função para buscar uma chave na árvore AVL
    void searchLEX(const char* key, int* result, int& result_size);
    //Função para percorrer a árvore em ordem
    void inOrderLEX(NodeLEX* NodeLEX);
    //Função para imprimir a árvore em ordem
    void printInOrderLEX();
    //Retorna o máximo entre dois valores
    int LeoMax(const int &a, const int &b);
    // Destrutor da árvore AVL
    ~AVLLEX();
// Função auxiliar para liberar a memória dos nós
    void clear(NodeLEX* node);
};

#endif