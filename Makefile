CFLAGS = --std=c11 -g -Wall -Wextra -pedantic -fsanitize=address
LDFLAGS = -fsanitize=address
main: main.o queue.o
main.o: queue.h
queue.o: queue.h

clean:
	rm -f *.o main