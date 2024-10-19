CC = g++

CFLAGS = -Wall -Werror -std=c++23

main: main.o
	$(CC) $(CFLAGS) -o main.out main.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm -f main.out *.o


