# Projeto PI - 2023.2
---
Projeto desenvolvido para a disciplina `Processamento de Imagens`, ministrada pela professora Beatriz Trinchão Andrade de Carvalho na Universidade Federal de Sergipe.  

---

## Desenvolvedores:

- [Joaquim Luna Menezes Neto](https://github.com/joaqmnz);
- [Renato Porfirio Santos Xavier](https://github.com/RenatoPorfirio);
- [Victor Matos Dos Santos Lima](https://github.com/VictorMSLima);
- [Yuming Ruan](https://github.com/Myngruan).
---

## Sobre o Pojeto 

### 1. Especificação

Será desenvolvido um programa que retorna a quantidade de linhas e palavras em uma imagem no formato PBM ASCII. A imagem conterá um texto com uma ou mais colunas.
O programa também deverá gerar uma imagem PBM ASCII com o texto de entrada, no qual cada palavra estará circunscrita por um retângulo.

Obs: O texto será completamente escrito com a fonte Arial, com o mesmo tamanho para todos caracteres, podendo conter ruidos sal e pimenta.

### 2. Dependências

#### Dependencias de Produção
- Compilador C++;

#### Dependencias de Desenvolvimento
- GNU Make;
- GNU Compiler Collection (GCC);
- Valgrind;

### 3. Estruturação

- bin: contém os binários do projeto após a compilação;
- src: contém todo o código fonte do projeto;
- img: contém todos os arquivos de imagem do projeto;

### 4. Como funciona

Para auxiliar na construção do projeto, foi adotado o uso da ferramenta [GNU Make](https://www.gnu.org/software/make/).
O arquivo Makefile contém as seguintes rotinas de execução:
    
- all(padrão): Compila o código gerando binários para execução padrão e debug, limpa os arquivos de objeto gerados no processo de compilação, e executa o programa;
- clean: Limpa os arquivos gerados pela compilação e execução do projeto;
- cc: Executa a compilação padrão do projeto;
- cc-dbg: Compila o projeto com flags de debug;
- run: Executa o programa normalmente;
- run-dbg: Executa o programa através do debugger [GDB](https://www.sourceware.org/gdb/)
- run-vgd: Executa o programa utilizando a ferramenta [Valgrind](https://valgrind.org/), com o intuito de inspecionar o gerenciamento de memória.
---
Copyright (C) 2024 Universidade Federal de Sergipe

Este programa é software livre: você pode redistribuí-lo e/ou modificá-lo sob os termos da Licença Pública Geral GNU conforme publicada por a Free Software Foundation, seja a versão 3 da Licença, ou (a seu critério) qualquer versão posterior.

Este programa é distribuído na esperança de que seja útil, mas SEM QUALQUER GARANTIA; mesmo sem a garantia implícita de COMERCIALIZAÇÃO ou ADEQUAÇÃO A UM DETERMINADO FIM. Veja a Licença Pública Geral GNU para mais detalhes.

Você deveria ter recebido uma cópia da Licença Pública Geral GNU junto com este programa. Caso contrário, consulte <https://www.gnu.org/licenses/>.
