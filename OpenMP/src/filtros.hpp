#ifndef __FILTROS_IMG_HPP__
#define __FILTROS_IMG_HPP__

#include <cmath>
#include <iostream>
#include "./utilitarios.hpp"

void filtro_mediana(int largura_mascara, int altura_mascara, float** matriz_mascara, byte** matriz_imagem_original, byte** matriz_imagem_copia, int x, int y){
    /*************************************************************
     * Filtro da mediana para uma escala binária. A  implementa- *
     * ção não necessita de ordenação, pois foi feita baseada na *
     * premissa de que dentre dois possíveis valores num conjun- *
     * to  de  tamanho ímpar, a  mediana sempre será o valor que *
     * aparece em maior quantidade.............................. *
    *************************************************************/
    int sobra_x = (largura_mascara-1)/2;
    int sobra_y = (altura_mascara-1)/2;
    int mapa[2] = {0,0};
    for(int v = 0; v < altura_mascara; v++){
        for(int w = 0; w < largura_mascara; w++){
            mapa[matriz_imagem_original[y+v-sobra_y][x+w-sobra_x]]++;
        }
    }
    matriz_imagem_copia[y][x] = mapa[0] > mapa[1] ? 0 : 1;
}

void filtro_dilatacao(int largura_mascara, int altura_mascara, float** matriz_mascara, byte** matriz_imagem_original, byte** matriz_imagem_copia, int x, int y){
    /*************************************************************
     * Filtro de que considera o pixel central como pivô........ *
    *************************************************************/
    if(!matriz_imagem_original[y][x]) return;
    int sobra_x = (largura_mascara-1)/2;
    int sobra_y = (altura_mascara-1)/2;
    
    for(int v = 0; v < altura_mascara; v++){
        for(int w = 0; w < largura_mascara; w++){
            int indice_v = y+v-sobra_y;
            int indice_w = x+w-sobra_x;
            matriz_imagem_copia[indice_v][indice_w] = matriz_imagem_original[indice_v][indice_w] || matriz_mascara[v][w];
        }
    }
}

void filtro_laplaciano(int largura_mascara, int altura_mascara, float** matriz_mascara, byte** matriz_imagem_original, byte** matriz_imagem_copia, int x, int y){
    /*************************************************************
     * Implementação de filtro laplaciano para imagens de escala *
     * binária.................................................. *
    *************************************************************/
    int sobra_x = (largura_mascara-1)/2;
    int sobra_y = (altura_mascara-1)/2;
    int valor = 0;
    int maior_valor = matriz_mascara[sobra_y][sobra_x];
    for(int v = 0; v < altura_mascara; v++){
        for(int w = 0; w < largura_mascara; w++){
            int indice_v = y+v-sobra_y;
            int indice_w = x+w-sobra_x;
            valor += matriz_imagem_original[indice_v][indice_w] * matriz_mascara[v][w];
        }
    }
    float c = 1.0/log(1 + maior_valor);
    matriz_imagem_copia[y][x] = ops::arredondar(c * log(1 + abs(valor)));
}

#endif