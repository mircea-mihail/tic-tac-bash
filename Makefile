run:compile
	./tic-tac-bash
install:compile
	sudo mv tic-tac-bash /usr/local/bin
compile:
	gcc -Wall -o tic-tac-bash main.c gameLogic.c printing.c ai.c -lncurses
clean: 
	rm tic-tac-bash
