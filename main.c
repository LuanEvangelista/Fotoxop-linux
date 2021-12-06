/*
 * DCE05968 - Estruturas de Dados I
 *
 * Função main() do EP
 * 
 * Você não precisa/deve modificar esse arquivo 
 */

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#include "Imagem.h"  /* Tipos e protótipos de funções que manipulam imagens */
#include "Grafico.h" /* Protótipos de funções graficas */

int main(int argc, char *argv[]) {

    Imagem* imagem = NULL; //Ponteiro para a imagem
    char nomeArq[100];     //Nome do arquivo

    //Verifica se foi passado como argumento o nomeo do arquivo .ppm
    //Caso não seja, é solicitado ao usuário o arquivo.
    if(argc == 2) {
        strcpy(nomeArq, argv[1]);
    }
    else {
        printf("Digite o nome do arquivo ppm: ");
        scanf("%99s[^\n]", nomeArq);
    }

    //Faz a leitura dos dados e salva as informação em 'imagem'
    imagem = carregaImagem(nomeArq);
    //Verifica se foi possivel criar a imagem
    if (imagem == NULL) {
        AVISO("Erro ao carregar a imagem");
        return 0;
    }
    //Inicializa o GLUT exibindo a imagem em uma janela
    inicializa(&argc, argv, imagem);

    return 0;
}


