#include<stdio.h>
#include<stdlib.h>
#include"../../mulprec.h"
#include"../../utils.h"
#include<limits.h>
#include<assert.h>
#include<time.h>

//桁数
#define NUM RAND_MAX

void init(struct Number *a, struct Number *b, struct Number *c, struct Number *d){
    clearByZero(a);
    clearByZero(b);
    clearByZero(c);
    clearByZero(d);
}

void genRandom(int *aRnd, int *bRnd){
    *aRnd = random() % NUM;
    *bRnd = random() % 9 + 1;
}

int main(int argc, char **argv){
    srandom(time(NULL));
    struct Number a, b, c, d;
    int aRnd = 0; int bRnd = 0; int c_i = 0; int d_i = 0;
    for (int i = 0; i < TEST_COUNT; i++){
        init(&a, &b, &c, &d);
        genRandom(&aRnd, &bRnd);
        setInt(&a, aRnd);
        setInt(&b, bRnd);
        fastdivide(&a, &b, &c, &d);
        c_i = mulprec2Num(&c);
        d_i = mulprec2Num(&d);
        assert(c_i == (aRnd / bRnd));
        assert(d_i == (aRnd % bRnd));
    }

    for (int i = 0; i < TEST_COUNT; i++){
        init(&a, &b, &c, &d);
        genRandom(&aRnd, &bRnd);
        int maRnd = -aRnd;
        int mbRnd = -bRnd;
        setInt(&a, maRnd);
        setInt(&b, mbRnd);
        fastdivide(&a, &b, &c, &d);
        c_i = mulprec2Num(&c);
        d_i = mulprec2Num(&d);
        assert(c_i == (maRnd / mbRnd));
        assert(d_i == (maRnd % mbRnd));
    }

    for (int i = 0; i < TEST_COUNT; i++){
        init(&a, &b, &c, &d);
        genRandom(&aRnd, &bRnd);
        int maRnd = -aRnd;
        setInt(&a, maRnd);
        setInt(&b, bRnd);
        fastdivide(&a, &b, &c, &d);
        c_i = mulprec2Num(&c);
        d_i = mulprec2Num(&d);
        assert(c_i == (maRnd / bRnd));
        assert(d_i == (maRnd % bRnd));
    }

    for (int i = 0; i < TEST_COUNT; i++){
        init(&a, &b, &c, &d);
        genRandom(&aRnd, &bRnd);
        int mbRnd = -bRnd;
        setInt(&a, aRnd);
        setInt(&b, mbRnd);
        fastdivide(&a, &b, &c, &d);
        c_i = mulprec2Num(&c);
        d_i = mulprec2Num(&d);
        assert(c_i == (aRnd / mbRnd));
        assert(d_i == (aRnd % mbRnd));
    }
}
