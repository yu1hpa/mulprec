#include<stdio.h>
#include<stdlib.h>
#include"../../mulprec.h"
#include"../../utils.h"
#include<limits.h>
#include<assert.h>
#include<time.h>

#define NUM RAND_MAX

void init(struct Number *a, struct Number *b, struct Number *c){
    clearByZero(a);
    clearByZero(b);
    clearByZero(c);
}

void genRandom(int *aRnd, int *bRnd){
    *aRnd = random() % NUM;
    *bRnd = random() % NUM;
}

int main(int argc, char **argv){
    srandom(time(NULL));
    struct Number a, b, c;
    int aRnd = 0; int bRnd = 0; int c_i = 0;
    for (int i = 0; i < TEST_COUNT; i++){
        init(&a, &b, &c);
        genRandom(&aRnd, &bRnd);
        setInt(&a, aRnd);
        setInt(&b, bRnd);
        sub(&a, &b, &c);
        c_i = mulprec2Num(&c);
        assert(c_i == (aRnd - bRnd));
    }

    for (int i = 0; i < TEST_COUNT; i++){
        init(&a, &b, &c);
        genRandom(&aRnd, &bRnd);
        int maRnd = -aRnd;
        int mbRnd = -bRnd;
        setInt(&a, maRnd);
        setInt(&b, mbRnd);
        sub(&a, &b, &c);
        c_i = mulprec2Num(&c);
        assert(c_i == (maRnd - mbRnd));
    }

    for (int i = 0; i < TEST_COUNT; i++){
        init(&a, &b, &c);
        genRandom(&aRnd, &bRnd);
        int maRnd = -aRnd;
        setInt(&a, maRnd);
        setInt(&b, bRnd);
        sub(&a, &b, &c);
        c_i = mulprec2Num(&c);
        assert(c_i == (maRnd - bRnd));
    }

    for (int i = 0; i < TEST_COUNT; i++){
        init(&a, &b, &c);
        genRandom(&aRnd, &bRnd);
        int mbRnd = -bRnd;
        setInt(&a, aRnd);
        setInt(&b, mbRnd);
        sub(&a, &b, &c);
        c_i = mulprec2Num(&c);
        assert(c_i == (aRnd - mbRnd));
    }
}
