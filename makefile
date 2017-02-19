CC= gcc -ansi -pedantic -Wall 

main: main.c print_ppm.c print_functions.c
	$(CC) -o autostereogram.out main.c print_ppm.c print_functions.c
