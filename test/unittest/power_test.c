#include<stdio.h>
#include<stdlib.h>
#include"../../mulprec.h"
#include"../../utils.h"
#include<limits.h>
#include<assert.h>
#include<time.h>
#include<math.h>

#define NUM 10

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
        power(&a, &b, &c);
        c_i = mulprec2Num(&c);
        assert(c_i == pow(aRnd, bRnd));
    }
}
