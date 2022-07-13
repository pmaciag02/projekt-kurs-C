main : main.c

	gcc -std=c11 -Wall -o main  main.c $(shell pkg-config gtk+-3.0 --cflags --libs)
