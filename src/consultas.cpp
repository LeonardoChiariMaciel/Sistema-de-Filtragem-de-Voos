#include "consultas.h"

using namespace std;
// Função que verifica se um valor está presente em um array
bool contains(int* array, int size, int value) {
    for (int i = 0; i < size; ++i) {
        if (array[i] == value) {
            return true;
        }
    }
    return false;
}

// Função que analisa uma string de consulta e retorna uma estrutura Consulta
Consulta analisarConsulta(const string& consulta) {
    Consulta result;
    result.num_condicoes = 0;
    stringstream ss(consulta);
    ss >> result.limit >> result.ordem;
    string condicao;
    ss >> condicao;

    // Armazenar a condição original completa
    strcpy(result.condicoes_originais[result.num_condicoes], condicao.c_str());

    size_t start = condicao.find("(((") + 3;
    size_t end = condicao.find(")))");
    string condicoes_str = condicao.substr(start, end - start);

    // Remover todos os parênteses manualmente
    char condicoes_clean[condicoes_str.length() + 1];
    int j = 0;
    for (size_t i = 0; i < condicoes_str.length(); ++i) {
        if (condicoes_str[i] != '(' && condicoes_str[i] != ')') {
            condicoes_clean[j++] = condicoes_str[i];
        }
    }
    condicoes_clean[j] = '\0';

    // Separar as condições usando o delimitador '&'
    char* token = strtok(condicoes_clean, "&");
    while (token != nullptr) {
        strcpy(result.condicoes[result.num_condicoes++], token);
        token = strtok(nullptr, "&");
    }

    return result;
}


void processarCondicao(char condicoes[][50], int num_condicoes, AVL& avl_duracao, AVL& avl_assentos, AVL& avl_preco, AVLLEX& avl_origem, AVLLEX& avl_destino, AVL& avl_paradas, int* gabarito, int& gabarito_size, int TAM) {
    int temp_gabarito[TAM]; // Array temporário para armazenar resultados intermediários
    int temp_size = 0; // Tamanho do array temporário
    int intersecao[TAM]; // Array para armazenar a interseção dos resultados
    int intersecao_size = 0; // Tamanho do array de interseção

    // Iterar sobre todas as condições
    for (int i = 0; i < num_condicoes; ++i) {
        string condicao = condicoes[i]; // Obter a condição atual
        temp_size = 0; // Resetar o tamanho do array temporário

        // Verificar o tipo de condição e buscar os resultados correspondentes nas árvores AVL
        if (condicao.find("dur>=") != string::npos) {
            double duracao_val = stod(condicao.substr(condicao.find("dur>=") + 5));
            avl_duracao.search(duracao_val, temp_gabarito, temp_size, true); // true para >=
        } else if (condicao.find("dur<=") != string::npos) {
            double duracao_val = stod(condicao.substr(condicao.find("dur<=") + 5));
            avl_duracao.search(duracao_val, temp_gabarito, temp_size, false); // false para <=
        } else if (condicao.find("dur==") != string::npos) {
            double duracao_val = stod(condicao.substr(condicao.find("dur==") + 5));
            avl_duracao.search(duracao_val, temp_gabarito, temp_size, true); // true para ==
        } else if (condicao.find("sea>=") != string::npos) {
            int assentos_val = stoi(condicao.substr(condicao.find("sea>=") + 5));
            avl_assentos.search(assentos_val, temp_gabarito, temp_size, true); // true para >=
        } else if (condicao.find("sea<=") != string::npos) {
            int assentos_val = stoi(condicao.substr(condicao.find("sea<=") + 5));
            avl_assentos.search(assentos_val, temp_gabarito, temp_size, false); // false para <=
        } else if (condicao.find("sea==") != string::npos) {
            int assentos_val = stoi(condicao.substr(condicao.find("sea==") + 5));
            avl_assentos.search(assentos_val, temp_gabarito, temp_size, true); // true para ==
        } else if (condicao.find("prc>=") != string::npos) {
            double preco_val = stod(condicao.substr(condicao.find("prc>=") + 5));
            avl_preco.search(preco_val, temp_gabarito, temp_size, true); // true para >=
        } else if (condicao.find("prc<=") != string::npos) {
            double preco_val = stod(condicao.substr(condicao.find("prc<=") + 5));
            avl_preco.search(preco_val, temp_gabarito, temp_size, false); // false para <=
        } else if (condicao.find("prc==") != string::npos) {
            double preco_val = stod(condicao.substr(condicao.find("prc==") + 5));
            avl_preco.search(preco_val, temp_gabarito, temp_size, true); // true para ==
        } else if (condicao.find("org==") != string::npos) {
            string origem_val = condicao.substr(condicao.find("org==") + 5);
            avl_origem.searchLEX(origem_val.c_str(), temp_gabarito, temp_size);
        } else if (condicao.find("dst==") != string::npos) {
            string destino_val = condicao.substr(condicao.find("dst==") + 5);
            avl_destino.searchLEX(destino_val.c_str(), temp_gabarito, temp_size);
        } else if (condicao.find("sto>=") != string::npos) {
            int paradas_val = stoi(condicao.substr(condicao.find("sto>=") + 5));
            avl_paradas.search(paradas_val, temp_gabarito, temp_size, true); // true para >=
        } else if (condicao.find("sto<=") != string::npos) {
            int paradas_val = stoi(condicao.substr(condicao.find("sto<=") + 5));
            avl_paradas.search(paradas_val, temp_gabarito, temp_size, false); // false para <=
        } else if (condicao.find("sto==") != string::npos) {
            int paradas_val = stoi(condicao.substr(condicao.find("sto==") + 5));
            avl_paradas.search(paradas_val, temp_gabarito, temp_size, true); // true para ==
        }

        // Se for a primeira condição, inicializa a interseção com os resultados da primeira condição
        if (i == 0) {
            for (int j = 0; j < temp_size; ++j) {
                intersecao[intersecao_size++] = temp_gabarito[j];
            }
        } else {
            // Para as condições subsequentes, faz a interseção com os resultados anteriores
            int new_intersecao[TAM];
            int new_intersecao_size = 0;
            for (int j = 0; j < intersecao_size; ++j) {
                if (contains(temp_gabarito, temp_size, intersecao[j])) {
                    new_intersecao[new_intersecao_size++] = intersecao[j];
                }
            }
            intersecao_size = new_intersecao_size;
            for (int j = 0; j < intersecao_size; ++j) {
                intersecao[j] = new_intersecao[j];
            }
        }
    }

    // Copiar a interseção final para o vetor gabarito
    for (int i = 0; i < intersecao_size; ++i) {
        gabarito[gabarito_size++] = intersecao[i];
    }
}
