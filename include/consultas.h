#ifndef CONSULTAS_H
#define CONSULTAS_H

#include "voo.h"
#include "avllex.h"
#include "avl.h"
#include "minheap.h"

using namespace std;

struct Consulta {
    int limit; //limite de resultados
    char ordem[4]; //ordem dos resultados
    char condicoes[10][50]; //condições da consulta
    char condicoes_originais[10][50]; //condições originais da consulta
    int num_condicoes; //número de condições
};
//Função que verifica se um valor está presente em um array
bool contains(int* array, int size, int value);
//Função que analisa uma string de consulta e retorna uma struct de consulta
Consulta analisarConsulta(const string& consulta);
//Função que processa as condições da consulta e atualiza o gabarito com os resultados
void processarCondicao(char condicoes[][50], int num_condicoes, AVL& avl_duracao, AVL& avl_assentos, AVL& avl_preco, AVLLEX& avl_origem, AVLLEX& avl_destino, AVL& avl_paradas, int* gabarito, int& gabarito_size, int TAM);

#endif