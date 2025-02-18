#ifndef AVL_H
#define AVL_H
#define MAX_INDICES 100

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
using namespace std;


struct Node {
    double key;  // Critério de ordenação (valor numérico)
    int indices[MAX_INDICES];  // Armazena os índices dos voos
    int numIndices;  // Quantidade de índices armazenados
    Node *leftChild;  // Ponteiro para o filho esquerdo
    Node *rightChild;  // Ponteiro para o filho direito
    int height;  // Altura do nó na árvore

    // Construtor do nó
    Node(double k, int idx);
};

struct AVL {
    Node *root = nullptr;  // Raiz da árvore AVL

    // Função para obter a altura de um nó
    int getHeight(Node *node);

    // Função para obter o fator de balanceamento de um nó
    int getBalance(Node *node);

    // Rotação à direita
    Node* rotateRight(Node* y);

    // Rotação à esquerda
    Node* rotateLeft(Node* x);

    // Função para inserir um nó na árvore AVL
    Node* insert(Node* node, double key, int idx);

    // Função para inserir uma nova chave na árvore AVL
    void insert(double key, int idx);
    // Função para percorrer a árvore em ordem
    void inOrder(Node* node);
    //Função pra imprimir em ordem
    void printInOrder();
    // Função para buscar um nó na árvore AVL
    void search(Node* node, double key, int* gabarito, int& gabarito_size, bool greater_equal);
    // Função para buscar um nó na árvore AVL
    void search(double key, int* gabarito, int& gabarito_size, bool greater_equal);
    //Retorna o Máximo entre dois valores
    int LeoMax(const int &__a, const int &__b);
    // Destrutor da árvore AVL
    ~AVL();
    // Função auxiliar para liberar a memória dos nós
    void clear(Node* node);
};


#endif
