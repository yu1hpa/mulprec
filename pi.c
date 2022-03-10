#include <stdio.h>
#include<sys/time.h>
#include "mulprec.h"

int main(void) {
    struct timeval tv;
    double tstart, tend;
    gettimeofday(&tv, NULL);
    tstart = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;

    struct Number N4; clearByZero(&N4);
    struct Number p, q0, q1, q2; clearByZero(&p); clearByZero(&q0);
    struct Number _q10, _q210; clearByZero(&_q10); clearByZero(&_q210);
    struct Number pi; clearByZero(&pi);
    struct Number nmax; clearByZero(&nmax);

    /// arctan(1/2)
    setInt(&nmax, 15);
    setInt(&p, 2);
    arctan(&p, &q0, &nmax);

    /// arctan(1/5)
    clearByZero(&p); clearByZero(&nmax);
    setInt(&p, 5);
    setInt(&nmax, 7);
    arctan(&p, &q1, &nmax);

    /// arctan(1/8)
    clearByZero(&p); clearByZero(&nmax);
    setInt(&p, 8);
    setInt(&nmax, 5);
    arctan(&p, &q2, &nmax);

    /// 4 * (arctan(1/2) + arctan(1/5) + arctan(1/8))
    setInt(&N4, 4);
    add(&q0, &q1, &_q10);
    add(&_q10, &q2, &_q210);
    multiple(&_q210, &N4, &pi);

    gettimeofday(&tv, NULL);
    dispNumberZeroSuppress(&pi);
    tend = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
    printf("処理時間 = %f[s]\n", tend - tstart);
}
