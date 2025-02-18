#ifndef VOO_H
#define VOO_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
using namespace std;

typedef struct Voo{
    string org; //local de partida
    string dst; //local de destino
    double prc; //preco do voo
    int sea; //números de assentos disponíveis
    string dep; //data de partida
    string arr; //data de chegada
    int sto; //número de paradas
    double dur; //duração do vôo
}voo_t, *voo_ptr;

int getTAM(char *arquivo); //retorna a quantidade de voos no arquivo
int carregaVoos(voo_ptr voos, int TAM, char *arquivo); //carrega os voos do arquivo para o vetor de voos e retorna a quantidade de consultas
void carregaConsultas(string* consultas, int TAM, int num_consultas, const char* arquivo); //carrega as consultas do arquivo para o vetor de consultas
void duracaoVoos(voo_ptr voos, int TAM); //Recebe a lista de voos, o tamanho da lista, a data de chegada e de saída daquele voo e calcula o tempo de duração do voo em segundos

#endif