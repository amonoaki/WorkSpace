#include <stdio.h>

void getData(int n, double pdata[n][n]);
void process(int n, double pdata[n][n]);
double getResult(int n, double pdata[n][n]);

int main (void) 
{
    int n = 0;
    printf("Please enter the size of the determinant: ");
    scanf("%d", &n);
    
    double data[n][n], produce = 0;

    getData(n, data);  //get the number of the determinant from keyboard or one file 
    process(n, data);  //process the data in the determinant, after this you can get a simple determinant
    produce = getResult(n, data);  //calculate the result of the determinant
    
    int i, j;
    printf("\nYou can get this determinant:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%7.3f ", data[i][j]);
        }
        putchar('\n');
    }

    printf("\nThe result is: %.3f \n", produce);
    return 0;
}

void getData(int n, double pdata[n][n])
{
    int i, j;
    printf("Please enter the data of determinant:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%lf", &pdata[i][j]);
        }
    }
}

void process(int n, double pdata[n][n])
{
    int i, j, k;
    double t;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            t = pdata[j][i] / pdata[i][i];
            for (k = i; k < n; k++) {
                pdata[j][k] += (-1) * t * pdata[i][k];
            }
        }
    }
}

double getResult(int n, double pdata[n][n])
{
    int i;
    double produce = 1;
    for (i = 0; i < n; i++) {
        produce *= pdata[i][i];
    }
    return produce;
}
