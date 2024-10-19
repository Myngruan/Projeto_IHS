#ifndef __UTILITARIOS_IMG_HPP__
#define __UTILITARIOS_IMG_HPP__

#include <ctime>
#include <cstdlib>
#include <omp.h>  

namespace ops {
    bool eNumero(char c){ return ('0' <= c && c <= '9') ? 1 : 0; }
    bool eAlfa(char c){ return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') ? 1 : 0; }
    int arredondar(float x){ int int_x = (int)x; return (x - int_x < 0.5) ? int_x : int_x + 1; }

    int numeroAleatorio(int inicio, int fim){ 
        return inicio + (rand() % (long)(fim - inicio + 1) * rand() % (long)(fim - inicio + 1)) % (fim - inicio + 1); 
    }
};

namespace matrizes {
    // Inicialização de uma matriz 2D
    template <class T>
    T** inicializar_matriz(int largura, int altura) {
        T** matriz = new T*[altura];

        // Paralelizando a alocação das linhas da matriz
        #pragma omp parallel for
        for (int i = 0; i < altura; i++) {
            matriz[i] = new T[largura];
        }
        return matriz;
    }

    // Função para destruir uma matriz 2D
    template <class T>
    void destruir_matriz(T** matriz, int altura) {
        // Paralelizando a destruição de cada linha da matriz
        #pragma omp parallel for
        for (int i = 0; i < altura; i++) {
            delete[] matriz[i];
        }
        delete[] matriz;
    }
}

#endif
