#include<stdio.h>
#include"mulprec.h"
int mulprec2Num(struct Number *a){
    int num, tmp = 0;
    for(int i = 0; i < KETA - 1; i++){
        if (i == 0) num = a->n[i];
        else {
            tmp = a->n[i];
            for (int j = i; j > 0; j--) {
                tmp *= 10;
            }
        }
        num += tmp;
    }
    if (getSign(a) == -1) return -num;
    else return num;
}
