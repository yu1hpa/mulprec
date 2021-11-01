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

void setRnd(struct Number *a, int k){
    if (k > KETA) exit(0);
    for (int i = k-1; i >= 0; i--){
        int rndnum = random()%10;
        a->n[i] = rndnum;
    }
}

void dispNumber(struct Number *a) {
    putSign(a);
    for (int i = KETA - 1; i >= 0; i--) {
        printf("%2d", a->n[i]);
    }
    puts("");
}

void dispNumberZeroSuppress(struct Number *a){
    putSign(a);
   for (int i = KETA - 1; i >= 0; i--){
        if(a->n[i] != 0) printf("%2d", a->n[i]);
    }
    puts("");
}

void copyNumber(struct Number *a, struct Number *b){
    *b = *a;
}

void getAbs(struct Number *a, struct Number *b){
    *b = *a;
    b->sign = 1;
}

int isZero(struct Number *a){
    for(int keta = KETA - 1; keta >= 0; keta--){
        if(a->n[keta] != 0){
            return -1;
            break;
        }
    }
    return 0;
}
