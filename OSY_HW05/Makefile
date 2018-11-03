CC=gcc
CFLAGS=-Wall -g

prod-cons: prod-cons.c
	${CC} ${CFLAGS} $< -o $@ -D_REENTRANT -lpthread
	