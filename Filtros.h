/* 
 * DCE05968 - Estruturas de Dados I
 *
 * Interface para uso do modulo Filtros
 */

#ifndef FILTRO_H
#define FILTRO_H

/* Tipos e protótipos de funções que manipulam imagens */
#include "Imagem.h"

void escurecerImagem(Imagem *img);

void clarearImagem(Imagem *img);

void escalaDeCinzaImagem(Imagem *img);

void filtroSobel(Imagem *img);

void deteccaoBordasLaplace(Imagem *img);

void meuFiltro(Imagem *img);

#endif /* FILTRO_H */