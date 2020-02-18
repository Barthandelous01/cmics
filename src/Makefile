CC = gcc
CCFLAGS = -O3 -lncurses -lcurl

.DEFAULT_GOAL := cmics
.PHONY : config install debug clean

config:
	../scripts/config

install:
	../scripts/install

debug:
	gcc -lncurses -lcurl -ggdb main.c -o cmics

clean:
	rm -rf ../../cmics

cmics: main.c
	$(CC) $(CCFLAGS) main.c -o cmics
