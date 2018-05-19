//快速排序算法实践
/*
 定标志(pivot = a[storeIndex-1])((pivot = a[storeIndex+1]))
 分区(in: array, pivot; p: compare & swap; o: divided_array)
 重复上面两个步骤
*/

#include <stdio.h>

void printArray(int *a, int n)
{
    int i;

    for (i = 0; i < n; i++) {
        printf("%02d ", a[i]);
    }
    putchar('\n');

}

void swap(int *x, int *y)
{
    int temp;

    if (x != y) {
        temp = *x;
        *x = *y;
        *y = temp;
    }
}

void quickSort(int *a, int lower, int ceiling)
{
    if (lower >= ceiling) {  //注意此处是 >=
        return;
    }

    int i, temp, pivot = a[ceiling], storedIndex = lower;  //注意递归上下限的使用

    for (i = lower; i < ceiling; i++) {
        if (a[i] <= pivot) {
            swap(&a[storedIndex], &a[i]);
            storedIndex++;
        }
    }
    swap(&a[storedIndex], &a[ceiling]);

    quickSort(a, lower, storedIndex-1);
    quickSort(a, storedIndex+1, ceiling);
}

int main(void)
{
    int n, i;
    printf("n = ");
    scanf("%d", &n);

    int a[n];
    printf("array:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    quickSort(a, 0, n-1);
    printArray(a, n);

    return 0;
}


