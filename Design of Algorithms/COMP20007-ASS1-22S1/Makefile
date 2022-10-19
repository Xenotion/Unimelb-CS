problem1a: problem1a.o leap.o utils.o
	gcc -Wall -o problem1a problem1a.o leap.o utils.o -g

problem1b: problem1b.o leap.o utils.o
	gcc -Wall -o problem1b problem1b.o leap.o utils.o -g

leap.o: leap.h utils.h leap.c
	gcc -Wall -c leap.c -g

utils.o: leap.h utils.h utils.c
	gcc -Wall -c utils.c -g

problem1a.o: utils.h problem1a.c
	gcc -Wall -c problem1a.c -g

problem1b.o: utils.h problem1b.c
	gcc -Wall -c problem1b.c -g

