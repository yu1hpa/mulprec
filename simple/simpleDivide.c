#include <stdio.h>
#include <stdlib.h>

int simpleDivide(int, int, int*, int*);

int main(int argc, char **argv){
    int a, b, c, d;
    int r;

    a = -12345678;
    b = -9;

    r = simpleDivide(a, b, &c, &d);

    if (r == -1) {
        printf("divide by zero error.\n");
    } else {
        printf("%d / %d = %d ... %d\n", a, b, c, d);
    }
    return 0;
}

int simpleDivide(int x, int y, int *z, int *w){
    int k;
    if (y == 0) return -1;
    if (x < 0 && y > 0){
        x = abs(x);
        simpleDivide(x, y, z, w);
        *z = -(*z);
        return 0;
    } else if (x >= 0 && y < 0){
        y = abs(y);
        simpleDivide(x, y, z, w);
        *z = -(*z);
        return 0;
    } else if (x < 0 && y < 0){
        x = abs(x);
        y = abs(y);
        simpleDivide(x, y, z, w);
        return 0;
    }

    k = 0;
    while(1) {
        if(x < y) break;
        x -= y;
        k++;
    }
    *z = k;
    *w = x;
    return 0;
}
