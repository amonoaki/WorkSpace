/*
 * 功能：对矩阵进行各项处理
 *       1、将任意矩阵转换成最简型矩阵
 *       2、求秩
 *       3、求逆
 *       4、求对应方程组的解
 * 作者：祯
 * */

#include <stdio.h>

void getData(int row, int column, double arr[row][column]);
void convert(int row, int column, double arr[row][column]);
int rank(int row, int column, double arr[row][column]);
void printArray(int row, int column, double arr[row][column]);
void inverse(int row, int column, double arr[row][column]);

int main(void)
{
    int row = 0, column = 0;
    printf("请输入 行数 和 列数 (以空格或回车间隔): ");
    scanf("%d%d", &row, &column);

    double data[row][column];
    printf("\n请输入矩阵(以空格或回车间隔): \n");
    getData(row, column, data);
    
    printf("矩阵的逆为:\n");   //矩阵求逆要用原始数据，且求逆不会改变原始数据
    inverse(row, column, data);//所以求逆放在改变原始数据的函数之前

    convert(row, column, data);

    printf("最简形矩阵为:\n");
    printArray(row, column, data);

    printf("矩阵的秩为: %d\n", rank(row, column, data));

    return 0;
}

//获取矩阵数据
void getData(int row, int column, double arr[row][column])
{
    int i = 0, j = 0;

    for (i = 0; i < row; i++) {
        for (j = 0; j < column; j++) {
            scanf("%lf", &arr[i][j]);
        }
    }
}

//将矩阵首行与第一条非零行交换
void preConvert(int row, int column, double arr[row][column])
{
    int i = 0, j = 0, target = 0;
    double temp = 0;

    for (i = 0; i < row; i++) {
        if (arr[i][0] != 0) {
            target = i;
        }
    }
    for (i = 0; i < column; i++) {
        temp = arr[0][i];
        arr[0][i] = arr[target][i];
        arr[target][i] = temp;
    }
}

//化为最简形
void convert(int row, int column, double arr[row][column])
{
    int i = 0, j = 0, k = 0;
    double rate = 0;

    //如果首行第一个元素为零，则进行预处理
    if (arr[0][0] == 0) {
        preConvert(row, column, arr);
    }

    //化为上三角矩阵
    for (i = 0; i < row - 1; i++) {
        for (j = i + 1; j < row; j++) {
            rate = arr[j][i] / arr[i][i];
            for (k = i; k < column; k++) {
                arr[j][k] -= arr[i][k] * rate;
            }
        }
    }

    //右上也化为零
    for (i = row - 1; i > 0; i--) {
        for (j = i - 1; j >= 0; j--) {
            rate = arr[j][i] / arr[i][i];
            for (k = i; k < column; k++) {
                arr[j][k] -= arr[i][k] * rate;
            }
        }
    }

    //阶梯处全部化为1
    for (i = 0; i < row; i++) {
        rate = 1 / arr[i][i];
        for (j = i; j < column; j++) {
            arr[i][j] *= rate;
        }
    }

}

//打印矩阵
void printArray(int row, int column, double arr[row][column])
{
    int i, j;

    for (i = 0; i < row; i++) {
        for (j = 0; j < column; j++) {
            printf("%7.3f ", arr[i][j]);
        }
        putchar('\n');
    }
}

//求秩
int rank(int row, int column, double arr[row][column])
{
    int i = 0, rank = 0;

    for (i = 0; i < row; i++) {
        if (arr[i][i] == 1) {
            rank++;
        } else {
            break;
        }
    }

    return rank;
}

//求逆
void inverse(int row, int column, double arr[row][column])
{
    if (row != column) {
        printf("无逆\n");
    } else {
        int i = 0, j = 0;
        double extendArr[row][column+row];
        
        //准备数据
        for (i = 0; i < row; i++) {
            for (j = 0; j < column; j++) {
                extendArr[i][j] = arr[i][j];
            }
        }
        for (i = 0; i < row; i++) {
            for (j = column; j < column+row; j++) {
                if ((j - row) == i) {
                    extendArr[i][j] = 1;
                } else {
                    extendArr[i][j] = 0;
                }
            }
        }

        //化成左最简形
        convert(row, (column+row), extendArr);

        //打印逆阵
        for (i = 0; i < row; i++) {
            for (j = column; j < column+row; j++) {
                printf("%7.3f ", extendArr[i][j]);
            }
            putchar('\n');
        }

    }
}
