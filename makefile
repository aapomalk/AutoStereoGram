CC= gcc -ansi -pedantic -Wall 

main: main.c print_ppm.c print_only_red.c
	$(CC) -o autostereogram.out main.c print_ppm.c print_only_red.c
