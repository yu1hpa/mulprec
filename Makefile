COMPILER=gcc
CFLAGS=-Wall -DPI -O2
all:
	$(COMPILER) $(CFLAGS) -o a.out pi.c mulprec.c -lm

