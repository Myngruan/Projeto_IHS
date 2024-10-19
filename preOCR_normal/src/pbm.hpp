#ifndef __PBM_IMG_HPP__
#define __PBM_IMG_HPP__

#include <string>
#include <stdexcept>
#include <cstring>
#include <cstdio>
#include "utilitarios.hpp"
#include "mascara.hpp"

using namespace ops;
using namespace matrizes;
using std::string;

typedef unsigned char byte;

class PBM_Img {
private:
    byte **_matriz;
    int _altura;
    int _largura;

    void carregar(string caminho_arquivo);
    /*************************************************************
     * Utiliza funções da libc para carregar dados de um arquivo *
     * PBM...................................................... *
     *************************************************************/

    void dfs(int i, int j, int &minX, int &maxX, int &minY, int &maxY);
    /*************************************************************
     * Busca em profundidade para identificar a palavra......... *
     *************************************************************/
    
public:
    int get_altura(){ return _altura; }
    
    int get_largura(){ return _largura; }

    byte **get_matriz(){ return _matriz; }

    byte get_pixel(int i, int j){ return _matriz[i][j]; }

    PBM_Img(byte **matriz, int largura, int altura);
    /*************************************************************
     * Constrói um objeto de imagem a partir de uma matriz...... *
     *************************************************************/
    
    PBM_Img(string caminho_arquivo){ srand(time(NULL)); carregar(caminho_arquivo); };
    /*************************************************************
     * Constrói um objeto de imagem a partir de um arquivo...... *
     *************************************************************/
    
    ~PBM_Img(){ destruir_matriz<byte>(_matriz, _altura); }
    
    void salvar(string caminho_arquivo);
    /*************************************************************
     * Utiliza funções da libc para salvar dados em um arquivo   *
     * PBM...................................................... *
     *************************************************************/

    PBM_Img copia();
    /*************************************************************
     * Cria uma cópia de um objeto de imagem.................... *
     *************************************************************/

    void negativo();
    /*************************************************************
     * Inverte as cores da imagem............................... *
     *************************************************************/

    void convoluir(Mascara *mascara);
    /*************************************************************
     * Faz a convolucao de uma máscara com a imagem............. *
     *************************************************************/

    void somar(PBM_Img *img);
    /*************************************************************
     * Soma a matriz da imagem passada como parâmetro à imagem   *
     * atual.................................................... *
     *************************************************************/

    void aplicar_ruidos(int percentual);
    /*************************************************************
     * Aplica ruidos aleatórios na imagem, de acordo com um per- *
     * centual de chance de aplicação........................... *
     *************************************************************/

    int *identificar_objetos();
    /*************************************************************
     * Cria o retângulo na palavra identificada*
     *************************************************************/
};

//IMPLEMENTAÇÕES DOS METODOS DA CLASSE PBM_Img

void PBM_Img::carregar(string caminho_arquivo){
    FILE *arq = fopen(caminho_arquivo.c_str(), "r");
    if (arq == NULL) exit(EXIT_FAILURE);
    long checkpoint;
    char ch_teste;
    int altura;
    int largura;
    char tipo[3];
    char descarga[1024];

    do{
        do{
            checkpoint = ftell(arq);
            fscanf(arq, "%c", &ch_teste);
        } while(!eNumero(ch_teste) && !eAlfa(ch_teste) && ch_teste != '#');
        if(ch_teste == '#'){
            fscanf(arq, "%[^\n]", descarga);
        } else if(ch_teste == 'P'){
            fseek(arq, checkpoint, SEEK_SET);
            fscanf(arq, "%s", tipo);
        } else exit(EXIT_FAILURE);
    } while(ch_teste == '#');

    if (strcmp(tipo, "P1")) throw std::invalid_argument("Tipo da imagem incorreto!");

    do{
        do{
            checkpoint = ftell(arq);
            fscanf(arq, "%c", &ch_teste);
        } while(!eNumero(ch_teste) && !eAlfa(ch_teste) && ch_teste != '#');
        if(ch_teste == '#'){
            fscanf(arq, "%[^\n]", descarga);
        } else if(eNumero(ch_teste)){
            fseek(arq, checkpoint, SEEK_SET);
            fscanf(arq, "%u %u", &largura, &altura);
        } else exit(EXIT_FAILURE);
    } while(ch_teste == '#');

    _matriz = inicializar_matriz<byte>(largura, altura);

    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            do{ fscanf(arq, "%c", &ch_teste); } while(!eNumero(ch_teste));
            _matriz[i][j] = ch_teste - 48;
        }
    }
    _largura = largura;
    _altura = altura;
    
    fclose(arq);
}

PBM_Img::PBM_Img(byte **matriz, int largura, int altura){
    srand(time(NULL));
    _largura = largura;
    _altura = altura;
    _matriz = matriz;
}

void PBM_Img::salvar(string caminho_arquivo){
    FILE *arq = fopen(caminho_arquivo.c_str(), "w");

    if(!arq) exit(EXIT_FAILURE);
    fprintf(arq, "P1\n");
    fprintf(arq, "%u %u\n", _largura, _altura);

    for(int i = 0; i < _altura; i++){
        for(int j = 0; j < _largura; j++){
            fprintf(arq, "%hhu", _matriz[i][j]);
        }
        fprintf(arq, "\n");
    }
    
    fclose(arq);
}

PBM_Img PBM_Img::copia(){
    byte **matriz = inicializar_matriz<byte>(_largura, _altura);
    for(int i = 0; i < _altura; i++){
        for(int j = 0; j < _largura; j++){
            matriz[i][j] = _matriz[i][j];
        }
    }
    return PBM_Img(matriz, _largura, _altura);
}

void PBM_Img::negativo(){
    for(int i = 0; i < _altura; i++){
        for(int j = 0; j < _largura; j++){
            _matriz[i][j] = !_matriz[i][j];
        }
    }
}

void PBM_Img::convoluir(Mascara *mascara){
    if(mascara->get_altura()%2 == 0 || mascara->get_largura()%2 == 0){
        throw std::invalid_argument("Máscara de dimensão par!");
    }
    int sobra_x = (mascara->get_largura()-1)/2;
    int sobra_y = (mascara->get_altura()-1)/2;

    byte **nova_matriz = inicializar_matriz<byte>(_largura, _altura);

    for(int i = 0; i < _altura; i++){
        for(int j = 0; j < _largura; j++){
            if(i < sobra_y || j < sobra_x || i >= (_altura - sobra_y) || j >= (_largura - sobra_x)){
                nova_matriz[i][j] = 0;
            }
            else{
                mascara->filtrar(_matriz, nova_matriz, j, i);
            }
        }
    }
    destruir_matriz<byte>(_matriz, _altura);
    _matriz = nova_matriz;
}

void PBM_Img::somar(PBM_Img *img){
    if(_largura != img->get_largura() || _altura != img->get_altura()){
        throw std::invalid_argument("Imagens de tamanhos diferentes!");
    }
    for(int i = 0; i < _altura; i++){
        for(int j = 0; j < _largura; j++){
            _matriz[i][j] = _matriz[i][j] || img->get_pixel(i, j);
        }
    }
}

void PBM_Img::aplicar_ruidos(int percentual){
    for(int i = 0; i < _altura; i++){
        for(int j = 0; j < _largura; j++){
            if(numeroAleatorio(0, 100) <= percentual){
                _matriz[i][j] = numeroAleatorio(0, 1);
            }
        }
    }
}

void PBM_Img::dfs(int i, int j, int &minX, int &maxX, int &minY, int &maxY){
    
    if(_matriz[i][j] != 1) return; // Verifica se o pixel já foi visitado ou é branco

    // Atualiza os valores máximos e mínimos de x e y
    minX = std::min(minX, j);
    maxX = std::max(maxX, j);
    minY = std::min(minY, i);
    maxY = std::max(maxY, i);

    _matriz[i][j] = 0; // Marca o pixel como visitado

    // Chamada recursiva para os pixels vizinhos
    dfs(i + 1, j, minX, maxX, minY, maxY);
    dfs(i - 1, j, minX, maxX, minY, maxY);
    dfs(i, j + 1, minX, maxX, minY, maxY);
    dfs(i, j - 1, minX, maxX, minY, maxY);
}

int *PBM_Img::identificar_objetos(){
    int qtdPalavras = 0, qtdLinhas = 0;

    byte **novaMatriz = inicializar_matriz<byte>(_largura, _altura);

    for(int i = 0; i < _altura; i++){
        for(int j = 0; j < _largura; j++){
            novaMatriz[i][j] = 0;
        }
    }

    int ultimoMaxY = -1;

    for(int i = 0; i < _altura; i++){
        for(int j = 0; j < _largura; j++){
            if(_matriz[i][j] == 1){
                int minX = 10000000, maxX = -1, minY = 10000000, maxY = -1;

                dfs(i, j, minX, maxX, minY, maxY);

                for(int a = minY; a < maxY; a++){
                    for(int b = minX; b < maxX; b++){
                        novaMatriz[a][b] = 1;
                    }
                }
                ultimoMaxY = maxY;
                qtdPalavras++;
            }
        }
        if(i == ultimoMaxY) qtdLinhas++;
    }

    destruir_matriz<byte>(_matriz, _altura);
    _matriz = novaMatriz;

    return new int[2]{qtdPalavras, qtdLinhas};
}

#endif