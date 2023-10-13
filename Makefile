run:compile
	./X-and-0
compile:
	gcc -o X-and-0 main.c -lncurses
clean: 
	rm X-and-0
