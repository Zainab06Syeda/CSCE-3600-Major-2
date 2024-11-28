CC = gcc
CFLAGS = -Wall -g
OBJ = main.o builtin.o history.o

my_shell: $(OBJ)
	$(CC) $(OBJ) -o my_shell

main.o: main.c shell.h
	$(CC) $(CFLAGS) -c main.c

builtin.o: builtin.c shell.h
	$(CC) $(CFLAGS) -c builtin.c

history.o: history.c shell.h
	$(CC) $(CFLAGS) -c history.c

clean:
	rm -f *.o my_shell
