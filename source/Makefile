CC=gcc

all: run

run: out
	./cod

bug: out
	gdb ./cod

out:
	$(CC) -g colisao.c interacao.c movimento.c gravidade.c personagens.c cenario.c camera.c main.c -o cod -lglut -lGLU -lGL -lm

clean:
	rm cod
