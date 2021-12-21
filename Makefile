CFLAGS = --std=c11 -g -Wall -Wextra -pedantic -fsanitize=address
LDFLAGS = -fsanitize=address
main: main.o list.o
main.o: list.h
list.o: list.h

clean:
	rm -f *.o main