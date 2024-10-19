CC = g++
CFLAGS = -Wall -Werror -std=c++23

main: main.o request.o
	$(CC) $(CFLAGS) -o main.out main.o request.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

request.o: request.cpp
	$(CC) $(CFLAGS) -c request.cpp

clean:
	rm -f main.out *.o

