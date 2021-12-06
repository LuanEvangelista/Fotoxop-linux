/*
 * DCE05968 - Estruturas de Dados I
 * Funções responsaveis pelos filtros que podem ser aplicados na imagem.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Imagem.h"  /* Tipos e protótipos de funções que manipulam imagens */
#include "Filtros.h" /* Protótipo das funções responsáveis pelos filtros das imagens */

/* Função responsável por escurecer uma imagem
 * A função recebe um ponteiro para um struct Imagem e altera/escurece 
 * cada um de seus pixels em cada canal de cor (RGB).
 * 
 * Analise essa função com bastante atenção. Ela irá te auxiliar no entendimento 
 * do TAD Imagem e como outros filtros podem ser implementados.
 *
 * Você não precisa modificar essa função 
 */
void escurecerImagem(Imagem *img){
    int v;
    printf("Digite o fator de escurecimento: ");
    scanf("%d", &v);
    /* Cada canal de cor (RGB) de cada pixel é reduzido 'v' do valor.
     * Note que devemos garantir que o valor esteja entre 0 e 255.   
     * Como estamos subtraindo, verificamos apenas se o valor é >= 0 
     * Note também a utilização de expressão ternária e o cast (conversão) 
     * entre os valores Byte (unsigned int) e int. Esse cast evita erros nas 
     * operações matemáticas.
     */ 
    for (int h = 0; h < obtemAltura(img); h++) {
        for (int w = 0; w < obtemLargura(img); w++) {
            //Obtém o pixel da posição (h, w) da imagem 
            Pixel pixel = obtemPixel(img, h, w);
            //Modifica cada canal de cor do pixel
            pixel.cor[RED]   = (((int)pixel.cor[RED] - v) >= 0 ? ((int)pixel.cor[RED] - v) : 0);
            pixel.cor[GREEN] = (((int)pixel.cor[GREEN] - v) >= 0 ? ((int)pixel.cor[GREEN] - v) : 0);
            pixel.cor[BLUE]  = (((int)pixel.cor[BLUE] - v) >= 0 ? ((int)pixel.cor[BLUE] - v) : 0);
            //Grava o novo pixel na posição (h, w) da imagem
            recolorePixel(img, h, w, pixel);
        }
    }
}

/* Função responsável por clarear uma imagem
 * A função recebe um ponteiro para um struct Imagem e altera/clareia 
 * cada um de seus pixels em cada canal de cor (RGB).
 */
void clarearImagem(Imagem *img){
    int c,h,w;
    printf("Digite o fator de clareamento: ");
    scanf("%d", &c);

    for (h = 0; h < obtemAltura(img); h++) {
        for (w = 0; w < obtemLargura(img); w++) {

            Pixel pixel = obtemPixel(img, h, w);

            pixel.cor[RED]   = (((int)pixel.cor[RED]   + c) <= 255 ? ((int)pixel.cor[RED]   + c) : 255);
            pixel.cor[GREEN] = (((int)pixel.cor[GREEN] + c) <= 255 ? ((int)pixel.cor[GREEN] + c) : 255);
            pixel.cor[BLUE]  = (((int)pixel.cor[BLUE]  + c) <= 255 ? ((int)pixel.cor[BLUE]  + c) : 255);

            recolorePixel(img, h, w, pixel);
        }
    }
}

/* Função responsável por converter uma imagem colorida em escala de cinza
 * A função recebe um ponteiro para um struct Imagem e converte 
 * cada um de seus pixels em cada canal de cor (RGB) em uma tonalidade de cinza.
 * 
 * No pdf de descrição do EP existem duas estretégias para a implementação 
 * desse filtro. Você deve implementar uma delas ou pesquisar por outras alternativas. 
 */
void escalaDeCinzaImagem(Imagem *img){
int ci,h,w;

    for (h = 0; h < obtemAltura(img); h++) {
        for (w = 0; w < obtemLargura(img); w++) {

            Pixel pixel = obtemPixel(img, h, w);

            ci = (((int)pixel.cor[RED] + (int)pixel.cor[GREEN] + (int)pixel.cor[BLUE]) / 3);

            pixel.cor[RED] = ci;
            pixel.cor[GREEN] = ci;
            pixel.cor[BLUE] = ci;

            recolorePixel(img, h, w, pixel);
        }
    }
}

/* Função responsável por aplicar o filtro de Sobel na imagem. 
 * Leia o pdf do EP para obter mais informações de como o filtro é implementado. 
 */
void filtroSobel(Imagem *img){
    int pxr,pxg,pxb;
    int pyr,pyg,pyb;

    int gx [3][3] = {
    { 1, 0,-1},
    { 2, 0,-2},
    { 1, 0,-1}};

    int gy [3][3] = {
    { 1, 2, 1},
    { 0, 0, 0},
    {-1,-2,-1}};

    Imagem* copy = copiaImagem(img);

    int h,w;
    for(h = 1; h < obtemAltura(copy)-1; h++){
        for(w = 1; w < obtemLargura(copy)-1; w++){

            Pixel pixel = obtemPixel(copy, h-1, w-1);
            pxr= gx[0][0] * (int)pixel.cor[RED];
            pxg= gx[0][0] * (int)pixel.cor[GREEN];
            pxb= gx[0][0] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h, w-1);
            pxr += gx[1][0] * (int)pixel.cor[RED];
            pxg += gx[1][0] * (int)pixel.cor[GREEN];
            pxb += gx[1][0] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h+1, w-1);
            pxr += gx[2][0] * (int)pixel.cor[RED];
            pxg += gx[2][0] * (int)pixel.cor[GREEN];
            pxb += gx[2][0] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h-1, w+1);
            pxr += gx[0][2] * (int)pixel.cor[RED];
            pxg += gx[0][2] * (int)pixel.cor[GREEN];
            pxb += gx[0][2] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h, w+1);
            pxr += gx[1][2] * (int)pixel.cor[RED];
            pxg += gx[1][2] * (int)pixel.cor[GREEN];
            pxb += gx[1][2] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h+1, w+1);
            pxr += gx[2][2] * (int)pixel.cor[RED];
            pxg += gx[2][2] * (int)pixel.cor[GREEN];
            pxb += gx[2][2] * (int)pixel.cor[BLUE];

         // -----------------------------------------

            pixel = obtemPixel(copy, h-1, w-1);
            pyr = gy[0][0] * (int)pixel.cor[RED];
            pyg = gy[0][0] * (int)pixel.cor[GREEN];
            pyb = gy[0][0] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h, w-1);
            pyr += gy[0][1] * (int)pixel.cor[RED];
            pyg += gy[0][1] * (int)pixel.cor[GREEN];
            pyb += gy[0][1] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h+1, w-1);
            pyr += gy[0][2] * (int)pixel.cor[RED];
            pyg += gy[0][2] * (int)pixel.cor[GREEN];
            pyb += gy[0][2] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h-1, w+1);
            pyr += gy[2][0] * (int)pixel.cor[RED];
            pyg += gy[2][0] * (int)pixel.cor[GREEN];
            pyb += gy[2][0] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h, w+1);
            pyr += gy[2][1] * (int)pixel.cor[RED];
            pyg += gy[2][1] * (int)pixel.cor[GREEN];
            pyb += gy[2][1] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h+1, w+1);
            pyr += gy[2][2] * (int)pixel.cor[RED];
            pyg += gy[2][2] * (int)pixel.cor[GREEN];
            pyb += gy[2][2] * (int)pixel.cor[BLUE];

            if(pxr < 0)
                pxr = 0;  
            if(pxg < 0)
                pxg = 0; 
            if(pxb < 0)
                pxb = 0; 

            if(pxr > 255)
                pxr = 255;
            if(pxg > 255)
                pxg = 255;
            if(pxb > 255)
                pxb = 255;
            //------------------
            if(pyr < 0)
                pyr = 0;  
            if(pyg < 0)
                pyg = 0; 
            if(pyb < 0)
                pyb = 0; 

            if(pyr > 255)
                pyr = 255;
            if(pyg > 255)
                pyg = 255;
            if(pyb > 255)
                pyb = 255;
            
            int MediaR=0;
            int MediaG=0;
            int MediaB=0;

            MediaR = (pxr + pyr) / 2;
            MediaG = (pxg + pyg) / 2;
            MediaB = (pxb + pyb) / 2;    
            pixel.cor[RED] = MediaR;
            pixel.cor[GREEN] = MediaG;
            pixel.cor[BLUE] = MediaB;
            recolorePixel(img, h, w, pixel);

        }
    }
    liberaImagem(copy);  
}

/* Função responsável por aplicar a detecçõa de bordas de Laplace na imagem. 
 * Leia o pdf do EP para obter mais informações de como o filtro é implementado. 
 */
void deteccaoBordasLaplace(Imagem *img) {
    int pr,pg,pb;
    int g [3][3] = {
    { 0,-1, 0},
    {-1, 4,-1},
    { 0,-1, 0}};

    Imagem* copy = copiaImagem(img);

    int h,w;
    for(h = 1; h < obtemAltura(copy)-1; h++){
        for(w = 1; w < obtemLargura(copy)-1; w++){
            
            Pixel pixel = obtemPixel(copy, h-1, w);
            pr = g[0][1] * (int)pixel.cor[RED];
            pg = g[0][1] * (int)pixel.cor[GREEN];
            pb = g[0][1] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h, w-1);
            pr += g[1][0] * (int)pixel.cor[RED];
            pg += g[1][0] * (int)pixel.cor[GREEN];
            pb += g[1][0] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h, w);
            pr += g[1][1] * (int)pixel.cor[RED];
            pg += g[1][1] * (int)pixel.cor[GREEN];
            pb += g[1][1] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h, w+1);
            pr += g[1][2] * (int)pixel.cor[RED];
            pg += g[1][2] * (int)pixel.cor[GREEN];
            pb += g[1][2] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h+1, w);
            pr += g[2][1] * (int)pixel.cor[RED];
            pg += g[2][1] * (int)pixel.cor[GREEN];
            pb += g[2][1] * (int)pixel.cor[BLUE];

            if(pr < 0)
                pr = 0; 
            if(pr > 255)
                pr = 255;
            
            if(pg < 0)
                pg = 0; 
            if(pg > 255)
                pg = 255;

            if(pb < 0)
                pb = 0; 
            if(pb > 255)
                pb = 255;
                
            pixel.cor[RED] = pr;
            pixel.cor[GREEN] = pg;
            pixel.cor[BLUE] = pb;

            recolorePixel(img, h, w, pixel);

        }
    }
    liberaImagem(copy);
}

/* Função responsável por aplicar na imagem o filtro definido por você. Seja criativo! 
 * Filtros que apenas fazem algumas modificações simples em cada pixel 
 * (por exemplo, negativo, espelhar a imagem) não serão considerados.
 */


void meuFiltro(Imagem *img){
    int pr,pg,pb;
    int g [5][5] = {
    {   1,   4,   6,  4,  1},
    {   4,  16,  24, 16,  4},
    {   6,  24,-476, 24,  6},
    {   4,  16,  24, 16,  4},
    {   1,   4,   6,  4,  1}};

    
    int pr1,pg1,pb1;
    int m[3][3] = {
    {-2,-1, 0},
    {-1, 1, 1},
    {0 , 1, 2}};
    
    
    Imagem* copy = copiaImagem(img);

    int h,w;
    for(h = 2; h < obtemAltura(copy)-2; h++){
        for(w = 2; w < obtemLargura(copy)-2; w++){

            // Matriz de G[5][5] abaixo :

            Pixel pixel = obtemPixel(copy, h-2, w-2);
            pr = g[0][0] * (int)pixel.cor[RED];
            pg = g[0][0] * (int)pixel.cor[GREEN];
            pb = g[0][0] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h-2, w-1);
            pr += g[0][1] * (int)pixel.cor[RED];
            pg += g[0][1] * (int)pixel.cor[GREEN];
            pb += g[0][1] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h-2, w);
            pr += g[0][2] * (int)pixel.cor[RED];
            pg += g[0][2] * (int)pixel.cor[GREEN];
            pb += g[0][2] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h-2, w+1);
            pr += g[0][3] * (int)pixel.cor[RED];
            pg += g[0][3] * (int)pixel.cor[GREEN];
            pb += g[0][3] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h-2, w+2);
            pr += g[0][4] * (int)pixel.cor[RED];
            pg += g[0][4] * (int)pixel.cor[GREEN];
            pb += g[0][4] * (int)pixel.cor[BLUE];
         //---------------------------------------
            pixel = obtemPixel(copy, h-1, w-2);
            pr += g[1][0] * (int)pixel.cor[RED];
            pg += g[1][0] * (int)pixel.cor[GREEN];
            pb += g[1][0] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h-1, w-1);
            pr += g[1][1] * (int)pixel.cor[RED];
            pg += g[1][1] * (int)pixel.cor[GREEN];
            pb += g[1][1] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h-1, w);
            pr += g[1][2] * (int)pixel.cor[RED];
            pg += g[1][2] * (int)pixel.cor[GREEN];
            pb += g[1][2] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h-1, w+1);
            pr += g[1][3] * (int)pixel.cor[RED];
            pg += g[1][3] * (int)pixel.cor[GREEN];
            pb += g[1][3] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h-1, w+2);
            pr += g[1][4] * (int)pixel.cor[RED];
            pg += g[1][4] * (int)pixel.cor[GREEN];
            pb += g[1][4] * (int)pixel.cor[BLUE];
         //--------------------------------------
            pixel = obtemPixel(copy, h, w-2);
            pr += g[2][0] * (int)pixel.cor[RED];
            pg += g[2][0] * (int)pixel.cor[GREEN];
            pb += g[2][0] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h, w-1);
            pr += g[2][1] * (int)pixel.cor[RED];
            pg += g[2][1] * (int)pixel.cor[GREEN];
            pb += g[2][1] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h, w);
            pr += g[2][2] * (int)pixel.cor[RED];
            pg += g[2][2] * (int)pixel.cor[GREEN];
            pb += g[2][2] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h, w+1);
            pr += g[2][3] * (int)pixel.cor[RED];
            pg += g[2][3] * (int)pixel.cor[GREEN];
            pb += g[2][3] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h, w+2);
            pr += g[2][4] * (int)pixel.cor[RED];
            pg += g[2][4] * (int)pixel.cor[GREEN];
            pb += g[2][4] * (int)pixel.cor[BLUE];

         //----------------------------------------
            pixel = obtemPixel(copy, h-1, w-2);
            pr += g[3][0] * (int)pixel.cor[RED];
            pg += g[3][0] * (int)pixel.cor[GREEN];
            pb += g[3][0] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h-1, w-1);
            pr += g[3][1] * (int)pixel.cor[RED];
            pg += g[3][1] * (int)pixel.cor[GREEN];
            pb += g[3][1] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h-1, w);
            pr += g[3][2] * (int)pixel.cor[RED];
            pg += g[3][2] * (int)pixel.cor[GREEN];
            pb += g[3][2] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h-1, w+1);
            pr += g[3][3] * (int)pixel.cor[RED];
            pg += g[3][3] * (int)pixel.cor[GREEN];
            pb += g[3][3] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h-1, w+2);
            pr += g[3][4] * (int)pixel.cor[RED];
            pg += g[3][4] * (int)pixel.cor[GREEN];
            pb += g[3][4] * (int)pixel.cor[BLUE];
         //-------------------------------------------
         pixel = obtemPixel(copy, h-2, w-2);
            pr += g[4][0] * (int)pixel.cor[RED];
            pg += g[4][0] * (int)pixel.cor[GREEN];
            pb += g[4][0] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h-2, w-1);
            pr += g[4][1] * (int)pixel.cor[RED];
            pg += g[4][1] * (int)pixel.cor[GREEN];
            pb += g[4][1] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h-2, w);
            pr += g[4][2] * (int)pixel.cor[RED];
            pg += g[4][2] * (int)pixel.cor[GREEN];
            pb += g[4][2] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h-2, w+1);
            pr += g[4][3] * (int)pixel.cor[RED];
            pg += g[4][3] * (int)pixel.cor[GREEN];
            pb += g[4][3] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h-2, w+2);
            pr += g[4][4] * (int)pixel.cor[RED];
            pg += g[4][4] * (int)pixel.cor[GREEN];
            pb += g[4][4] * (int)pixel.cor[BLUE];

         // Matriz de M[3][3] abaixo :
         //------------------------------------------
         
            pixel = obtemPixel(copy, h-2, w-2);
            pr1 = m[0][0] * (int)pixel.cor[RED];
            pg1 = m[0][0] * (int)pixel.cor[GREEN];
            pb1 = m[0][0] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h-2, w-1);
            pr1 += m[0][1] * (int)pixel.cor[RED];
            pg1 += m[0][1] * (int)pixel.cor[GREEN];
            pb1 += m[0][1] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h-2, w);
            pr1 += m[0][2] * (int)pixel.cor[RED];
            pg1 += m[0][2] * (int)pixel.cor[GREEN];
            pb1 += m[0][2] * (int)pixel.cor[BLUE];
         //---------------------------------------
            pixel = obtemPixel(copy, h-1, w-2);
            pr1 += m[1][0] * (int)pixel.cor[RED];
            pg1 += m[1][0] * (int)pixel.cor[GREEN];
            pb1 += m[1][0] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h-1, w-1);
            pr1 += m[1][1] * (int)pixel.cor[RED];
            pg1 += m[1][1] * (int)pixel.cor[GREEN];
            pb1 += m[1][1] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h-1, w);
            pr1 += m[1][2] * (int)pixel.cor[RED];
            pg1 += m[1][2] * (int)pixel.cor[GREEN];
            pb1 += m[1][2] * (int)pixel.cor[BLUE];
         //--------------------------------------
            pixel = obtemPixel(copy, h, w-2);
            pr1 += m[2][0] * (int)pixel.cor[RED];
            pg1 += m[2][0] * (int)pixel.cor[GREEN];
            pb1 += m[2][0] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h, w-1);
            pr1 += m[2][1] * (int)pixel.cor[RED];
            pg1 += m[2][1] * (int)pixel.cor[GREEN];
            pb1 += m[2][1] * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copy, h, w);
            pr1 += m[2][2] * (int)pixel.cor[RED];
            pg1 += m[2][2] * (int)pixel.cor[GREEN];
            pb1 += m[2][2] * (int)pixel.cor[BLUE];
         //----------------------------------------

            //contas da matriz G[5][5]
            int conta1 = -pr/256;
            int conta2 = -pg/256;
            int conta3 = -pb/256;

         //Condiçoes para nao ultrapassar os limites:
            // Matriz M
            if(pr1 < 0)
                pr1 = 0; 
            if(pr1 > 255)
                pr1 = 255;
            
            if(pg1 < 0)
                pg1 = 0; 
            if(pg1 > 255)
                pg1 = 255;

            if(pb1 < 0)
                pb1 = 0; 
            if(pb1 > 255)
                pb1 = 255;
         
            // Matriz G

            if(conta1 < 0)
                conta1 = 0; 
            if(conta1 > 255)
                conta1 = 255;
            
            if(conta2 < 0)
                conta2 = 0; 
            if(conta2 > 255)
                conta2 = 255;

            if(conta3 < 0)
                conta3 = 0; 
            if(conta3 > 255)
                conta3 = 255;

             //-----------------------
             //Comparaçao de cor mais escura

            if(conta1 < pr1)
                pixel.cor[RED] = (Byte)conta1;
            else
                pixel.cor[RED] = (Byte)pr1;

            if(conta2 < pg1)
                pixel.cor[GREEN] = (Byte)conta2;
            else
                pixel.cor[GREEN] = (Byte)pg1;
            
            if(conta3 < pb1)
                pixel.cor[BLUE] = (Byte)conta3;
            else
                pixel.cor[BLUE] = (Byte)pb1;
                

            recolorePixel(img, h, w, pixel);


        }
    }
    liberaImagem(copy);
    
}