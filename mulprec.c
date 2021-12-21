#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>
#include<math.h>
#include<string.h>
#include "mulprec.h"

// 基数
#define RADIX 1000000000
#define RADIX_KETA (int)log10(RADIX)

#define MEMO_SIZE 10000


struct Number N1;
struct Number N2;

// グローバル変数だから0で初期化済み
struct Number ZERO;

void initNumber(){
    clearByZero(&N1); clearByZero(&N2);
    setInt(&N1, 1);
    setInt(&N2, 2);
}

// 配列をゼロで初期化
void clearByZero(struct Number *a){
    setSign(&ZERO, 1);
    memcpy(a, &ZERO, sizeof(ZERO));
}

/*
 * もし、signが1なら+ を先頭に表示
 *            -1なら- を先頭に表示
 */
void putSign(struct Number *a){
    a->sign != 1? printf("-") : printf("+");
}

// ランダムに値を生成して配列にセット
void setRnd(struct Number *a, int k){
    if (k > KETA) exit(0);
    for (int i = k-1; i >= 0; i--){
        int rndnum = random()%10;
        a->n[i] = rndnum;
    }
    // 下一桁が2で割り切れたら+にセット
    // 割り切れなければ-にセット
    if (a->n[0] % 2 == 0) a->sign = 1;
    else a-> sign = -1;
}

// 配列を表示
void dispNumber(struct Number *a) {
    putSign(a);
    for (int i = KETA - 1; i >= 0; i--) {
        printf("%09llu", a->n[i]);
    }
    puts("");
}


void dispNumberZeroSuppress(struct Number *a){
    putSign(a);
   for (int i = KETA - 1; i >= 0; i--){
        if(a->n[i] != 0) printf("%09llu", a->n[i]);
    }
    puts("");
}

/*
 * copyNumber(a, b)
 * 第一引数を第二引数にコピー
 * */
void copyNumber(struct Number *a, struct Number *b){
    *b = *a;
}

/*
 * 第一引数の絶対値を取って
 * 第二引数のポインタにコピーする
 */
void getAbs(struct Number *a, struct Number *b){
    *b = *a;
    b->sign = 1;
}

/*
 * ポインタのデータがゼロかどうか
 * ゼロでなければ 0
 * そうでなければ -1
 */
int isZero(struct Number *a){
    for(int keta = KETA - 1; keta >= 0; keta--){
        if(a->n[keta] != 0){
            return -1;
            break;
        }
    }
    return 0;
}

/*
 * 第一引数で受け取ったものを
 * 10倍したものを格納した配列を第二引数で返す
 */
int mulBy10(struct Number *a, struct Number *b){
    if (a->n[KETA - 1] != 0) return -1;
    for(int keta = 0; keta < KETA; keta++){
        b->n[keta+1] = a->n[keta];
    }
    b->n[0] = 0;
    b->sign = a->sign;
    return 0;
}

/*
 * 第一引数で受け取ったものを
 * 1/10 倍したものを格納した配列を第二引数で返す
 */
int divBy10(struct Number *a, struct Number *b){
    for(int keta = 0; keta < KETA; keta++){
        b->n[keta] = a->n[keta+1];
    }
    b->n[KETA-1] = 0;
    b->sign = a->sign;
    return a->n[0];
}

/*
 * 配列に任意の値を格納する
 */
int setInt(struct Number *a, int x){
    int i, m;
    if (x < 0) {
        a->sign = -1;
        x = -x;
    }
    for(i = 0; i < KETA; i++){
        m = x % RADIX;
        a->n[i] = m;
        x = (x - m) / RADIX;
    }
    if (x != 0) return -1;
    else return 0;
}

/*
 * 任意の配列に、任意の符号をセットする
 */
int setSign(struct Number *a, int s){
    if (isZero(a) == -1){
        if (s == -1) a->sign = -1;
        else if (s == 1) a->sign = 1;
        else return -1;
    } else a->sign = 1;

    return 0;
}

/*
 * 配列の符号を取得する
 */
int getSign(struct Number *a){
    if (a->sign == 1) return 1;
    else return -1;
}

/*
 * a == b -> 0
 * a > b  -> 1
 * a < b  -> -1
 * */
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

/*
 * a + b = c
 */
int add(struct Number *a, struct Number *b, struct Number *c){
    uint_fast64_t d, e = 0;

    if (a->sign == 1 && b->sign == -1) {
        struct Number d; clearByZero(&d);
        getAbs(b, &d);
        sub(a, &d, c);
        return 0;
    } else if (a->sign == -1 && b->sign == 1) {
        struct Number d; clearByZero(&d);
        getAbs(a, &d);
        sub(b, &d, c);
        return 0;
    } else if (a->sign == -1 && b->sign == -1) {
        struct Number d, e; clearByZero(&d); clearByZero(&e);
        getAbs(a, &d); getAbs(b, &e);
        add(&d, &e, c);
        setSign(c, -1);
        return 0;
    } else {
        for (int keta = 0; keta < KETA; keta++){
            d = a->n[keta] + b->n[keta] + e;
            c->n[keta]  = d % RADIX;
            e = (d - c->n[keta])/RADIX;
        }
    }
    if (e != 0) return -1;
    else return 0;
}

/*
 * a - b = c
 * */
int sub(struct Number *a, struct Number *b, struct Number *c){
    //桁借り
    int_fast64_t ai, bi, h = 0;

    if(a->sign == 1 && b->sign == -1) {
        struct Number d; clearByZero(&d);
        getAbs(b, &d);
        if(add(a, &d, c) != 0) return -1;
        return 0;
    } else if (a->sign == -1 && b->sign == 1) {
        struct Number d; clearByZero(&d);
        getAbs(a, &d);
        if(add(b, &d, c) != 0) return -1;
        setSign(c, -1);
        return 0;
    } else if (a->sign == -1 && b->sign == -1) {
        struct Number d, e; clearByZero(&d); clearByZero(&e);
        getAbs(a, &d); getAbs(b, &e);
        sub(&e, &d, c);
        return 0;
    }
    else {
        if(numComp(a, b) == 1 || numComp(a, b) == 0){
            for(int i = 0; i < KETA; i++){
                ai = a->n[i];
                bi = b->n[i];
                ai = ai - h;
                if(ai >= bi) {
                    c->n[i] = ai - bi;
                    h = 0;
                } else {
                    c->n[i] = RADIX + ai - bi;
                    h = 1;
                }
            }
        } else {
            struct Number d; clearByZero(&d);
            sub(b, a, &d);
            d.sign = -1;
            copyNumber(&d, c);
        }
    }
    return 0;
}

/*
 * a * b = c
 */
int multiple(struct Number *a, struct Number *b, struct Number *c){
    if (getSign(a) == 1 && getSign(b) == -1) {
        struct Number d; clearByZero(&d);
        getAbs(b, &d);
        multiple(a, &d, c);
        setSign(c, -1);
        return 0;
    } else if (getSign(a) == -1 && getSign(b) == 1) {
        struct Number d; clearByZero(&d);
        getAbs(a, &d);
        multiple(b, &d, c);
        setSign(c, -1);
        return 0;
    } else if (getSign(a) == -1 && getSign(b) == -1) {
        struct Number d, e; clearByZero(&d); clearByZero(&e);
        getAbs(a, &d);
        getAbs(b, &e);
        multiple(&d, &e, c);
        return 0;
    }
    struct Number d, e; clearByZero(&d); clearByZero(&e);
    clearByZero(c); //[NOTE]: 一つ前のcをクリアする
    uint_fast64_t h = 0;
    for (int i = 0; i < KETA - 1; i++){
        h = 0;
        for (int j = 0; j < KETA - 1; j++){
            e.n[j] = (a->n[j] * b->n[i] + h) % RADIX;
            h = (a->n[j] * b->n[i] + h) / RADIX;
        }
        for(int k = i; k > 0; k--){
            mulBy10(&e, &d);
            copyNumber(&d, &e);
        }
        if (i == 0) copyNumber(&e, &d);
        struct Number t; clearByZero(&t);
        add(&d, c, &t);
        copyNumber(&t, c);
    }
    if (h != 0) return -1;
    return 0;
}

/*
 * a + 1 = b
 */
int increment(struct Number *a, struct Number *b){
    struct Number one; clearByZero(&one);
    int r;
    setInt(&one, 1);
    r = add(a, &one, b);
    return r;
}

/*
 * a / b = c...d
 */
int divide(struct Number *a, struct Number *b, struct Number *c, struct Number *d){
    struct Number n, m; clearByZero(&n); clearByZero(&m);
    copyNumber(a, &n);
    if (getSign(a) == 1 && getSign(b) == -1) {
        struct Number p; clearByZero(&p);
        getAbs(b, &p);
        divide(a, &p, c, d);
        setSign(c, -1);
        return 0;
    } else if (getSign(a) == -1 && getSign(b) == 1) {
        struct Number p; clearByZero(&p);
        getAbs(a, &p);
        divide(&p, b, c, d);
        setSign(c, -1);
        setSign(d, -1);
        return 0;
    } else if (getSign(a) == -1 && getSign(b) == -1) {
        struct Number p, q; clearByZero(&p); clearByZero(&q);
        getAbs(a, &p);
        getAbs(b, &q);
        divide(&p, &q, c, d);
        setSign(d, -1);
        return 0;
    }
    if (!isZero(b)) return -1;
    while(1) {
        if(numComp(&n, b) == -1) break;
        // n - b = m
        sub(&n, b, &m);
        copyNumber(&m, &n);

        clearByZero(&m);
        increment(c, &m);
        copyNumber(&m, c);
    }
    copyNumber(&n, d);
    return 0;
}

int power(struct Number *a, struct Number *b, struct Number *c){
    struct Number d, e, f;
    clearByZero(&d); clearByZero(&e); clearByZero(&f);
    struct Number one; clearByZero(&one);
    setInt(&one, 1);
    setInt(c, 1);
    if(!isZero(b)) {
        return 0;
    }
    if (numComp(b, &one) == 0) {
        copyNumber(a, c);
        return 0;
    }
    while (1){
        multiple(c, a, &e);
        copyNumber(&e, c);

        increment(&d, &f);
        copyNumber(&f, &d);
        if(numComp(b, &d) == 0) break;
    }
    return 0;
}

int fastpower(struct Number *a, struct Number *b, struct Number *c){
    struct Number one; clearByZero(&one);
    setInt(&one, 1);
    setInt(c, 1);

    if (!isZero(b)) {
        return 0;
    }
    if (numComp(b, &one) == 0){
        copyNumber(a, c);
        return 0;
    }

    struct Number x, y, z, w;
    clearByZero(&x); clearByZero(&y); clearByZero(&z); clearByZero(&w);
    copyNumber(b, &x);
    setInt(&y, 2);
    divide(&x, &y, &z, &w);
    //剰余が0ならば
    if (!isZero(&w)) {
        struct Number m; clearByZero(&m);
        multiple(a, a, &m);
        fastpower(&m, &z, c);
        return 0;
    }
    struct Number s, n, m;
    clearByZero(&s); clearByZero(&n); clearByZero(&m);

    sub(b, &one, &s);
    fastpower(a, &s, &n);

    multiple(a, &n, &m);
    copyNumber(&m, c);

    return 0;
}
