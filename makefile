FILES=main.c


build:
	clear
	gcc -Wall main.c utils.c logger.c server.c parser.c -o server

run:
	sudo ./setup.sh
	./server

