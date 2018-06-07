#include <stdio.h>

void printArray(int *a, int n)
{
    int i;

    for (i = 0; i < n; i++) {
        printf("%2d ", a[i]);
    }
    putchar('\n');

}

int insert(int *a, int n)
{

    int i, j, temp;

    for(i=1; i<n; i++)

    {

        temp=a[i];

        for(j=i; j>0 && a[j-1]>temp; j--)
        {
            a[j]=a[j-1];
            printf("i:%-2d j:%-2d -->", i, j);
            printArray(a, n);
        }

        a[j]=temp;
        printf("i:%-2d j:%-2d -->", i, j);
        printArray(a, n);

    }
}

int main(void)
{
    int a[12] = {12, 34, 23, 45, 67, 24, 56, 74, 9, 78, 96, 32};

    printf("原始数据  -->");
    printArray(a, 12);
    insert(a, 12);

    return 0;
}
