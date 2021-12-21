CFLAGS= -std=c11 -Wall -Wextra -pedantic -g
LDFLAGS=

ALL: googletest gtest_queue

# dependencies
queue.o: queue.c queue.h

gtest_queue: gtest_queue.o queue.o
	g++ -pthread -std=c++11 gtest_queue.o queue.o -o gtest_queue -L./googletest/build/lib -lgtest
gtest_queue.o: gtest_queue.cpp queue.h
	g++ -pthread -std=c++11 -I./googletest/googletest/include -g -c gtest_queue.cpp

gtest: gtest_queue
	./gtest_queue

googletest:
	(git clone git://github.com/google/googletest.git ; cd googletest ; mkdir build ; cd build ; cmake .. ; make)

clean:
	rm -f *.o gtest_queue
	rm -rf ./googletest








#CFLAGS = --std=c11 -g -Wall -Wextra -pedantic -fsanitize=address
#LDFLAGS = -fsanitize=address
#main: main.o list.o
#main.o: list.h
#list.o: list.h

#clean:
#	rm -f *.o main