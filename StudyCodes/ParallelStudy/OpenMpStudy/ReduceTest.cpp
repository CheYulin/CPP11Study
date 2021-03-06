//
// Created by cheyulin on 5/4/16.
//

#include <cstdio>
#include <vector>

void SimpleReduce() {

    int i, n, chunk;
    float a[100], b[100], result;

/* Some initializations */
    n = 100;
    chunk = 10;
    result = 0.0;
    for (i = 0; i < n; i++) {
        a[i] = i * 1.0;
        b[i] = i * 2.0;
    }

#pragma omp parallel for      \
  default(shared) private(i)  \
  schedule(static,chunk)      \
  reduction(+:result)
    for (i = 0; i < n; i++)
        result = result + (a[i] * b[i]);
    printf("Final result= %f\n", result);
}

//http://stackoverflow.com/questions/20413995/reducing-on-array-in-openmp
struct m10x1 {
    int v[10];
};

using namespace std;


int A[] = {84, 30, 95, 94, 36, 73, 52, 23, 2, 13};
m10x1 S = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
int n, m = 0;

void print_m10x1(m10x1 x) {
    int i;
    for (i = 0; i < 10; i++)
        printf("%d ", x.v[i]);
    printf("\n");
}

m10x1 add_m10x1(m10x1 x, m10x1 y) {
    m10x1 r = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    int i;
    for (i = 0; i < 10; i++)
        r.v[i] = x.v[i] + y.v[i];
    return r;
}

#pragma omp declare reduction(m10x1Add: m10x1: \
omp_out=add_m10x1(omp_out, omp_in)) initializer( \
omp_priv={{ 0,  0,  0,  0,  0,  0,  0,  0, 0,  0}} )

int main() {
#pragma omp parallel for reduction(m10x1Add: S)
    for (n = 0; n < 10; ++n) {
        for (m = 0; m <= n; ++m) {
            S.v[n] += A[m];
        }
    }
    print_m10x1(S);
}