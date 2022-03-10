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

#define MEMO_SIZE 2000


struct Number N1;
struct Number N2;

// グローバル変数だから0で初期化済み
struct Number ZERO;

void initNumber(){
    setSign(&N1, 1);
    setIntToZero(&N1, 1);
    setSign(&N2, 1);
    setIntToZero(&N2, 2);
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

void copyByZero(struct Number *a){
    copyNumber(&ZERO, a);
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
        setSign(a, -1);
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

int setIntToZero(struct Number *a, int x){
    if (x > 9) {
        return -1;
    }
    if (x < 0) {
        setSign(a, -1);
        x = -x;
    }
    a->n[0] = x;
    return 0;
}

int getInt(struct Number *a, int *x){
    int tmp = 1;
    for (int i = 0; i < KETA; i++){
      *x += a->n[i] * tmp;
      tmp *= RADIX;
    }
    if (getSign(a) == -1) *x *= -1;
    return 0;
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
        struct Number d; copyByZero(&d);
        getAbs(b, &d);
        sub(a, &d, c);
        return 0;
    } else if (a->sign == -1 && b->sign == 1) {
        struct Number d; copyByZero(&d);
        getAbs(a, &d);
        sub(b, &d, c);
        return 0;
    } else if (a->sign == -1 && b->sign == -1) {
        struct Number d, e; copyByZero(&d); copyByZero(&e);
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
        struct Number d; copyByZero(&d);
        getAbs(b, &d);
        if(add(a, &d, c) != 0) return -1;
        return 0;
    } else if (a->sign == -1 && b->sign == 1) {
        struct Number d; copyByZero(&d);
        getAbs(a, &d);
        if(add(b, &d, c) != 0) return -1;
        setSign(c, -1);
        return 0;
    } else if (a->sign == -1 && b->sign == -1) {
        struct Number d, e; copyByZero(&d); copyByZero(&e);
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
            struct Number d; copyByZero(&d);
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
        struct Number d; copyByZero(&d);
        getAbs(b, &d);
        multiple(a, &d, c);
        setSign(c, -1);
        return 0;
    } else if (getSign(a) == -1 && getSign(b) == 1) {
        struct Number d; copyByZero(&d);
        getAbs(a, &d);
        multiple(b, &d, c);
        setSign(c, -1);
        return 0;
    } else if (getSign(a) == -1 && getSign(b) == -1) {
        struct Number d, e; copyByZero(&d); copyByZero(&e);
        getAbs(a, &d);
        getAbs(b, &e);
        multiple(&d, &e, c);
        return 0;
    }
    struct Number d, e; copyByZero(&d); copyByZero(&e);
    copyByZero(c); //[NOTE]: 一つ前のcをクリアする
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
        struct Number t; copyByZero(&t);
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
    int r;
    setIntToZero(&N1, 1);
    r = add(a, &N1, b);
    return r;
}

/*
 * a / b = c...d
 */
int divide(struct Number *a, struct Number *b, struct Number *c, struct Number *d){
    struct Number n, m; copyByZero(&n); copyByZero(&m);
    copyNumber(a, &n);
    if (getSign(a) == 1 && getSign(b) == -1) {
        struct Number p; copyByZero(&p);
        getAbs(b, &p);
        divide(a, &p, c, d);
        setSign(c, -1);
        return 0;
    } else if (getSign(a) == -1 && getSign(b) == 1) {
        struct Number p; copyByZero(&p);
        getAbs(a, &p);
        divide(&p, b, c, d);
        setSign(c, -1);
        setSign(d, -1);
        return 0;
    } else if (getSign(a) == -1 && getSign(b) == -1) {
        struct Number p, q; copyByZero(&p); copyByZero(&q);
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

        copyByZero(&m);
        increment(c, &m);
        copyNumber(&m, c);
    }
    copyNumber(&n, d);
    return 0;
}

int fastdivide(struct Number *a, struct Number *b, struct Number *c, struct Number *d){
    if (getSign(a) == 1 && getSign(b) == -1) {
        struct Number p; copyByZero(&p);
        getAbs(b, &p);
        fastdivide(a, &p, c, d);
        setSign(c, -1);
        return 0;
    } else if (getSign(a) == -1 && getSign(b) == 1) {
        struct Number p; copyByZero(&p);
        getAbs(a, &p);
        fastdivide(&p, b, c, d);
        setSign(c, -1);
        setSign(d, -1);
        return 0;
    } else if (getSign(a) == -1 && getSign(b) == -1) {
        struct Number p, q; copyByZero(&p); copyByZero(&q);
        getAbs(a, &p);
        getAbs(b, &q);
        fastdivide(&p, &q, c, d);
        setSign(d, -1);
        return 0;
    }
    if (!isZero(b)) return -1;
    uint_fast64_t t = 0;
    uint_fast64_t h = 0;
    uint_fast64_t _b = b->n[0];
    for (int i = KETA - 1; i >= 0; i--) {
        t = RADIX * h + a->n[i];
        h = t % _b;
        c->n[i] = (t - h) / _b;
    }
    struct Number tmp; copyByZero(&tmp);
    setInt(&tmp, h);
    copyNumber(&tmp, d);
    return 0;
}

int power(struct Number *a, struct Number *b, struct Number *c){
    struct Number d, e, f;
    copyByZero(&d); copyByZero(&e); copyByZero(&f);
    setIntToZero(&N1, 1);
    setIntToZero(c, 1);
    if(!isZero(b)) {
        return 0;
    }
    if (numComp(b, &N1) == 0) {
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
    setIntToZero(&N1, 1);
    setIntToZero(c, 1);

    if (!isZero(b)) {
        return -1;
    }
    if (numComp(b, &N1) == 0){
        copyNumber(a, c);
        return -1;
    }

    struct Number x, z, w;
    copyByZero(&x); copyByZero(&z); copyByZero(&w);
    copyNumber(b, &x);
    setIntToZero(&N2, 2);
    fastdivide(&x, &N2, &z, &w);
    //剰余が0ならば
    if (!isZero(&w)) {
        struct Number m; copyByZero(&m);
        multiple(a, a, &m);
        fastpower(&m, &z, c);
        return 0;
    }
    struct Number s, n, m;
    copyByZero(&s); copyByZero(&n); copyByZero(&m);

    sub(b, &N1, &s);
    fastpower(a, &s, &n);

    multiple(a, &n, &m);
    copyNumber(&m, c);

    return 0;
}

int shiftTo(int shift, struct Number *a){
    a->n[shift] = 1;
    return 0;
}


/**
 * isOdd(struct Number *)
 * 奇数 return 1
 * 偶数 return 0
 */
int isOdd(struct Number *a){
    if(a->n[0] % 2 != 0){
        return 1;
    }
    return 0;
}

/**
 * fastpowdiv(struct Number *, struct Number *, struct Number *, struct Number *, struct Number *)
 * nmax : p = {2, 5, 8}，p^{2n} < RADIXを満たす最大のn
 */
struct Number memo[MEMO_SIZE];
void fastpowdiv(struct Number *p, struct Number *q, struct Number *quo, struct Number *nmax, struct Number *a){
    struct Number _, i; copyByZero(&i); copyByZero(&_);
    struct Number _m; copyByZero(&_m);
    struct Number n1, n2, _n2; copyByZero(&n1); copyByZero(&n2); copyByZero(&_n2);
    // q < nmax
    int _q = 0;
    getInt(q, &_q);
    if (isZero(&memo[_q]) != 0){
        copyNumber(&memo[_q], &i);
        fastdivide(quo, &i, a, &_);
    } else if (numComp(q, nmax) == -1){
        fastpower(p, q, &i);
        copyNumber(&i, &memo[_q]);
        fastdivide(quo, &memo[_q], a, &_);
    } else {
        if (isOdd(q)){
            fastdivide(q, &N2, &n1, &_);
            copyNumber(&n1, &_n2);
            increment(&_n2, &n2);
        } else {
            fastdivide(q, &N2, &n1, &_);
            copyNumber(&n1, &n2);
        }
        struct Number _a; copyByZero(&_a);
        fastpowdiv(p, &n1, quo, nmax, &_a);
        fastpowdiv(p, &n2, &_a, nmax, a);
    }
}

void commonForArctan(int *n, struct Number *p, struct Number *a, struct Number *nmax){
    struct Number _2n, q, h, i, j, k,
                  quo, _,
                  _n, _q, P2;

    copyByZero(&_2n); copyByZero(&q);
    copyByZero(&h); copyByZero(&i); copyByZero(&j); copyByZero(&k);
    copyByZero(&quo); copyByZero(&_);
    copyByZero(&_n);copyByZero(&_q);
    copyByZero(&P2);

    initNumber();

    shiftTo(KETA-2, &h);
    setInt(&_n, *n);
    multiple(&_n, &N2, &_2n); // 2 * n
    add(&_2n, &N1, &q); // 2n + 1 = q
    fastdivide(&h, &q, &quo, &_); // h / (2n + 1)

    fastdivide(&quo, p, a, &k); // (h / (2n + 1)) / p = a...k

    fastpower(p, &N2, &P2); // p^2
    fastpowdiv(&P2, &_n, a, nmax, &j); // a / ((p^2) ^ n) = j (n < nmax)
    copyNumber(&j, a);

    if(isOdd(&_n)){
        setSign(a, -1);
    } else {
        setSign(a, 1);
    }
}


/*
  int arctan(struct Number *, struct Number *, struct Number *)

  - q = 2n + 1
  - 0 <= n <= INF

  arctan(x) = (-1) ^ n / q * (x ^ q) for |x| < 1

  実装の方針
  x = 1/pとおく
  arctan(1/p) = (-1)^ n / q * (p^q) for |1/p| < 1

*/
int arctan(struct Number *p, struct Number *a, struct Number *nmax){
    /*
     * old : 一つ前の項
     * new : 次の項
     */
    struct Number old, new,
                  sub_oldnew, abs_son, // abs_son : abs_sub_oldnew
                  b, ans;

    copyByZero(&old); copyByZero(&new);
    copyByZero(&sub_oldnew); copyByZero(&abs_son);
    copyByZero(&b); copyByZero(&ans);

    // メモ化再帰用のメモ配列 初期化
    for(int i = 0; i < MEMO_SIZE; i++){
        copyByZero(&memo[i]);
    }


    for(int n = 0; ; n++) {
        copyNumber(&new, &old);
        commonForArctan(&n, p, a, nmax);
        getAbs(a, &new);
        sub(&old, &new, &sub_oldnew); getAbs(&sub_oldnew, &abs_son);
        add(a, &ans, &b); copyNumber(&b, &ans);
        if (numComp(&abs_son, &N1) == -1) break;
    }
    copyNumber(&ans, a);
    return 0;
}
