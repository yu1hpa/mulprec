#include<stdint.h>

// 基数
#define RADIX 1000000000
#define RADIX_KETA (int)log10(RADIX)

 /**
  * KETA = 求めたい桁数 / 9
  *
  * NOTE: 後ろ数桁は誤差がある
  */
#ifdef PI
#define KETA 114 // 1000桁程度
//#define KETA 556 // 5000桁程度
//#define KETA 1114 // 10000桁程度
#endif

// for testing
#ifdef TEST
#define KETA 20
#endif

struct Number {
    uint_fast64_t n[KETA];
    int sign;
};

void clearByZero(struct Number *);
void copyByZero(struct Number *);
void putSign(struct Number *);
void setRnd(struct Number *, int);
void dispNumber(struct Number *);
void dispNumberZeroSuppress(struct Number *);
void copyNumber(struct Number *, struct Number *);
void getAbs(struct Number *, struct Number *);
int isZero(struct Number *);
int mulBy10(struct Number *, struct Number *);
int divBy10(struct Number *, struct Number *);
int setInt(struct Number *, int);
int setIntToZero(struct Number *, int);
int getInt(struct Number *, int *);
int setSign(struct Number *, int);
int getSign(struct Number *);
int numComp(struct Number *, struct Number *);
int add(struct Number *, struct Number *, struct Number *);
int sub(struct Number *, struct Number *, struct Number *);
int simpleMultiple(int, int, int *);
int multiple(struct Number *, struct Number *, struct Number *);
int increment(struct Number *, struct Number *);
int divide(struct Number *, struct Number *, struct Number *, struct Number *);
int fastdivide(struct Number *, struct Number *, struct Number *, struct Number *);
int power(struct Number *, struct Number *, struct Number *);
int fastpower(struct Number *, struct Number *, struct Number *);
int arctan(struct Number *, struct Number *, struct Number *);

