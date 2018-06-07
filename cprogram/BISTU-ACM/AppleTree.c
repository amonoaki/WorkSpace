//AppleTree.c
#include <stdio.h>

int main(void)
{
    int a[10], h, i, count = 0;

    for (i = 0; i < 10; i++) {
        scanf("%d", &a[i]);
    }
    scanf("%d", &h);

    for (i = 0; i < 10; i++) {
        if (h+30 >= a[i]) {
            count++;
        }
    }

    printf("%d", count);

    return 0;
}
