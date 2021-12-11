#define KETA 40

struct Number {
    int n[KETA];
    int sign;
};

void clearByZero(struct Number *);
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
int setSign(struct Number *, int);
int getSign(struct Number *);
int numComp(struct Number *, struct Number *);
int add(struct Number *, struct Number *, struct Number *);
int sub(struct Number *, struct Number *, struct Number *);
int simpleMultiple(int, int, int *);
int multiple(struct Number *, struct Number *, struct Number *);
int divide(struct Number *, struct Number *, struct Number *, struct Number *);
