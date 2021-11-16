#include<stdio.h>
#include<stdlib.h>
#include"../../mulprec.h"
#include"../../utils.h"
#include<limits.h>
#include<assert.h>

#define NUM 3

int main(int argc, char **argv){
    struct Number a, b, c;
    int a_i, b_i, c_i = 0;
    for (int i = 0; i < TEST_COUNT; i++){
        clearByZero(&a);
        clearByZero(&b);
        clearByZero(&c);
        setRnd(&a, NUM);
        setRnd(&b, NUM);
        a_i = mulprec2Num(&a);
        b_i = mulprec2Num(&b);
        multiple(&a, &b, &c);
        c_i = mulprec2Num(&c);
        assert(c_i == (a_i * b_i));
    }
}
