CC = g++
CFLAGS = -Wall -Werror -std=c++23

main: main.o request.o webserver.o loadbalancer.o
	$(CC) $(CFLAGS) -o main.out main.o request.o webserver.o loadbalancer.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

request.o: request.cpp
	$(CC) $(CFLAGS) -c request.cpp

webserver.o: webserver.cpp
	$(CC) $(CFLAGS) -c webserver.cpp

loadbalancer.o: loadbalancer.cpp
	$(CC) $(CFLAGS) -c loadbalancer.cpp

clean:
	rm -f main.out *.o
