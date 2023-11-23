CC=gcc

all: run

run: out
	./cod

bug: out
	gdb ./cod

out:
	$(CC) -g gravidade.c personagem-esfera.c cenario.c camera.c main.c -o cod -lglut -lGLU -lGL -lm

clean:
	rm cod
