build: 
	clear
	gcc -Wall main.c router.c ./utils/utils.c ./utils/logger.c ./backends/server.c ./utils/parser.c -I../fs/src/include/ -L../fs/bin/ -lfs -lmagic -o ../build/server

debug:
	clear
	gcc -g -Wall main.c router.c ./utils/utils.c ./utils/logger.c ./backends/server.c ./utils/parser.c -o ../build/server

run:
	cd ../build/ && ./run.sh

clean:
	rm -f vgcore.*
