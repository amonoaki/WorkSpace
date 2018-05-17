//两个数比较
#include <stdio.h>

int max(int x, int y)
{
    return (x > y) ? x : y;
}

void printMax(int n, int fir[], int sec[])
{
    int i;

    for(i = 0; i < n; i++) {
        printf("%d\n", max(fir[i], sec[i]));
    }
}

int main(void)
{
    int n, i;
    
    scanf("%d", &n);
    
    int fir[n], sec[n];

    for (i = 0; i < n; i++) {
        scanf("%d", &fir[i]);
        scanf("%d", &sec[i]);
    }

    printMax(n, fir, sec);

    return 0;
}
