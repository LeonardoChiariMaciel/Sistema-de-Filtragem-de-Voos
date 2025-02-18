#include "avllex.h"

// Função para obter a altura de um nó
int AVLLEX::getHeightLEX(NodeLEX *NodeLEX) {
    return NodeLEX ? NodeLEX->height : 0;
}

// Função para obter o fator de balanceamento de um nó
int AVLLEX::getBalanceLEX(NodeLEX *NodeLEX) {
    return NodeLEX ? getHeightLEX(NodeLEX->leftChild) - getHeightLEX(NodeLEX->rightChild) : 0;
}

// Rotação à direita
NodeLEX* AVLLEX::rotateRightLEX(NodeLEX* y) {
    NodeLEX* x = y->leftChild;  // x é o filho esquerdo de y
    NodeLEX* T2 = x->rightChild;  // T2 é o filho direito de x

    // Realiza a rotação
    x->rightChild = y;
    y->leftChild = T2;

    // Atualiza as alturas
    y->height = LeoMax(getHeightLEX(y->leftChild), getHeightLEX(y->rightChild)) + 1;
    x->height = LeoMax(getHeightLEX(x->leftChild), getHeightLEX(x->rightChild)) + 1;

    // Retorna a nova raiz
    return x;
}

// Rotação à esquerda
NodeLEX* AVLLEX::rotateLeftLEX(NodeLEX* x) {
    NodeLEX* y = x->rightChild;  // y é o filho direito de x
    NodeLEX* T2 = y->leftChild;  // T2 é o filho esquerdo de y

    // Realiza a rotação
    y->leftChild = x;
    x->rightChild = T2;

    // Atualiza as alturas
    x->height = LeoMax(getHeightLEX(x->leftChild), getHeightLEX(x->rightChild)) + 1;
    y->height = LeoMax(getHeightLEX(y->leftChild), getHeightLEX(y->rightChild)) + 1;

    // Retorna a nova raiz
    return y;
}

// Função para inserir um nó na árvore AVLLEX
NodeLEX* AVLLEX::insertLEX(NodeLEX* NodeLEX, const char* key, int idx) {
    // Passo 1: Realiza a inserção normal em uma árvore binária de busca
    if (NodeLEX == nullptr)
        return new struct NodeLEX(key, idx);
    // Se a chave for menor que a chave do nó, insere na subárvore esquerda
    if (strcmp(key, NodeLEX->key) < 0)
        NodeLEX->leftChild = insertLEX(NodeLEX->leftChild, key, idx);
    // Se a chave for maior que a chave do nó, insere na subárvore direita
    else if (strcmp(key, NodeLEX->key) > 0)
        NodeLEX->rightChild = insertLEX(NodeLEX->rightChild, key, idx);
    else {
        // Chave duplicada, adiciona o índice ao nó existente
        NodeLEX->indices[NodeLEX->numIndices++] = idx;
        return NodeLEX;
    }

    // Passo 2: Atualiza a altura do nó ancestral
    NodeLEX->height = 1 + LeoMax(getHeightLEX(NodeLEX->leftChild), getHeightLEX(NodeLEX->rightChild));

    // Passo 3: Obtém o fator de balanceamento do nó ancestral para verificar se ele ficou desbalanceado
    int balance = getBalanceLEX(NodeLEX);

    // Se o nó ficou desbalanceado, existem 4 casos

    // Caso 1: Rotação à direita
    if (balance > 1 && strcmp(key, NodeLEX->leftChild->key) < 0)
        return rotateRightLEX(NodeLEX);

    // Caso 2: Rotação à esquerda
    if (balance < -1 && strcmp(key, NodeLEX->rightChild->key) > 0)
        return rotateLeftLEX(NodeLEX);

    // Caso 3: Rotação à esquerda-direita
    if (balance > 1 && strcmp(key, NodeLEX->leftChild->key) > 0) {
        NodeLEX->leftChild = rotateLeftLEX(NodeLEX->leftChild);
        return rotateRightLEX(NodeLEX);
    }

    // Caso 4: Rotação à direita-esquerda
    if (balance < -1 && strcmp(key, NodeLEX->rightChild->key) < 0) {
        NodeLEX->rightChild = rotateRightLEX(NodeLEX->rightChild);
        return rotateLeftLEX(NodeLEX);
    }

    // Retorna o ponteiro do nó (inalterado)
    return NodeLEX;
}

// Função para inserir uma nova chave na árvore AVLLEX
void AVLLEX::insertLEX(const char* key, int idx) {
    // Insere a chave na árvore AVLLEX
    root = insertLEX(root, key, idx);
}

// Função para buscar uma chave na árvore AVLLEX
void AVLLEX::searchLEX(const char* key, int* result, int& result_size) {
    // Inicializa o vetor de resultados
    NodeLEX* current = root;
    while (current != nullptr) {
        // Compara a chave com a chave do nó atual
        int cmp = strcmp(key, current->key);
        if (cmp == 0) {
            // Chave encontrada, copia os índices para o vetor de resultados
            for (int i = 0; i < current->numIndices; ++i) {
                result[result_size++] = current->indices[i];
            }
            return;
        } else if (cmp < 0) {
            // Se a chave for menor, desce para a subárvore esquerda
            current = current->leftChild;
        } else {
            //se não, desce para a da direita
            current = current->rightChild;
        }
    }
}

// Função para percorrer a árvore em ordem
void AVLLEX::inOrderLEX(NodeLEX* NodeLEX) {
    if (NodeLEX) {
        // Percorre a subárvore esquerda
        inOrderLEX(NodeLEX->leftChild);
        cout << NodeLEX->key << ": ";
        for (int i = 0; i < NodeLEX->numIndices; i++) {
            // Imprime os índices dos voos
            cout << NodeLEX->indices[i] << " ";
        }
        cout << endl;
        // Percorre a subárvore direita
        inOrderLEX(NodeLEX->rightChild);
    }
}

// Função para imprimir a árvore em ordem
void AVLLEX::printInOrderLEX() {
    // Percorre a árvore em ordem
    inOrderLEX(root);
}

int AVLLEX::LeoMax(const int &a, const int &b){
    //reimplementação da função max
    return a > b ? a : b;
}

// Destrutor da árvore AVL
AVLLEX::~AVLLEX() {
    clear(root);
}

// Função auxiliar para liberar a memória dos nós
void AVLLEX::clear(NodeLEX* node) {
    if (node) {
        clear(node->leftChild);
        clear(node->rightChild);
        delete node;
    }
}