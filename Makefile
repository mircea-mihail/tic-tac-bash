run:compile
	./tic-tac-bash
compile:
	gcc -Wall -o tic-tac-bash main.c gameLogic.c printing.c -lncurses
clean: 
	rm tic-tac-bash
