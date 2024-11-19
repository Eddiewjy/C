#include <stdio.h>
int Fib_recur(int m, int k) {
    if (m == k - 1)
        return 1;
    else if (m < k - 1)
        return 0;
    else
        m--;
    return Fib_recur(m - 2, k) + Fib_recur(m - 1, k);
}
#define N 1000 // 记录的总条数，视情况而定
typedef struct students {
    char project[10];
    int sex; // 0男1女
    char school;
    int score;
} stu;

void sum_score(stu s[]) {
    int A[3] = {0}; // 第一位男，第二位女，第三位总
    int B[3] = {0};
    int C[3] = {0};
    int D[3] = {0};
    int E[3] = {0};
    for (int i = 0; i < N; i++) {
        switch (s[i].school) {
        case 'A':
            if (s[i].sex)
                A[1] += 1;
            else
                A[0] += 1;
            break;
        case 'B':
            if (s[i].sex)
                B[1] += 1;
            else
                B[0] += 1;
            break;
        case 'C':
            if (s[i].sex)
                C[1] += 1;
            else
                C[0] += 1;
            break;
        case 'D':
            if (s[i].sex)
                D[1] += 1;
            else
                D[0] += 1;
            break;
        case 'E':
            if (s[i].sex)
                E[1] += 1;
            else
                E[0] += 1;
            break;
        }
    }
    A[2] = A[0] + A[1];
    B[2] = A[0] + A[1];
    C[2] = A[0] + A[1];
    D[2] = A[0] + A[1];
    E[2] = A[0] + A[1];
    return;
}

#include <math.h>
#include <stdio.h>


#define MAXINT 10000
#define ARRAYSIZE 100

void error_handing() {
    long long a[ARRAYSIZE];
    long long n;
    printf("input your n:");
    scanf("%d", &n);
    if (n > ARRAYSIZE) {
        printf("error");
    } else {
        long long fac[n];
        a[0] = fac[0] = 0;
        fac[1] = 1;
        a[1] = 2;
        for (long long i = 2; i < n; i++) {
            fac[i] = i * fac[i - 1];
            if (fac[i] * pow(2, i)) {
                printf("error");
            } else {
                a[i] = fac[i] * pow(2, i);
            }
        }
    }
}