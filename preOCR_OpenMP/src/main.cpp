/********************************************************************
 * Execução:....................................................... *
 * Ao rodar o comando `make run` ou digitar `./main` no............ *
 * terminal após compilar o arquivo main.cpp, o programa........... *
 * irá executar os testes de operação definidos no arquivo......... *
 * testes.hpp para cada uma das imagens identificadas na........... *
 * variável `arquivos` no arquivo main.cpp......................... *
 * ................................................................ *
 * O processo ocorrerá em 5 passos:................................ *
 * ................................................................ *
 * 1. Suavização da imagem para eliminação de ruídos;.............. *
 * 2. Dilatação da imagem para unir as letras e melhorar a......... *
 *    identificação de palavras;................................... *
 * 3. Identificação de palavras e linhas através de caixas......... *
 *    retangulares que demarcam as mesmas;......................... *
 * 4. Aplicação de filtro de derivação de 2ª ordem para............ *
 *    capturar os contornos das caixas retangulares;............... *
 * 5. Soma da imagem original com a imagem derivada para........... *
 *    destacar as palavras identificadas........................... *
 * ................................................................ *
 * O resultado final será armazenado no caminho:................... *
 * img/resultados/<nome_da_imagem>/5_final.pbm..................... *
 * ................................................................ *
 * A contagem de linhas e palavras será armazenada em:............. *
 * img/resultados/<nome_da_imagem>/3_identificacao.pbm_contagem.txt *
 *******************************************************************/

#include <iostream>
#include <ctime>
#include <omp.h>
#include "./testes.hpp"
#include "./mascara.hpp"
#include "./filtros.hpp"

int main(){
    time_t inicio = time(0);

    Mascara mascara_suavizacao = Mascara(3, 3, filtro_mediana, false);
    
    Mascara mascara_dilatacao = Mascara(11, 7, filtro_dilatacao, true);
    for(int i = 0; i < mascara_dilatacao.get_altura(); i++){
        for(int j = 0; j < mascara_dilatacao.get_largura(); j++){
            mascara_dilatacao.matriz[i][j] = 1;
        }
    }
    
    Mascara mascara_derivacao = Mascara(3, 3, filtro_laplaciano, true);
    mascara_derivacao.matriz[0][0] = -1;
    mascara_derivacao.matriz[0][1] = -1;
    mascara_derivacao.matriz[0][2] = -1;
    mascara_derivacao.matriz[1][0] = -1;
    mascara_derivacao.matriz[1][1] = 9;
    mascara_derivacao.matriz[1][2] = -1;
    mascara_derivacao.matriz[2][0] = -1;
    mascara_derivacao.matriz[2][1] = -1;
    mascara_derivacao.matriz[2][2] = -1;

    string arquivos[3]{
        "grupo_01_imagem_1_linhas_33_palavras_391",
        "grupo_01_imagem_2_linhas_45_palavras_337",
        "grupo_01_imagem_3_linhas_16_palavras_276"
    };
    #pragma omp parallel for
    for(size_t i = 0; i < 3; i++){
        string nomeArquivo = arquivos[i];
        string mkdir = "mkdir -m 777 -p img/resultados/" + nomeArquivo;

        system(mkdir.c_str());

        std::cout << "**************************************************************************" << std::endl;
        std::cout << "Processando imagem: img/exemplos/" + nomeArquivo + ".pbm\n" << std::endl;

        std::cout <<"Passo 1 - ";
        teste_suavizacao("img/exemplos/"+nomeArquivo+".pbm", "img/resultados/"+nomeArquivo+"/1_suavizacao.pbm", &mascara_suavizacao);
        std::cout << std::endl;
        std::cout <<"Passo 2 - ";
        teste_dilatacao("img/resultados/"+nomeArquivo+"/1_suavizacao.pbm", "img/resultados/"+nomeArquivo+"/2_dilatacao.pbm", &mascara_dilatacao);
        std::cout << std::endl;
        std::cout <<"Passo 3 - ";
        teste_identificar_palavras("img/resultados/"+nomeArquivo+"/2_dilatacao.pbm", "img/resultados/"+nomeArquivo+"/3_identificacao.pbm");
        std::cout << std::endl;
        std::cout <<"Passo 4 - ";
        teste_derivacao("img/resultados/"+nomeArquivo+"/3_identificacao.pbm", "img/resultados/"+nomeArquivo+"/4_derivacao.pbm", &mascara_derivacao);
        std::cout << std::endl;
        std::cout <<"Passo 5 - ";
        teste_soma("img/resultados/"+nomeArquivo+"/1_suavizacao.pbm", "img/resultados/"+nomeArquivo+"/4_derivacao.pbm", "img/resultados/"+nomeArquivo+"/5_final.pbm");
        std::cout << std::endl;
    }

    time_t fim = time(0);

    std::cout << "Tempo: " << difftime(fim, inicio) << std::endl;

    return 0;

}

// g++ ./src/main.cpp -o ./main 