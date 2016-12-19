GCC = gcc -g

all: server client

server: server.c pipe_networking.c
	$(GCC) server.c pipe_networking.c -o server

client: client.c pipe_networking.c
	$(GCC) client.c pipe_networking.c -o client

runs: server
	./server

runc: client
	./client
clean: 
	rm *.c
	rm *~
