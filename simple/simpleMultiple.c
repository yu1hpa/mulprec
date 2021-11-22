#include <stdio.h>
#include <assert.h>
#include <limits.h>

int simpleMultiple(int, int, int*);

int main(int argc, char **argv){
    int a, b, c;

    a = 1234;
    b = 9;
    simpleMultiple(a, b, &c);
    assert(c == a*b);
    printf("%d * %d = %d\n", a, b, c);
}

int simpleMultiple(int a, int b, int *c){
    int cnt = 1;
    while(1){
        int w = INT_MAX - a;
        if (w < *c) return -1;
        *c += a;
//        printf("%d\n", *c);
        if (cnt >= b) break;
        cnt++;
    }
    return 0;
}

