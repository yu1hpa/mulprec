#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "mulprec.h"

void clearByZero(struct Number *a){
    for (int i = 0; i < KETA; i++){
        a->n[i] = 0;
    }
    a->sign = 1;
}

/*
 * もし、signが1なら+ を先頭に表示
 *            -1なら- を先頭に表示
 */
void putSign(struct Number *a){
    a->sign != 1? printf("-") : printf("+");
}
