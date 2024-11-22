
CROSS=
CC=$(CROSS)gcc
CFLAGS=-I./include
LDFLAGS = -L./lib/openssl
LIBS = -lssl -lcrypto
OBJS = main.o hash.o symmetric.o mac.o tools.o

main:$(OBJS)
	gcc $(OBJS) $(LDFLAGS) $(LIBS) -o cryptoTools
main.o:main.c
	gcc -c main.c $(CFLAGS) $(LIBS) -o main.o	
clean:
	rm -f $(OBJS)
