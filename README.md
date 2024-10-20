# Projeto_IHS
---
Projeto de Interface Hardware/Software baseado no projeto de Processamento de Imagen com foco na aplicação de técnicas de paralelismo para otimizar o desempenho.

---

## Desenvolvedores:

- [Joaquim Luna Menezes Neto](https://github.com/joaqmnz);
- [Victor Matos Dos Santos Lima](https://github.com/VictorMSLima);
- [Yuming Ruan](https://github.com/Myngruan).
---


## Sobre o Projeto 

### Especificação do Projeto de Processamento de Imagens

Será desenvolvido um programa que retorna a quantidade de linhas e palavras em uma imagem no formato PBM ASCII. A imagem conterá um texto com uma ou mais colunas.
O programa também deverá gerar uma imagem PBM ASCII com o texto de entrada, no qual cada palavra estará circunscrita por um retângulo.

Obs: O texto será completamente escrito com a fonte Arial, com o mesmo tamanho para todos caracteres, podendo conter ruidos sal e pimenta.

Na pasta preOCR_Normal, encontra-se o projeto desenvolvido em C++.

## Otimização de Tempo de Execução com Técnicas de Paralelismo

Foram aplicadas duas técnicas de paralelismo distintas para otimizar o tempo de execução do projeto de processamento de imagens. O objetivo foi explorar diferentes abordagens de paralelismo a fim de acelerar o processamento e melhorar a eficiência geral.

### Estrutura do Projeto

- **`preOCR`**: Contém o projeto original desenvolvido em C++ sem técnicas de paralelismo.
- **`preOCR_Pthreads`**: Implementa paralelismo utilizando **pthreads**.
- **`preOCR_OpenMP`**: Utiliza **OpenMP** para a otimização de tempo de execução.

### Pthreads

Na pasta `preOCR_paralelo`, foram utilizadas as pthreads, uma biblioteca de threads padrão no POSIX, para dividir o processamento em múltiplas threads. A ideia é que diferentes partes da imagem sejam processadas simultaneamente por diferentes threads, permitindo um melhor uso dos recursos do sistema. Essa técnica é amplamente usada para operações que podem ser paralelizadas de forma explícita, onde o desenvolvedor tem controle total sobre a criação e gerenciamento das threads.

### OpenMP

Na pasta `preOCR_OpenMP`, a técnica de paralelismo implementada foi o OpenMP. Trata-se de uma API que facilita a paralelização de loops e outras operações em programas C++ sem a necessidade de gerenciar diretamente as threads. Com o OpenMP, foram aplicadas diretivas que identificam automaticamente as seções do código que podem ser executadas em paralelo, distribuindo a carga de trabalho entre os núcleos disponíveis de maneira mais automatizada e simples para o desenvolvedor.

## Conclusão

Essas técnicas foram implementadas com o intuito de comparar a eficiência das abordagens de pthreads e de OpenMP, ambas voltadas para a aceleração de tarefas críticas.
