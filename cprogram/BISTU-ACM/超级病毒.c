#include <stdio.h>

int count(char org[], char tar[])
{
    int i = 0, j = 0, k = 0, count1 = 0, count2 = 0;
    int length = 0;

    for(i = 0; i < 10000 && org[i] != '\n'; i++) {
        length++;
    }

    for (i = 0; i < 1000000; i++) {
        if (tar[i] == '\n') {
            break;
        }
        else if (tar[i] == org[1]) {
            count1 = 0;
            for (j = i, k = 0; j < 1000000 && k < length; j++, k++) {
                if (tar[j] == org[k]) {
                    count1++;
                } else {
                    break;
                }
            }
            if (count1 == length) {
                count2++;
            }
        }
    }

    return count2;
}

int main(void)
{
    int n = 0, i = 0;
    char org[10000];

    n = scanf("%d", &n);
    char tar[n][1000000];

    getchar();
    fgets(org, 10000, stdin);

    for (; i < n; i++) {
        fgets(tar[i], 1000000, stdin);
    }

    for (i = 0; i < n; i++) {
        printf("%d\n", count(org, tar[i]));
    }

    return 0;
}
