#include "minheap.h"
#include <iostream>
#include <cstring>
using namespace std;

// Construtor da classe MinHeap
MinHeap::MinHeap(int cap, const char* ordem) : capacity(cap), size(0) {
    heap = new voo_ptr[capacity]; // Aloca memória para o heap
    strcpy(this->ordem, ordem); // Copia a ordem para o atributo da classe
}

// Destrutor da classe MinHeap
MinHeap::~MinHeap() {
    delete[] heap; // Libera a memória alocada para o heap
}

// Função para trocar dois elementos no heap
void MinHeap::Leoswap(int i, int j) {
    voo_ptr temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

// Função para verificar se o heap está vazio
bool MinHeap::isEmpty() {
    return size == 0;
}

// Funções para obter o índice do pai, filho esquerdo e filho direito
int MinHeap::parent(int i) { return (i - 1) / 2; }
int MinHeap::leftChild(int i) { return (2 * i + 1); }
int MinHeap::rightChild(int i) { return (2 * i + 2); }

// Função para manter a propriedade do heap após a inserção
void MinHeap::heapify_up(int index) {
    while (index != 0 && compara(heap[index], heap[parent(index)])) {
        Leoswap(index, parent(index));
        index = parent(index);
    }
}

// Função para manter a propriedade do heap após a remoção
void MinHeap::heapify_down(int index) {
    int smallest = index;
    int left = leftChild(index);
    int right = rightChild(index);

    if (left < size && compara(heap[left], heap[smallest])) {
        smallest = left;
    }

    if (right < size && compara(heap[right], heap[smallest])) {
        smallest = right;
    }

    if (smallest != index) {
        Leoswap(index, smallest);
        heapify_down(smallest);
    }
}

// Função para redimensionar o heap quando a capacidade é atingida
void MinHeap::resizeHeap() {
    int newCapacity = capacity * 2;
    voo_ptr* newHeap = new voo_ptr[newCapacity];
    for (int i = 0; i < size; ++i) {
        newHeap[i] = heap[i];
    }
    delete[] heap;
    heap = newHeap;
    capacity = newCapacity;
}

// Função para inserir um novo elemento no heap
void MinHeap::insertM(voo_ptr voo) {
    if (size == capacity) {
        resizeHeap(); // Aumenta a capacidade do heap
    }
    heap[size] = voo;
    heapify_up(size);
    size++;
}

// Função para remover e retornar o menor elemento do heap
voo_ptr MinHeap::removeandreturnMin() {
    if (size <= 0) {
        cout << "Heap vazio. Não há elementos para remover.\n";
        return nullptr;
    }
    voo_ptr root = heap[0];
    heap[0] = heap[size - 1];
    size--;
    heapify_down(0);
    return root;
}

// Função para comparar dois elementos do heap de acordo com a ordem especificada
bool MinHeap::compara(const voo_ptr &v1, const voo_ptr &v2) {
    if (strcmp(ordem, "psd") == 0) return comparaPSD(v1, v2);
    if (strcmp(ordem, "pds") == 0) return comparaPDS(v1, v2);
    if (strcmp(ordem, "dps") == 0) return comparaDPS(v1, v2);
    if (strcmp(ordem, "dsp") == 0) return comparaDSP(v1, v2);
    if (strcmp(ordem, "spd") == 0) return comparaSPD(v1, v2);
    if (strcmp(ordem, "sdp") == 0) return comparaSDP(v1, v2);
    return false;
}

// Funções para comparar dois elementos do heap de acordo com diferentes critérios
//Caso 1: Preço-Paradas-Duração
bool MinHeap::comparaPSD(const voo_ptr &v1, const voo_ptr &v2) {
    if (v1->prc < v2->prc) return true;
    if (v1->prc > v2->prc) return false;
    if (v1->sto < v2->sto) return true;
    if (v1->sto > v2->sto) return false;
    if (v1->dur < v2->dur) return true;
    return false;
}
//Caso 2: Preço-Duração-Paradas
bool MinHeap::comparaPDS(const voo_ptr &v1, const voo_ptr &v2) {
    if (v1->prc < v2->prc) return true;
    if (v1->prc > v2->prc) return false;
    if (v1->dur < v2->dur) return true;
    if (v1->dur > v2->dur) return false;
    if (v1->sto < v2->sto) return true;
    return false;
}
//Caso 3: Duração-Preço-Paradas
bool MinHeap::comparaDPS(const voo_ptr &v1, const voo_ptr &v2) {
    if (v1->dur < v2->dur) return true;
    if (v1->dur > v2->dur) return false;
    if (v1->prc < v2->prc) return true;
    if (v1->prc > v2->prc) return false;
    if (v1->sto < v2->sto) return true;
    return false;
}
//Caso 4: Duração-Paradas-Preço
bool MinHeap::comparaDSP(const voo_ptr &v1, const voo_ptr &v2) {
    if (v1->dur < v2->dur) return true;
    if (v1->dur > v2->dur) return false;
    if (v1->sto < v2->sto) return true;
    if (v1->sto > v2->sto) return false;
    if (v1->prc < v2->prc) return true;
    return false;
}
//Caso 5: Paradas-Preço-Duração
bool MinHeap::comparaSPD(const voo_ptr &v1, const voo_ptr &v2) {
    if (v1->sto < v2->sto) return true;
    if (v1->sto > v2->sto) return false;
    if (v1->prc < v2->prc) return true;
    if (v1->prc > v2->prc) return false;
    if (v1->dur < v2->dur) return true;
    return false;
}
//Caso 6: Paradas-Duração-Preço
bool MinHeap::comparaSDP(const voo_ptr &v1, const voo_ptr &v2) {
    if (v1->sto < v2->sto) return true;
    if (v1->sto > v2->sto) return false;
    if (v1->dur < v2->dur) return true;
    if (v1->dur > v2->dur) return false;
    if (v1->prc < v2->prc) return true;
    return false;
}