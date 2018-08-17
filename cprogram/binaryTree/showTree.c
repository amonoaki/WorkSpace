#include <stdio.h>
#include <math.h>
#include "binaryTree.h"
#include "showTree.h"

#define WIDTH 4  //单位宽度空格数

//插入数据
void fileInsert()
{
    
}

void countRow(const Tree *tree, int *floor, int *maxrow)
{
    
	//创建临时树作为参数树的拷贝
	Tree tempTree;
	InitializeTree(&tempTree);
	tempTree = *tree;

	//记录临时树的根节点
	Trnode *p = tempTree.root;

	//递归遍历
	if (TreeHasEmpty(&tempTree)) {  //无路可走,返回上一层
        if (*maxrow < *floor) {
            *maxrow = *floor;
        }
        floor--;
		return ;
	} else {
		if (p->left != NULL) {  //左边有路,往左走
			tempTree.root = p->left;
            floor++;
			countRow(&tempTree, floor, maxrow);
		}
		if (NULL != p->right) {  //右边有路,往右走
			tempTree.root = p->right;
            floor++;
			countRow(&tempTree, floor, maxrow);
		}
	}
	return ;
}

void putSpace(FILE *fp, double number)
{
    number *= 2;
    while ((int)number > 0) {
        putc(' ', fp);
        number--;
    }
}

double beginSpaces(int row, int floor)
{
    double w0 = ( pow(2, row-1)-1 ) * WIDTH;
    double w1 = ( row - 1 - floor ) * WIDTH;
    double w2 = ( w0 - w1*(pow(2, floor)-1) ) / 2;

    return w2;
}

//到达下一行末尾
void toNextLine(FILE *fp)
{
    while(getc(fp) != '\n') {}  //进入下一行
    while(getc(fp) != '\n') {}  //进入下一行
    fseek(fp, -2L, SEEK_CUR);  //回到上一行末尾
    //此时指针指向该行最后一个字符'\n'
}

//回到上一行末尾
void toLastLine(FILE *fp)
{
    while (fseek(fp, -2L, SEEK_CUR) != -1) {
        if ('\n' == getc(fp)) {
            fseek(fp, -2L, SEEK_CUR);
            return;
        }
    }
    printf("已到达文件头");
    return;
}

void printTree(const Tree *tree, FILE *fp, const int row, int *floor, bool *option)
{
    //option为真打印初始位置宽度,否则打印单位宽度
	//创建临时树作为参数树的拷贝
	Tree tempTree;
	InitializeTree(&tempTree);
	tempTree = *tree;

	//记录临时树的根节点
	Trnode *p = tempTree.root;

	//递归遍历
	if (TreeHasEmpty(&tempTree)) {  //无路可走,返回上一层
        printf("      \n");
        *option = false;
        (*floor)--;
        /*//文件指针返回上一行末尾*/
		return;
	} else {
        if(*option) {
            double number = beginSpaces(row, *floor);//获得起始处空格数量
            putSpace(fp, number);//打印起始处空格
            //处理换行
            putc('\n', fp);
            fseek(fp, -1L, SEEK_CUR);
        } else {
            double number = WIDTH;//获得单位宽度空格数量
            /*putSpace(fp, number);[>//打印单位宽度空格<]*/
            //插入空格,不能直接写入,以防覆盖原有内容
        }

        //插入数据, 注意:是插入,如果直接写入,那将会覆盖部分原有内容
        /*fprintf(fp, "%s:%d", (p->item).name, (p->item).value);*/
        
        //继续遍历
		if (p->left != NULL) {  //左边有路,往左走
			tempTree.root = p->left;
            (*floor)++;
            /*//文件指针指向下一行末尾*/
            printTree(&tempTree, fp, row, floor, option);
		}
		if (NULL != p->right) {  //右边有路,往右走
			tempTree.root = p->right;
            (*floor)++;
            /*//文件指针指向下一行末尾*/
            printTree(&tempTree, fp, row, floor, option);
		}
	}

    (*floor)--;
    /*//文件指针返回上一行末尾*/
	return ;
}

void showTree(const Tree *tree)
{
    //数据文件
    FILE *fp = fopen("./tree.txt", "w+");
    
    int row = 1;
    int floor = 1;
    bool option = true;

    countRow(tree, &floor, &row);

    printTree(tree, fp, row, &floor, &option);
}
