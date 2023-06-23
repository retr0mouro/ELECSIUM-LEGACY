CFLAGS=-Wall -Wextra -pedantic -O2
LIBS=-lm -lcurses -lcsfml-audio


# List of source files
SOURCES = main.c estado.c music.c mobs.c menus.c luz.c mapa.c movimento.c game.c


# List of object files
OBJECTS = $(SOURCES:.c=.o)

# Output executable
EXECUTABLE = game

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
