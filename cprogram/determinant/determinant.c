#include <stdio.h>

void getData(int n, double data[n][n]);
int preProcess(int n, double data[n][n]);
void process(int n, double data[n][n]);
double getResult(int n, double data[n][n]);
void showResult(double produce, int n, double data[n][n]);

int main (void) 
{
    int n = 0, flag = 1;
    printf("Please enter the size of the determinant: ");
    scanf("%d", &n);
    double data[n][n], product = 0;

    getData(n, data);  //get the number of the determinant from keyboard or one file 
    flag = preProcess(n, data);  //make sure that the first number of the first line is not zero, or the next process will be interrupt
    if (flag != 0) {
        process(n, data);  //process the data in the determinant, after this you can get a simple determinant
        product = getResult(n, data);  //calculate the result of the determinant
    }
    product *= flag;
    showResult(product, n, data);  //show the processed determinant and the final result
    
    return 0;
}

void getData(int n, double data[n][n])
{
    int i, j;
    printf("Please enter the data of determinant:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%lf", &data[i][j]);
        }
    }
}

void exchange(int n, double array1[n], double array2[n])
{
    int i;
    for (i = 0; i < n; i++) {
        array1[i] = array2[i];
    }
}

int preProcess(int n, double data[n][n])
{
    int i, temp = 0, flag = 1;
    double tempArray[n];

    for (i = 0; i < n; i++) {
        if (data[i][0] != 0) {
            temp = i;
            break;
        } else {
            if (i == n - 1) {
                return 0;
            }
            continue;
        }
    }
    if (temp != 0) {
        exchange(n, tempArray, data[0]);
        exchange(n, data[0], data[temp]);
        exchange(n, data[temp], tempArray);
        flag *= -1;
    }
    return flag;
}
void process(int n, double data[n][n])
{
    int i, j, k;
    double t;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            t = data[j][i] / data[i][i];
            for (k = i; k < n; k++) {
                data[j][k] += (-1) * t * data[i][k];
            }
        }
    }
}

double getResult(int n, double data[n][n])
{
    int i;
    double produce = 1;
    for (i = 0; i < n; i++) {
        produce *= data[i][i];
    }
    return produce;
}

void showResult(double product, int n, double data[n][n])
{
    int i, j;
    printf("\nYou can get this determinant:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%7.3f ", data[i][j]);
        }
        putchar('\n');
    }
    printf("\nThe result is: %.3f \n", product);
}
