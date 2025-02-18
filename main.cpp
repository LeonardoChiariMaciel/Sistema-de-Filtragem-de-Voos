#include "voo.h"
#include "avllex.h"
#include "avl.h"
#include "minheap.h"
#include "consultas.h"

using namespace std;

int main(int argc, char* argv[]){
    //Trata erros na passagem do arquivo
    if (argc < 2) {
        std::cout << "ERRO: NOME DO ARQUIVO NAO FORNECIDO" << std::endl;
        return 1;
    }
    //lê o arquivo, abre e trata possível problema na abertura do mesmo
    char* nomeArquivo = argv[1];
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cout << "ERRO: NAO FOI POSSIVEL ABRIR O ARQUIVO" << std::endl;
        return 1;
    }
    int TAM = getTAM(nomeArquivo); //número de voos
    voo_ptr voos = new voo_t[TAM]; //vetor de voos
    int num_consultas;
    num_consultas = carregaVoos(voos, TAM, nomeArquivo); //carrega os voos e retorna o número de consultas
    string consultas[num_consultas]; //vetor de consultas
    carregaConsultas(consultas, TAM, num_consultas, nomeArquivo); //carrega as consultas
    duracaoVoos(voos, TAM); //calcula a duração dos voos

    string consultas_print[num_consultas]; //deixa armazenadas as consultas para futura impressão
    carregaConsultas(consultas_print, TAM, num_consultas, nomeArquivo); //carrega novamente as consultas para impressão
    
    //Repete para cada consulta o seguinte procedimento:
    for (int i = 0; i < num_consultas; i++) {
        //Chama a função de analisar consultas para a i-ésima consulta
        Consulta consulta = analisarConsulta(consultas[i]);
        cout << consultas_print[i] << endl; //pré-impressão da consulta
        
        //declara e preenche a AVL do tipo lexicográfica para origem
        AVLLEX avl_origem; 
        for (int i = 0; i < TAM; ++i) {
            avl_origem.insertLEX(voos[i].org.c_str(), i);
        }
        //declara e preenche a AVL do tipo lexicográfica para destino
        AVLLEX avl_destino;
        for (int i = 0; i < TAM; ++i) {
            avl_destino.insertLEX(voos[i].dst.c_str(), i);
        }
        //declara e preenche a AVL de preços
        AVL avl_preco;
        for (int i = 0; i < TAM; ++i) {
            avl_preco.insert(voos[i].prc, i);
        }
        //declara e preenche a AVL de assentos
        AVL avl_assentos;
        for (int i = 0; i < TAM; ++i) {
            avl_assentos.insert(voos[i].sea, i);
        }
        //declara e preenche a AVL de paradas
        AVL avl_paradas;
        for (int i = 0; i < TAM; ++i) {
            avl_paradas.insert(voos[i].sto, i);
        }
        //declara e preenche a AVL de duração
        AVL avl_duracao;
        for (int i = 0; i < TAM; ++i) {
            avl_duracao.insert(voos[i].dur, i);
        }

        // Processar a condição e preencher o vetor gabarito
        int gabarito[TAM];
        int gabarito_size = 0;
        processarCondicao(consulta.condicoes, consulta.num_condicoes, avl_duracao, avl_assentos, avl_preco, avl_origem, avl_destino, avl_paradas, gabarito, gabarito_size, TAM);

        // Inserir os voos no MinHeap
        MinHeap minHeap(gabarito_size, consulta.ordem); 
        for (int j = 0; j < gabarito_size; ++j) {
            minHeap.insertM(&voos[gabarito[j]]);
        }

        // Imprimir os voos ordenados conforme o limite
        for (int j = 0; j < consulta.limit && !minHeap.isEmpty(); ++j) {
            voo_ptr voo = minHeap.removeandreturnMin();
            cout << voo->org << " " << voo->dst << " " << voo->prc << " " << voo->sea
                 << " " << voo->dep << " " << voo->arr << " " << voo->sto << endl;
        }
    }

    delete[] voos;

    return 0;
}