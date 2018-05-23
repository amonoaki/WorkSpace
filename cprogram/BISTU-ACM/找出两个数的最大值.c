//找出两个数的最大值.c
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
        if (x[i] == y[i]) {
            printf("These numbers are equal.\n");
        } else {
            printf("%d", (x[i] > y[i]) ? x[i] : y[i]);
        }
    }
    return 0;
}
