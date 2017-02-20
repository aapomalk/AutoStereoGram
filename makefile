CC= gcc -ansi -pedantic -Wall 

main: main.c read_and_print_functions.c make_stereogram.c
	$(CC) -o autostereogram.out main.c read_and_print_functions.c make_stereogram.c
