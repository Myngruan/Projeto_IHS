#ifndef __TESTES_HPP__
#define __TESTES_HPP__

#include <iostream>
#include <fstream>
#include "./pbm.hpp"
#include "./mascara.hpp"

void teste_ruido(string origem, string destino, unsigned int probabilidade_ruido){
    PBM_Img img = PBM_Img(origem);
    std::cout << "Aplicando ruido com probabilidade de " << probabilidade_ruido << "% em: " << origem << std::endl;
    img.aplicar_ruidos(10);
    std::cout << "Salvando resultado em: " << destino << std::endl;
    img.salvar(destino);
}

void teste_suavizacao(string origem, string destino, Mascara *mascara_suavizacao){
    PBM_Img img = PBM_Img(origem);
    std::cout << "Aplicando suavizacao com mascara " << mascara_suavizacao->get_largura() << "x" << mascara_suavizacao->get_altura() << " em: " << origem << std::endl;
    img.convoluir(mascara_suavizacao);
    std::cout << "Salvando resultado em: " << destino << std::endl;
    img.salvar(destino);
}

void teste_dilatacao(string origem, string destino, Mascara *mascara_dilatacao){
    PBM_Img img = PBM_Img(origem);
    std::cout << "Aplicando dilatação com mascara " << mascara_dilatacao->get_largura() << "x" << mascara_dilatacao->get_altura() << " em: " << origem << std::endl;
    img.convoluir(mascara_dilatacao);
    std::cout << "Salvando resultado em: " << destino << std::endl;
    img.salvar(destino);
}

void teste_derivacao(string origem, string destino, Mascara *mascara_derivacao){
    PBM_Img img = PBM_Img(origem);
    std::cout << "Aplicando derivação com mascara " << mascara_derivacao->get_largura() << "x" << mascara_derivacao->get_altura() << " em: " << origem << std::endl;
    img.convoluir(mascara_derivacao);
    std::cout << "Salvando resultado em: " << destino << std::endl;
    img.salvar(destino);
}

void teste_soma(string imagem1, string imagem2, string destino){
    PBM_Img img1 = PBM_Img(imagem1);
    PBM_Img img2 = PBM_Img(imagem2);
    std::cout << "Somando " << imagem1 << " à " << imagem2 << std::endl;
    img1.somar(&img2);
    std::cout << "Salvando resultado em: " << destino << std::endl;
    img1.salvar(destino);
}

void teste_identificar_palavras(string origem, string destino){
    PBM_Img img = PBM_Img(origem);
    std::cout << "Identificando palavras em: " << origem << std::endl;
    int *contagens = img.identificar_objetos();
    std::cout << "Salvando resultado em: " << destino << std::endl;
    img.salvar(destino);

    std::cout << "Salvando resultado da contagem no arquivo: " << destino + "_contagem.txt" << std::endl;
    std::ofstream arquivo(destino + "_contagem.txt");
    arquivo << "Palavras: " << contagens[0] << std::endl << "Linhas: " << contagens[1] << std::endl;
    arquivo.close();
    delete [] contagens;
}

#endif