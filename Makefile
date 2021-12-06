
EXECUTAVEL=EP1

CC     = gcc
CFLAGS = -O0 -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow 
GLLIB = -lm -lGL -lGLU -lglut

all: $(EXECUTAVEL)

$(EXECUTAVEL): main.o Imagem.o Grafico.o Filtros.o
	@echo Criando arquivo executável: $@
	@$(CC) main.o Imagem.o Filtros.o Grafico.o $(GLLIB) -o $(EXECUTAVEL) 

main.o: main.c
	@echo Compilando arquivo objeto: $@
	@$(CC) $(CFLAGS) -c main.c

Imagem.o: Imagem.c
	@echo Compilando arquivo objeto: $@
	@$(CC) $(CFLAGS) -c Imagem.c 

Grafico.o: Grafico.c
	@echo Compilando arquivo objeto: $@
	@$(CC) $(CFLAGS) -c Grafico.c 

Filtros.o: Filtros.c
	@echo Compilando arquivo objeto: $@
	@$(CC) $(CFLAGS) -c Filtros.c 

run: $(EXECUTAVEL)
	./$(EXECUTAVEL) boy.ppm

memcheck: $(EXECUTAVEL) 
	valgrind --tool=memcheck --leak-check=full ./$(EXECUTAVEL) boy.ppm

.PHONY: clean
clean:
	rm -f $(EXECUTAVEL) *.o