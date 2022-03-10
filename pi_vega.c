#include <stdio.h>
#include "mulprec.h"

int main(void) {
    struct Number N4, N8;
    struct Number p, q0, q1, q0_ans, q1_ans;
    struct Number pi;
    struct Number nmax;

    clearByZero(&N4); clearByZero(&N8);
    clearByZero(&p); clearByZero(&q0); clearByZero(&q1);
    clearByZero(&q0_ans); clearByZero(&q1_ans);
    clearByZero(&pi); clearByZero(&nmax);

    /// arctan(1/2)
    setInt(&nmax, 15);
    setInt(&p, 2);
    arctan(&p, &q0, &nmax);

    /// arctan(1/7)
    clearByZero(&p); clearByZero(&nmax);
    setInt(&p, 7);
    setInt(&nmax, 6);
    arctan(&p, &q1, &nmax);

    setInt(&N4, 4);
    setInt(&N8, 8);

    /// 8 * arctan(1/2)
    multiple(&N8, &q0, &q0_ans);

    /// 4 * arctan(1/7)
    multiple(&N4, &q1, &q1_ans);

    /// 8 * arctan(1/2) - 4 * arctan(1/7)
    sub(&q0_ans, &q1_ans, &pi);

    dispNumberZeroSuppress(&pi);
}
