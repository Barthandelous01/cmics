CC = gcc
CCFLAGS = -O3 -lncurses -lcurl

.DEFAULT_GOAL := cmics
.PHONY : config install debug clean clean update

config:
	../scripts/config

install:
	../scripts/install

debug:
	gcc -lncurses -lcurl -ggdb main.c -o cmics

clear:
	rm -rf ../../cmics

update:
	rm /usr/local/bin/cmics
	rm /usr/local/bin/img
	../scripts/install

clean:
	rm cmics

cmics: main.c
	$(CC) $(CCFLAGS) main.c -o cmics
