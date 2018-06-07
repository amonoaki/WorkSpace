//PrimeGenerator.c
#include <stdio.h>

void prime(int down, int up)
{
    int i, j;

    for (i = down; i <= up; i++) {
        for (j = 2; j < i; j++) {
            if (i % j == 0) {
                break;
            }
        }
        if (i != 1 && j >= (i-1) || i == 2) {
            printf("%d\n", i);
        }
    }
}

int main(void)
{
    int n, i, j;

    scanf("%d", &n);

    int down[n], up[n];  //存放求素数的上下限

    //接受各组上下限
    for (i = 0; i < n; i++) {
        scanf("%d", &down[i]);
        scanf("%d", &up[i]);
    }

    //打印各组素数
    for (i = 0; i < n; i++) {
        prime(down[i], up[i]);
        putchar('\n');
    }

    return 0;
}
