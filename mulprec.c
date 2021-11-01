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

int mulBy10(struct Number *a, struct Number *b){
    if (a->n[KETA - 1] != 0) return -1;
    for(int keta = 0; keta < KETA; keta++){
        b->n[keta+1] = a->n[keta];
    }
    b->n[0] = 0;
    b->sign = a->sign;
    return 0;
}

int divBy10(struct Number *a, struct Number *b){
    for(int keta = 0; keta < KETA; keta++){
        b->n[keta] = a->n[keta+1];
    }
    b->n[KETA-1] = 0;
    b->sign = a->sign;
    return a->n[0];
}

int setInt(struct Number *a, int x){
    int i, m;
    if (x < 0) {
        a->sign = -1;
        x = -x;
    }
    for(i = 0; i < KETA; i++){
        m = x % 10;
        a->n[i] = m;
        x = (x - m) / 10;
    }
    if (x != 0) return -1;
    else return 0;
}

int setSign(struct Number *a, int s){
    if (a->n[0] != 0){
        if (s == -1) a->sign = -1;
        else if (s == 1) a->sign = 1;
        else return -1;
    } else {
        a->sign = 1;
        return 0;
    }
    return 0;
}

int getSign(struct Number *a){
    if (a->sign == 1) return 1;
    else return -1;
}

int numComp(struct Number *a, struct Number *b){
    if (a->sign > b->sign) return 1;
    else if (a->sign < b->sign) return -1;
    else if (a->sign == 1 && b->sign == 1) {
        for (int keta = KETA - 1; keta >= 0; keta--) {
            if (a->n[keta] > b->n[keta]) return 1;
            else if (a->n[keta] < b->n[keta]) return -1;
        }
    }
    else if (a->sign == -1 && b->sign == -1) {
        for (int keta = KETA - 1; keta >= 0; keta--) {
            if (a->n[keta] < b->n[keta]) return 1;
            else if (a->n[keta] > b->n[keta]) return -1;
        }
    }
    return 0;
}
