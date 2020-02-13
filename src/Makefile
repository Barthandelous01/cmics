CC = gcc
CCFLAGS = -O3 -lncurses -lcurl

.DEFAULT_GOAL := cmics
.PHONY : config install

config:
	../scripts/config

install:
	../scripts/install

cmics: main.c
	$(CC) $(CCFLAGS) main.c -o cmics
