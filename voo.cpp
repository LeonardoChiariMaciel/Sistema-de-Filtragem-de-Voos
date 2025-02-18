#include "voo.h"
int getTAM(char *arquivo){
    ifstream file(arquivo); // Abra o arquivo de texto
    if (!file) {
        cerr << "Erro ao abrir o arquivo" << endl;
        return -1;
    }

    // Redireciona a entrada padrão para o arquivo
    cin.rdbuf(file.rdbuf());
    int TAM; //declara TAM
    cin >> TAM; //Atribui a TAM o número de voos
    file.close(); // Feche o arquivo
    return TAM; //Retorna o tamanho
}

int carregaVoos(voo_ptr voos, int TAM, char *arquivo){
    ifstream file(arquivo); // Abra o arquivo de texto

    // Redireciona a entrada padrão para o arquivo
    cin.rdbuf(file.rdbuf());
    int lixo; //variável para guardar lixo
    cin>>lixo; //pula a informação de tamanho armazenando ela no lixo
    for (int i = 0; i < TAM; ++i) {
        //preenche o vetor de voos
        cin >> voos[i].org >> voos[i].dst >> voos[i].prc >> voos[i].sea
            >> voos[i].dep >> voos[i].arr >> voos[i].sto;
    }
    int num_consultas; 
    cin >> num_consultas; //lê o número de consultas
    file.close(); // Feche o arquivo
    return num_consultas; //retorna o número de consultas
}

void carregaConsultas(string* consultas, int TAM, int num_consultas, const char* arquivo) {
    //essa função pula tudo anterior às consultas no arquivo
    ifstream file(arquivo);
    cin.rdbuf(file.rdbuf());
    string linha;
    getline(file, linha);
    for (int i = 0; i < TAM; ++i) {
        getline(file, linha);
    }
    getline(file, linha);
    for (int i = 0; i < num_consultas; ++i) {
        //armazena as consultas num vetor de strings
        getline(file, consultas[i]);
    }
}

void duracaoVoos(voo_ptr voos, int TAM) {
    for(int i = 0; i < TAM; i++){
        //pega a informação de data não tratada da saída e da chegada dos voos 
        string dep = voos[i].dep;
        string arr = voos[i].arr;
        //extrai apenas a parte da hora e dos minutos de saída e chegada da string
        int dia_inicio = stoi(dep.substr(8, 2));
        int dia_fim = stoi(arr.substr(8, 2));
        int h_dep = stoi(dep.substr(11, 2));
        int m_dep = stoi(dep.substr(14, 2));
        int h_arr = stoi(arr.substr(11, 2));
        int m_arr = stoi(arr.substr(14, 2));
        //converte a duração total de HH, MM para segundos
        int dur = (h_arr - h_dep) * 3600 + (m_arr - m_dep) * 60;
        //Adiciona 24h no caso em que a chegada e a saída aconteceram em dias diferentes
        if(dia_fim != dia_inicio){
            dur += 24 * 3600;
        }
        voos[i].dur = dur;
    }
}