CFLAGS=-Wall -Wextra -pedantic -O2
LIBS=-lm -lcurses -lcsfml-audio

jogo: main.o
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

clean:
	rm jogo *.o
