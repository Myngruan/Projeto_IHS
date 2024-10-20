#include <iostream>
#include <ctime>
#include <pthread.h>
#include "./testes.hpp"
#include "./mascara.hpp"
#include "./filtros.hpp"

using namespace std;

string arquivos[3]{
    "grupo_01_imagem_1_linhas_33_palavras_391",
    "grupo_01_imagem_2_linhas_45_palavras_337",
    "grupo_01_imagem_3_linhas_16_palavras_276"
};

Mascara mascara_suavizacao = Mascara(3, 3, filtro_mediana, false);
Mascara mascara_dilatacao = Mascara(11, 7, filtro_dilatacao, true);
Mascara mascara_derivacao = Mascara(3, 3, filtro_laplaciano, true);

void *ocr(void *id){
    long i = (long) id;
    string nomeArquivo = arquivos[i];
    string mkdir = "mkdir -m 777 -p img/resultados/" + nomeArquivo;

    system(mkdir.c_str());

    cout << "Processando imagem (" << i << "): img/exemplos/" + nomeArquivo + ".pbm\n" << endl << endl;

    cout << "Passo 1 (" << i << ") - Suavizacao" << endl << endl;
    teste_suavizacao("img/exemplos/"+nomeArquivo+".pbm", "img/resultados/"+nomeArquivo+"/1_suavizacao.pbm", &mascara_suavizacao);

    cout << "Passo 2 (" << i << ") - Dilatacao" << endl << endl;
    teste_dilatacao("img/resultados/"+nomeArquivo+"/1_suavizacao.pbm", "img/resultados/"+nomeArquivo+"/2_dilatacao.pbm", &mascara_dilatacao);

    cout << "Passo 3 (" << i << ") - Identificar Palavras" << endl << endl;
    teste_identificar_palavras("img/resultados/"+nomeArquivo+"/2_dilatacao.pbm", "img/resultados/"+nomeArquivo+"/3_identificacao.pbm");

    cout << "Passo 4 (" << i << ") - Derivacao" << endl << endl;
    teste_derivacao("img/resultados/"+nomeArquivo+"/3_identificacao.pbm", "img/resultados/"+nomeArquivo+"/4_derivacao.pbm", &mascara_derivacao);

    cout << "Passo 5 (" << i << ") - Soma" << endl << endl;
    teste_soma("img/resultados/"+nomeArquivo+"/1_suavizacao.pbm", "img/resultados/"+nomeArquivo+"/4_derivacao.pbm", "img/resultados/"+nomeArquivo+"/5_final.pbm");

    pthread_exit(NULL);
}

void inicializacao_mascara_dilatacao(){
    for(int i = 0; i < mascara_dilatacao.get_altura(); i++){
        for(int j = 0; j < mascara_dilatacao.get_largura(); j++){
            mascara_dilatacao.matriz[i][j] = 1;
        }
    }
}

void inicializacao_mascara_derivacao(){
    mascara_derivacao.matriz[0][0] = -1;
    mascara_derivacao.matriz[0][1] = -1;
    mascara_derivacao.matriz[0][2] = -1;
    mascara_derivacao.matriz[1][0] = -1;
    mascara_derivacao.matriz[1][1] = 9;
    mascara_derivacao.matriz[1][2] = -1;
    mascara_derivacao.matriz[2][0] = -1;
    mascara_derivacao.matriz[2][1] = -1;
    mascara_derivacao.matriz[2][2] = -1;
}

int main(){
    time_t inicio = time(0);

    pthread_t threads[3];
    
    inicializacao_mascara_dilatacao();
    inicializacao_mascara_derivacao();

    for(long i = 0; i < 3; i++) pthread_create(&threads[i], NULL, ocr, (void *) i);

    for(int i = 0; i < 3; i++)
        if(pthread_join(threads[i], NULL) != 0)
            perror("Falha ao finalizar a thread\n");

    time_t fim = time(0);

    cout << "Tempo: " << difftime(fim, inicio) << endl;

    return 0;

}