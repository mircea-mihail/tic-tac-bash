run:compile
	./tic-tac-bash
compile:
	gcc -o tic-tac-bash main.c gameLogic.c printing.c -lncurses
clean: 
	rm tic-tac-bash
