//sum_of_integer.c
#include <stdio.h>

void calculate(int n[], int m)
{
    int i, j, sum;
    for (i = 0; i < m; i++) {
        sum = 0;
        for (j = 1; j <= n[i]; j++) {
            sum += j;
        }
        printf("%d\n\n", sum);
    }
}

int main(void)
{
    int m, i;
    scanf("%d", &m);
    int n[m];

    for (i = 0; i < m; i++) {
        scanf("%d", &n[i]);
    }

    calculate(n, m);

    return 0;
}
