FS_DIR := ../fs/
OUT_DIR:=../build/
build: 
	clear
	git submodule update --init --recursive
	$(MAKE) -C $(FS_DIR)
	mkdir -p $(OUT_DIR)
	gcc -Wall main.c router.c ./utils/utils.c ./utils/logger.c ./backends/server.c ./utils/parser.c -I$(FS_DIR)src/include/ -L$(FS_DIR)bin -lfs -lmagic -o $(OUT_DIR)/server

debug:
	clear
	gcc -g -Wall main.c router.c ./utils/utils.c ./utils/logger.c ./backends/server.c ./utils/parser.c -o ../build/server

run:
	cd ../build/ && ./run.sh

clean:
	rm -f vgcore.*
