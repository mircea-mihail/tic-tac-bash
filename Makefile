run:compile
	./x-and-0
compile:
	gcc -o x-and-0 main.c gameLogic.c -lncurses
clean: 
	rm x-and-0
