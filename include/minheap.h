#ifndef MINHEAP_H
#define MINHEAP_H

#include "voo.h"

class MinHeap {
    voo_ptr* heap; //ponteiro para o array que armazena o heap
    int capacity;
    int size;
    char ordem[4]; //armazena as letras p, d e s na ordem desejada

    void heapify_down(int index); //ajusta o heap quando um paciente é retirado
    void heapify_up(int index); //ajusta o heap quando um paciente é inserido
    void Leoswap(int i, int j); //função de troca
    void resizeHeap(); // Função para aumentar a capacidade do heap
    int parent(int i); //encontra o indice do pai
    int leftChild(int i); //encontra o indice do filho esquerdo
    int rightChild(int i); //encontra o indice do filho direito
    bool comparaPSD(const voo_ptr &v1, const voo_ptr &v2); //para ordenações do tipo psd
    bool comparaPDS(const voo_ptr &v1, const voo_ptr &v2); //para ordenações do tipo pds
    bool comparaDPS(const voo_ptr &v1, const voo_ptr &v2); //para ordenações do tipo dps
    bool comparaDSP(const voo_ptr &v1, const voo_ptr &v2); //para ordenações do tipo dsp
    bool comparaSPD(const voo_ptr &v1, const voo_ptr &v2); //para ordenações do tipo spd
    bool comparaSDP(const voo_ptr &v1, const voo_ptr &v2); //para ordenações do tipo sdp
public:
    MinHeap(int cap, const char* ordem); //construtor
    ~MinHeap(); //destrutor
    void insertM(voo_ptr voo); //insere um elemento na árvore
    voo_ptr removeandreturnMin(); //remove um elemento da árvore
    bool isEmpty(); //checa se a árvore está vazia
    bool compara(const voo_ptr &v1, const voo_ptr &v2); //função compara utilizando o critério desejado
};

#endif