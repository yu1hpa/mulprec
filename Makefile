all:
	gcc -Wall -o a.out check2.c mulprec.c utils.c -lm

unittest:
	gcc -Wall -o ./test/a.out ./test/unittest/multiple_test.c mulprec.c utils.c -lm

