CC=gcc
CFLAGS=-Wall -I.
LIBS=-lglut -lGLU -lGL -lm

SRC=$(wildcard *.c)

all: clean run

run: out
	./$<

out: $(SRC)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	@if [[ -f ./out ]]; then\
		rm ./out;\
	fi
