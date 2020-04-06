CFLAG = -DDEBUG -std=c99

main: main.o scheduler.o process.o
	gcc $(CFLAG) main.o scheduler.o process.o -o main
main.o: main.c
	gcc $(CFLAG) main.c -c
process.o: process.c process.h
	gcc $(CFLAG) process.c -c
scheduler.o: scheduler.c scheduler.h
	gcc $(CFLAG) scheduler.c -c

clean:
	rm -rf main *o
