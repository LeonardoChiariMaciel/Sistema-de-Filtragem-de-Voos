#include "avl.h"

// Construtor do nó
Node::Node(double k, int idx) : key(k), leftChild(nullptr), rightChild(nullptr), height(1), numIndices(1) {
    indices[0] = idx;  // Armazena o índice do voo
}

// Função para obter a altura de um nó
int AVL::getHeight(Node *node) {
    return node ? node->height : 0;
}

// Função para obter o fator de balanceamento de um nó
int AVL::getBalance(Node *node) {
    return node ? getHeight(node->leftChild) - getHeight(node->rightChild) : 0;
}

// Rotação à direita
Node* AVL::rotateRight(Node* y) {
    Node* x = y->leftChild;  // x é o filho esquerdo de y
    Node* T2 = x->rightChild;  // T2 é o filho direito de x

    // Realiza a rotação
    x->rightChild = y;
    y->leftChild = T2;

    // Atualiza as alturas
    y->height = LeoMax(getHeight(y->leftChild), getHeight(y->rightChild)) + 1;
    x->height = LeoMax(getHeight(x->leftChild), getHeight(x->rightChild)) + 1;

    // Retorna a nova raiz
    return x;
}

// Rotação à esquerda
Node* AVL::rotateLeft(Node* x) {
    Node* y = x->rightChild;  // y é o filho direito de x
    Node* T2 = y->leftChild;  // T2 é o filho esquerdo de y

    // Realiza a rotação
    y->leftChild = x;
    x->rightChild = T2;

    // Atualiza as alturas
    x->height = LeoMax(getHeight(x->leftChild), getHeight(x->rightChild)) + 1;
    y->height = LeoMax(getHeight(y->leftChild), getHeight(y->rightChild)) + 1;

    // Retorna a nova raiz
    return y;
}

// Função para inserir um nó na árvore AVL
Node* AVL::insert(Node* node, double key, int idx) {
    // Passo 1: Realiza a inserção normal em uma árvore binária de busca
    if (node == nullptr)
        return new Node(key, idx);

    if (key < node->key)
        node->leftChild = insert(node->leftChild, key, idx);
    else if (key > node->key)
        node->rightChild = insert(node->rightChild, key, idx);
    else {
        // Chave duplicada, adiciona o índice ao nó existente
        node->indices[node->numIndices++] = idx;
        return node;
    }

    // Passo 2: Atualiza a altura do nó ancestral
    node->height = 1 + LeoMax(getHeight(node->leftChild), getHeight(node->rightChild));

    // Passo 3: Obtém o fator de balanceamento do nó ancestral para verificar se ele ficou desbalanceado
    int balance = getBalance(node);

    // Se o nó ficou desbalanceado, existem 4 casos

    // Caso 1: Rotação à direita
    if (balance > 1 && key < node->leftChild->key)
        return rotateRight(node);

    // Caso 2: Rotação à esquerda
    if (balance < -1 && key > node->rightChild->key)
        return rotateLeft(node);

    // Caso 3: Rotação à esquerda-direita
    if (balance > 1 && key > node->leftChild->key) {
        node->leftChild = rotateLeft(node->leftChild);
        return rotateRight(node);
    }

    // Caso 4: Rotação à direita-esquerda
    if (balance < -1 && key < node->rightChild->key) {
        node->rightChild = rotateRight(node->rightChild);
        return rotateLeft(node);
    }

    // Retorna o ponteiro do nó (inalterado)
    return node;
}

// Função para inserir uma nova chave na árvore AVL
void AVL::insert(double key, int idx) {
    root = insert(root, key, idx);
}

// Função para percorrer a árvore em ordem
void AVL::inOrder(Node* node) {
    if (node) {
        // Percorre a subárvore esquerda
        inOrder(node->leftChild);
        cout << node->key << ": ";
        for (int i = 0; i < node->numIndices; i++) {
            // Imprime os índices dos voos
            cout << node->indices[i] << " ";
        }
        cout << endl;
        // Percorre a subárvore direita
        inOrder(node->rightChild);
    }
}

// Função para imprimir a árvore em ordem
void AVL::printInOrder() {
    inOrder(root);
}

// Função para buscar nós na árvore AVL
void AVL::search(Node* node, double key, int* gabarito, int& gabarito_size, bool greater_equal) {
    if (!node) return;
    // Se a chave do nó for maior ou igual à chave de busca
    if (greater_equal) {
        // Se a chave do nó for maior ou igual à chave de busca, percorre a subárvore esquerda
        if (node->key >= key) {
            for (int i = 0; i < node->numIndices; ++i) {
                // Armazena os índices dos voos
                gabarito[gabarito_size++] = node->indices[i];
            }
            // Continua a busca na subárvore esquerda
            search(node->leftChild, key, gabarito, gabarito_size, greater_equal);
        }
        // Se a chave do nó for menor que a chave de busca, percorre a subárvore direita
        search(node->rightChild, key, gabarito, gabarito_size, greater_equal);
    } else {
        // Se a chave do nó for menor ou igual à chave de busca, percorre a subárvore direita
        if (node->key <= key) {
            // Armazena os índices dos voos
            for (int i = 0; i < node->numIndices; ++i) {
                gabarito[gabarito_size++] = node->indices[i];
            }
            // Continua a busca na subárvore direita
            search(node->rightChild, key, gabarito, gabarito_size, greater_equal);
        }
        // Se a chave do nó for maior que a chave de busca, percorre a subárvore esquerda
        search(node->leftChild, key, gabarito, gabarito_size, greater_equal);
    }
}

void AVL::search(double key, int* gabarito, int& gabarito_size, bool greater_equal) {
    // Inicia a busca a partir da raiz
    search(root, key, gabarito, gabarito_size, greater_equal);
}

int AVL::LeoMax(const int &a, const int &b){
    //reimplementação da função max
    return a > b ? a : b;
}
// Destrutor da árvore AVL
AVL::~AVL() {
    clear(root);
}

// Função auxiliar para liberar a memória dos nós
void AVL::clear(Node* node) {
    if (node) {
        clear(node->leftChild);
        clear(node->rightChild);
        delete node;
    }
}