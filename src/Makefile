
CROSS=
CC=$(CROSS)gcc
CFLAGS=-I../include
LDFLAGS = -L../lib/openssl
LIBS = -lssl -lcrypto

SRCS = hash.c symmetric.c mac.c tools.c
OBJS = $(SRCS:.c=.o)
 
all: $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

