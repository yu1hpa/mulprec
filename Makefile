COMPILER=clang
CFLAGS=-Wall -DPI -O3
all:
	$(COMPILER) $(CFLAGS) -o a.out pi.c mulprec.c -lm

