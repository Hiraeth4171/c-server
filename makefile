FILES=main.c


build: 
	gcc -Wall main.c utils.c logger.c server.c iniparser.h -o server

run: 
	./server

