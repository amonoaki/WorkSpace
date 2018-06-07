//简单的四则运算.c
#include <stdio.h>

int main(void)
{
    int n, i;
    scanf("%d", &n);

    int x[n], y[n];
    for (i = 0; i < n; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }

    for (i = 0; i < n; i++) {
        printf("%d %d %d %d\n", x[i]+y[i], x[i]*y[i], x[i]-y[i], x[i]/y[i]);
    }

    return 0;
}
