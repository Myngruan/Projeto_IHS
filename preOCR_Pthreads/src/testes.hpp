#ifndef __TESTES_HPP__
#define __TESTES_HPP__

#include <iostream>
#include <fstream>
#include "./pbm.hpp"
#include "./mascara.hpp"

void teste_ruido(string origem, string destino, unsigned int probabilidade_ruido){
    PBM_Img img = PBM_Img(origem);
    img.aplicar_ruidos(10);
    img.salvar(destino);
}

// void aplicar(int id, string origem, string destino, Mascara *mascara){
//     PBM_Img img = PBM_Img(origem);
//     img.convoluir(id, mascara);
//     img.salvar(destino);
// }

void teste_suavizacao(string origem, string destino, Mascara *mascara_suavizacao){
    PBM_Img img = PBM_Img(origem);
    img.convoluir(mascara_suavizacao);
    img.salvar(destino);
}

void teste_dilatacao(string origem, string destino, Mascara *mascara_dilatacao){
    PBM_Img img = PBM_Img(origem);
    img.convoluir(mascara_dilatacao);
    img.salvar(destino);
}

void teste_derivacao(string origem, string destino, Mascara *mascara_derivacao){
    PBM_Img img = PBM_Img(origem);
    img.convoluir(mascara_derivacao);
    img.salvar(destino);
}

void teste_soma(string imagem1, string imagem2, string destino){
    PBM_Img img1 = PBM_Img(imagem1);
    PBM_Img img2 = PBM_Img(imagem2);
    img1.somar(&img2);
    img1.salvar(destino);
}

void teste_identificar_palavras(string origem, string destino){
    PBM_Img img = PBM_Img(origem);
    int *contagens = img.identificar_objetos();
    img.salvar(destino);

    std::ofstream arquivo(destino + "_contagem.txt");
    arquivo.close();
    delete [] contagens;
}

#endif