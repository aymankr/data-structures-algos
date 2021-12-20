CFLAGS = --std=c11 -g -Wall -Wextra -pedantic -fsanitize=address
LDFLAGS = -fsanitize=address
main: main.o file.o
main.o: file.h
file.o: file.h

clean:
	rm -f *.o main