/*
 * 功能：对矩阵进行各项处理
 *       1、将任意矩阵转换成最简型矩阵
 *       2、求秩
 *       3、求逆
 * 局限：只能处理部分具有相同行的情况
 * 作者：祯
 * */

#include <stdio.h>
#include <math.h>

void getData(int row, int column, double arr[row][column]);
int convert(int row, int column, double arr[row][column], int option);
int rank(int row, int column, double arr[row][column]);
void printArray(int row, int column, double arr[row][column]);
void inverse(int row, int column, double arr[row][column], int option);
void copyArray(int row, int column, double origin_arr[row][column], double target_arr[row][column]);

int main(void)
{
    int row = 0, column = 0, option = 0;
    printf("请输入 行数: ");
    scanf("%d", &row);
    printf("请输入 列数: ");
    scanf("%d", &column);
    printf("是否展开步骤(1-是, 0-否)");
    scanf("%d", &option);

    double data[row][column];
    printf("\n请输入矩阵(以空格或回车间隔): \n");
    getData(row, column, data);

    double cp_data[row][column];
    copyArray(row, column, data, cp_data);

    int rank = convert(row, column, data, option);
    printf("矩阵的秩为: %d\n", rank);

    printf("最简形矩阵为:\n");
    printArray(row, column, data);

    printf("求逆:\n");
    if (rank == row) {
        inverse(row, column, cp_data, option);  //矩阵求逆要用原始数据
    } else {
        printf("<无逆>\n");  //是方阵不是满秩无逆
    }

    printf("Press any key to continue...\n");
    getchar();
    getchar();

    return 0;
}

//交换指定的两行数据(内部功能函数)
void exchange(int row, int column, double arr[row][column], int origin, int target)
{
    int i = 0;
    double temp = 0;

    if (origin != target) {
        for (i = 0; i < column; i++) {
            temp = arr[origin][i];
            arr[origin][i] = arr[target][i];
            arr[target][i] = temp;
        }
    }
}

//将矩阵首行与第一条非零行交换(内部功能函数)
void preConvert(int row, int column, double arr[row][column])
{
    int i = 0, target = 0;

    for (i = 0; i < row; i++) {
        if (arr[i][0] != 0) {
            target = i;
        }
    }
    exchange(row, column, arr, 0, target);
}

//检测是否有非零行，有则换到后面(内部功能函数)
int rowSearch(int row, int column, double arr[row][column])
{
    int i = 0, j = 0, count = 0, count1 = 0;

    while(1) {
        for (i = 0; i < row-count1; i++) {
            count = 0;
            for (j = 0; j < column; j++) {
                if (fabs(arr[i][j]-0) < 0.000001) {
                    count++;
                }
            }
            if (count == column) {
                exchange(row, column, arr, i, row-1-count1);
                count1++;  //代表空行的数量
            }
        }
        break;
    }

    return count1;

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

//转化为最简形
int convert(int row, int column, double arr[row][column], int option)
{
    int i = 0, j = 0, k = 0, count1 = 0;
    double rate = 0;

    //如果首行第一个元素为零，则进行预处理
    if (arr[0][0] == 0) {
        preConvert(row, column, arr);
    }

    //化为上三角矩阵
    for (i = 0; i < row - 1 - count1; i++) {
        for (j = i + 1; j < row; j++) {
            rate = arr[j][i] / arr[i][i];
            for (k = i; k < column; k++) {
                arr[j][k] -= arr[i][k] * rate;
            }
        }
        count1 = rowSearch(row, column, arr);
    }
    if (option == 1) {
        printf("(化为上三角矩阵)\n");
        printArray(row, column, arr);
    }

    //求秩
    int r = rank(row, column, arr);

    //右上也化为零
    for (i = r - 1; i > 0; i--) {
        for (j = i - 1; j >= 0; j--) {
            rate = arr[j][i] / arr[i][i];
            for (k = i; k < column; k++) {
                arr[j][k] -= arr[i][k] * rate;
            }
        }
    }
    if (option == 1) {
        printf("(右上也化为零)\n");
        printArray(row, column, arr);
    }

    //阶梯处全部化为1
    for (i = 0; i < r; i++) {
        rate = 1 / arr[i][i];
        for (j = i; j < column; j++) {
            arr[i][j] *= rate;
        }
    }
    if (option == 1) {
        printf("(阶梯处全部化为1)\n");
        printArray(row, column, arr);
    }

    return r;
}


//求秩
int rank(int row, int column, double arr[row][column])
{
    int i = 0, j = 0, rank = row, count = 0;

    for (i = 0; i < row; i++) {
        count = 0;
        for (j = 0; j < column; j++) {
            if ( fabs(arr[i][j]-0) < 0.000001) {
                count++;
            }
        }
        if (count == column) {
            rank--;
        }
    }

    return rank;
}

//求逆
void inverse(int row, int column, double arr[row][column], int option)
{
    if (row != column) {
        printf("<无逆>\n");  //不是方阵无逆
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
        convert(row, (column+row), extendArr, option);

        //打印逆阵
        printf("逆为：\n");
        for (i = 0; i < row; i++) {
            for (j = column; j < column+row; j++) {
                printf("%7.3f ", extendArr[i][j]);
            }
            putchar('\n');
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

//复制数组
void copyArray(int row, int column, double origin_arr[row][column], double target_arr[row][column])
{
    int i = 0, j = 0;

    for (i = 0; i < row; i++) {
        for (j = 0; j < column; j++) {
            target_arr[i][j] = origin_arr[i][j];
        }
    }
}

