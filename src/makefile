
build: 
	clear
	gcc -Wall main.c router.c ./utils/utils.c ./utils/logger.c ./backends/server.c ./utils/parser.c -o ../build/server

debug:
	clear
	gcc -g -Wall main.c router.c ./utils/utils.c ./utils/logger.c ./backends/server.c ./utils/parser.c -o ../build/server

run:
	sudo ../build/setup.sh
	../build/server

