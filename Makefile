CC=gcc

# Source file de modificat
SRC=main.c functii.c

# Executable file
EXEC=clasament

# Default target
all: build

# -lm pentru math.h
build: $(SRC)
	$(CC) -g -o $(EXEC) $^ -lm

run:
	./$(EXEC) team.in graf.out score.out

clean:
	rm -f $(EXEC)