#ifndef __MASCARA_IMG_HPP__
#define __MASCARA_IMG_HPP__

#include <iostream>
#include "./utilitarios.hpp"

typedef unsigned char byte;

class Mascara {
private:
    int _altura;
    int _largura;
    void (*_op_filtro)(int largura_mascara, int altura_mascara, float** matriz_mascara, byte** matriz_imagem_original, byte** matriz_imagem_copia, int x, int y);
public:
    float **matriz;
    
    int get_altura(){ return _altura; }

    int get_largura(){ return _largura; }

    Mascara(int largura, int altura, void (*op_filtro)(int, int, float**, byte**, byte**, int, int), bool inicializar_matriz = true){
        _altura = altura;
        _largura = largura;
        _op_filtro = op_filtro;
        matriz = inicializar_matriz ? matrizes::inicializar_matriz<float>(largura, altura) : NULL;
    }

    void inicializar_matriz(){
        if(matriz) matrizes::destruir_matriz<float>(matriz, _altura);
        matriz = matrizes::inicializar_matriz<float>(_largura, _altura);
    }

    ~Mascara(){ if(matriz) matrizes::destruir_matriz<float>(matriz, _altura); }

    void filtrar(byte** matriz_imagem_original, byte** matriz_imagem_copia, int x, int y){
        _op_filtro(_largura, _altura, matriz, matriz_imagem_original, matriz_imagem_copia, x, y);
    }

    void imprimir(){
        if(matriz){
            for(int i = 0; i < _altura; i++){
                for(int j = 0; j < _largura; j++){
                    std::cout << matriz[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }
    }
};

#endif