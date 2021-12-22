CFLAGS= -std=c11 -Wall -Wextra -pedantic -g  -D_XOPEN_SOURCE=700 -fsanitize=address -fno-omit-frame-pointer
LDFLAGS = -fsanitize=address -fno-omit-frame-pointer

ALL: googletest gtest_queue gtest_list

# dependencies
queue.o: queue.c queue.h
list.o: list.c list.h
personne.o : personne.c personne.h

gtest_queue: queue.o personne.o gtest_queue.cpp
	g++ -pthread -std=c++11 -g -fsanitize=address -fno-omit-frame-pointer gtest_queue.cpp queue.o personne.o -o gtest_queue -I./googletest/googletest/include -L./googletest/build/lib -lgtest

gtest_list: list.o personne.o gtest_list.cpp
	g++ -pthread -std=c++11 -g -fsanitize=address -fno-omit-frame-pointer gtest_list.cpp list.o personne.o -o gtest_list -I./googletest/googletest/include -L./googletest/build/lib -lgtest

test_queue: test_queue.o queue.o

googletest:
	(git clone git://github.com/google/googletest.git ; cd googletest ; mkdir build ; cd build ; cmake .. ; make)

clean:
	rm -f *.o gtest_queue

gclean: clean
	rm -rf ./googletest


#CFLAGS= -std=c11 -Wall -Wextra -pedantic -g  -D_XOPEN_SOURCE=700 -fsanitize=address -fno-omit-frame-pointer
#LDFLAGS = -fsanitize=address -fno-omit-frame-pointer
#main: main.o list.o
#main.o: list.h
#list.o: list.h

#clean:
#	rm -f *.o main