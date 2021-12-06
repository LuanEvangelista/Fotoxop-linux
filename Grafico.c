/*
 * DCE05968 - Estruturas de Dados I
 * Funções responsaveis pela parte grafica.
 */

/*
 * As funções presentes nesse módulo NÃO precisam ser modificadas, a não ser que você
 * queira adicionar mais opções (por exemplo, mais filtros) ao programa.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h> /* Funções do glut */
#endif

#include "Imagem.h"  /* Tipos e protótipos de funções que manipulam imagens */
#include "Filtros.h" /* Protótipo das funções responsáveis pelos filtros das imagens */

/* Protótipo das funções do módulo Grafico                       */
/* Como essas funções não estão no Grafico.h elas são acessíveis */
/* apenas no módulo Grafico.c                                    */ 
void alteraTamanhoJanela(int w, int h);
void gerenciaTeclado(unsigned char key, int x, int y);
void desenha();
void opcoes();

/*-------------------------------------------------------------*/
/* Funções e variáveis static são visíveis apenas no módulo    */
/*-------------------------------------------------------------*/

/* VARIAVEIS GLOBAIS: iniciam com o caractere '_' (underscore)  */
static Imagem *_imagem = NULL;
static Imagem *_copiaDaImagem = NULL;
static Imagem *_imagemOriginal = NULL;
static bool _imagemFoiModificada = false;


/* Função responsável por iniciar o glut e gerar a janela com a imagem
 * Além disso, ela também iniciliza as variáveis globais utilizadas no programa.
 *
 * Você não precisa/deve modificar essa função 
 */
void inicializa(int *argc, char *argv[], Imagem *img){

    // Variável global '_imagem' recebem o endereço de 'img'
    _imagem = img;
    // Fazemos uma cópia da imagem para ser utilizada na opção de desfazer uma operação
    _copiaDaImagem = copiaImagem(_imagem);
    // Precisamos de uma cópia da imagem original, para ser utilizada na opção de voltar a imagem original
    _imagemOriginal = copiaImagem(_imagem);

    /* GLUT */
    glutInit(argc, argv);
    /* Inicializa o glut */
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    /* Cria uma janela com o tamanho da imagem */
    glutInitWindowSize(obtemLargura(_imagem), obtemAltura(_imagem));
    /* Configura o título da janela */
    glutCreateWindow("FotoXop");

    /* ------------------------------------------------------------------------------------------------ */
    /* Funções callback que serão utilizadas para tratar evetos                                         */
    /* Função 'gerenciaTeclado' é chamada sempre que uma tecla for presionada                           */
    glutKeyboardFunc(gerenciaTeclado);
    //Função 'alteraTamanhoJanela' é chamada sempre que o tamanho da janela for modificada              */
    glutReshapeFunc(alteraTamanhoJanela); 
    //Função 'desenha' é chamada sempre que qualquer evento acontecer para desenhar a imagem na janela  */
    glutDisplayFunc(desenha);
    /* ------------------------------------------------------------------------------------------------ */

    /* Exibi (no terminal) as opções do programa */
    opcoes();

    /* Inicia o loop do glut que fica responsável por gerenciar todos os eventos enquanto 
     * o programa não for finalizado.
     */
    glutMainLoop();
}

/* Função responsável por fazer o desenho na janela do glut
 * 
 * Você não precisa/deve modificar essa função 
 */
void desenha() {
    int col, lin;
    /* Cada pixel da imagem é desenhado como sendo um ponto da janela          */
    /* Esses pontos são desenhados de acordo com a sua posição e cor na imagem */
    glBegin(GL_POINTS);
    for (int h = 0; h < obtemAltura(_imagem); h++) {
        for (int w = 0; w < obtemLargura(_imagem); w++) {
            Pixel pixel = obtemPixel(_imagem, h, w);
            glColor3ubv(pixel.cor);
            glVertex2f(w, obtemAltura(_imagem) - h - 1);
        }
    }
    glEnd();

    /* Sempre que a função é chamada todas as informações que estão no 
     * buffer do sistema deve ser exibido. A função abaixo fica responsável por
     * essa atualização.
     */
    glutSwapBuffers();
}

/* Função responsável por redesenhar as informações, caso o tamanho da janela seja alterado
 * 
 * Você não precisa/deve modificar essa função 
 */
void alteraTamanhoJanela(int col, int lin) {
    glViewport(0, 0, col, lin);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, col, 0, lin);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}

/* Função responsável por gerenciar os eventos do teclado
 * Sempre que uma tecla é precionada na janela do glut, essa função é invocada.
 *
 * Essa função chama as funções (de acordo com a opção escolhida) presentes nos 
 * módulos Imagem.h e Filtros.h.  
 * 
 * Você não precisa/deve modificar essa função, mas fique a vontade para adiconar 
 * outras opções (por exemplo, outros filtros). 
 * Se for adicionar novas opções, adicione após o último case e não modifique o 
 * conteúdo de cada case.
 */
void gerenciaTeclado(unsigned char key, int mx, int my) {
    char nomeArq[100];
    switch (key) {
    /* Filtro: escurecerImagem */
    /* Responsável por aplicar o filtro escurecer na imagem */
    case '1':
        AVISO(Grafico: escurecendo a imagem.);
        _copiaDaImagem = copiaImagem(_imagem);
        escurecerImagem(_imagem);
        _imagemFoiModificada = true;
        AVISO(Grafico: voltei da funcao escurecerImagem.\n);
        opcoes();
        desenha();
        break;
    /* Filtro: clarearImagem */
    /* Responsável por aplicar o filtro clarear na imagem */
    case '2':
        AVISO(Grafico: clareando a imagem.);
        _copiaDaImagem = copiaImagem(_imagem);
        clarearImagem(_imagem);
        _imagemFoiModificada = true;
        AVISO(Grafico: voltei da funcao clarearImagem.\n);
        opcoes();
        desenha();
        break;
    /* Filtro: escalaDeCinzaImagem */
    /* Responsável por aplicar o filtro escala de cinza na imagem */
    case '3':
        AVISO(Grafico: realcando a imagem.);
        _copiaDaImagem = copiaImagem(_imagem);
        escalaDeCinzaImagem(_imagem);
        _imagemFoiModificada = true;
        AVISO(Grafico: voltei da funcao escalaDeCinzaImagem.\n);
        opcoes();
        desenha();
        break;
    /* Filtro: Filtro de Sobel */
    /* Responsável por aplicar o filtro de sobel na imagem */
    case '4':
        AVISO(Grafico: aplicando o filtro de Sobel na imagem.);
        _copiaDaImagem = copiaImagem(_imagem);
        filtroSobel(_imagem);
        _imagemFoiModificada = true;
        AVISO(Grafico: voltei da funcao filtroSobel.\n);
        opcoes();
        desenha();
        break;
    /* Filtro: deteccaoBordasLaplace */
    /* Responsável por aplicar a detecção de bordas de Laplace na imagem */
    case '5':
        AVISO(Grafico: aplicando a detecção de bordas de Laplace na imagem.);
        _copiaDaImagem = copiaImagem(_imagem);
        deteccaoBordasLaplace(_imagem);
        _imagemFoiModificada = true;
        AVISO(Grafico: voltei da funcao deteccaoBordasLaplace.\n);
        opcoes();
        desenha();
        break;
    /* Filtro: meuFiltro */
    /* Responsável por aplicar o filtro que você desenvolveu na imagem */
    case 'm':
    case 'M':
        AVISO(Grafico: aplicando o Meu Filtro na imagem.);
        _copiaDaImagem = copiaImagem(_imagem);
        meuFiltro(_imagem);
        _imagemFoiModificada = true;
        AVISO(Grafico: voltei da funcao meuFiltro.\n);
        opcoes();
        desenha();
        break;
    /* Volta para a imagem original */
    case 'o':
    case 'O':
        AVISO(Grafico: voltando para a imagem original.);
        liberaImagem(_imagem);
        _imagem = copiaImagem(_imagemOriginal);
        _imagemFoiModificada = false;
        AVISO(Grafico: exibindo imagem original.\n);
        opcoes();
        desenha();
        break;
    /* Desfaz a última modificação */
    case 'z':
    case 'Z':
        AVISO(Grafico: desfazendo a ultima modificacao.);
        if (_imagemFoiModificada){
            liberaImagem(_imagem);
            _imagem = copiaImagem(_copiaDaImagem);
            _imagemFoiModificada = false;
        }
        else{
            AVISO(Grafico: Nada a ser desfeito!);
        }
        AVISO(Grafico: voltei da funcao desfazOperacao.\n);
        opcoes();
        desenha();
        break;
    /* Salva a imagem */
    case 's':
    case 'S':
        AVISO(Grafico: chamando a funcao salvaImagem.);
        printf("Informe o nome do arquivo para a gravação: ");
        scanf("%s", nomeArq);
        salvaImagem(_imagem, nomeArq);
        AVISO(Grafico: voltei da funcao salvaImagem.\n);
        opcoes();
        break;
    /* Termina a execução do programa  */
    case 27: // tecla ESC
    case 'x':
    case 'X':
        liberaImagem(_imagem);
        liberaImagem(_copiaDaImagem);
        liberaImagem(_imagemOriginal);
        exit(EXIT_SUCCESS);
        break; //Nunca chegará aqui, apenas para evitar alguns warnings 

    /* Caso queira adicionar outras opções ao seu programa, adicione novos case's aqui*/   

    /* Ignora teclas que não estejam entre uma das opções */ 
    default:
        break;
    }
}

/* Função que apenas exibi as opções do programa no terminal.
 * Caso você escolha adicionar novas opções, complete essa função. 
 * Caso contrário, não precisa modificá-la.
 */
void opcoes() {
    printf("Escolha uma opção:\n"
           " '1' para escurecer a imagem\n"
           " '2' para clarear a imagem\n"
           " '3' para deixar a imagem em escala de cinza\n"
           " '4' para aplicar o filtro de Sobel\n"
           " '5' para aplicar a detecção de bordas de Laplace\n"
           " 'm' para aplicar o Meu Filtro\n"
           " 'o' para voltar a imagem original\n"
           " 'z' para desfazer a última modificação\n"
           " 's' para salvar a imagem atual\n"
           " 'x' para encerrar o programa\n");
}