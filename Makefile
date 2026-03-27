CC = gcc
CFLAGS = -Wall -Wextra -pthread
OBJ = main.o geral.o operacoesThreads.o
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) -pthread

main.o: main.c geral.h
	$(CC) $(CFLAGS) -c main.c

geral.o: geral.c geral.h
	$(CC) $(CFLAGS) -c geral.c

operacoesThreads.o: operacoesThreads.c operacoesThreads.h
	$(CC) $(CFLAGS) -c operacoesThreads.c	

clean:
	rm -f *.o $(TARGET)