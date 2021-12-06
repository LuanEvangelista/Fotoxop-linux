/* 
 * DCE05968 - Estruturas de Dados I
 *
 * Interface para uso do modulo Imagem
 * 
 * Neste EP, armazenaremos as imagens utilizaremos True Color (24 bits)
 * https://en.wikipedia.org/wiki/Color_depth#True_color_(24-bit)
 * 
 * Cada cor (de um pixel) é decomposta nas componentes básicas 
 * red (vermelho), green (verde) e blue (azul) ou RGB.
 * 
 */

#ifndef IMAGEM_H
#define IMAGEM_H

/*
 * Note que alguns enum's e struct's foram definidos no arquivo Imagem.h
 * Isso significa que arquivos externos podem acessar cada campo do struct. 
 * Essa decisão foi feita para facilitar a implementação de algumas funções. 
 * Por exemplo, o 'enum Cores' estando no arquivo Imagem.h permite que qualquer 
 * outro arquivo que inclua o arquivo Imagem.h possa usá-lo. O mesmo acontece 
 * com o 'enum bool'. 
 */

/* defines auxiliares para exibir mensagens e erros durante a execução do programa */
#define AVISO(msg) fprintf(stdout, "AVISO: %s\n", #msg)
#define ERRO(msg) fprintf(stderr, "ERRO: %s\n", #msg)

/* enum para facilitar o acesso (indice) a cada canal de cor da imagem */
enum Cores {
    RED   /* = 0 */,
    GREEN /* = 1 */,
    BLUE  /* = 2 */
};

/* enum para a criação de variáveis do tipo 'bool' */
typedef enum {
    false,
    true
} bool;

/* Byte = valores entre 0 e 255 (8 bits) */
typedef unsigned char Byte;

/* Um pixel é formado pela combinação de 3 cores: vemelho (R), verde (B), azul (B)*/
/* Supondo que a variável que armazena um pixel se chama 'pixel', para acessar cada 
 * canal de uma cor, basta fazer: 
 * pixel.cor[RED] para acessar a intensidade de vermelho do pixel
 * pixel.cor[GREEN] para acessar a intensidade de verde do pixel
 * pixel.cor[BLUE] para acessar a intensidade de azul do pixel
 * Note que o campo 'cor' é do tipo Byte (unsigned char - 8bits). Assim, ele pode armazenar 
 * valores entre 0 e 255.
*/
typedef struct pixel {
     Byte cor[3];
     /* cor[RED]   eh um valor entre 0 e 255 */
     /* cor[GREEN] eh um valor entre 0 e 255 */
     /* cor[BLUE]  eh um valor entre 0 e 255*/
} Pixel;

typedef struct imagem Imagem;

Imagem* alocaImagem(int largura, int altura);

void liberaImagem(Imagem *img);

int obtemLargura(Imagem *img);

int obtemAltura(Imagem *img);

Pixel obtemPixel(Imagem *img, int l, int c);

void recolorePixel(Imagem *img, int l, int c, Pixel pixel);

Imagem* copiaImagem(Imagem *origem);

Imagem *carregaImagem(const char *nomeArquivo);

void salvaImagem(Imagem *img, const char *nomeArquivo);

#endif /* IMAGEM_H */