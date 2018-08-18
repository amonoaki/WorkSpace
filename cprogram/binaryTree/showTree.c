#include <stdio.h>
#include <math.h>
#include <string.h>
#include "binaryTree.h"
#include "showTree.h"


//插入数据
void fileInsert(FILE *fp, const char *str)
{
    long cur = ftell(fp);
    long len = strlen(str);
    int i = 0;
    char c;

    //建一个新文档
    FILE *fpnew = fopen("./tree_new.txt", "w");

    //复制前面内容
    fseek(fp, 0L, SEEK_SET);
    while ((c=getc(fp)) != EOF) {
        if (i >= cur) {
            break;
        }
        putc(c, fpnew);
        i++;
    }

    //加入待插入的内容
    fprintf(fpnew, "%s", str);

    //复制后面内容
    fseek(fp, -1L, SEEK_CUR);
    while ((c=getc(fp)) != EOF) {
        putc(c, fpnew);
    }

    //将旧文件用新文件覆盖, 并重新打开
    fclose(fp);
    fclose(fpnew);

    rename("./tree_new.txt", "./tree.txt");

    fp = fopen("./tree.txt", "r+");
    fseek(fp, cur+len, SEEK_SET);
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
        (*floor)--;
		return ;
	} else {
		if (p->left != NULL) {  //左边有路,往左走
			tempTree.root = p->left;
            (*floor)++;
			countRow(&tempTree, floor, maxrow);
		}
		if (NULL != p->right) {  //右边有路,往右走
			tempTree.root = p->right;
            (*floor)++;
			countRow(&tempTree, floor, maxrow);
		}
	}
    (*floor)--;
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
    double w1 = pow(2, row - 1 - floor) * WIDTH;
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
    printf("已到达文件头\n");
    return;
}

void initializeFile(FILE *fp, int row)
{
    int i;

    for (i = 0; i < row; i++) {
        double number = beginSpaces(row, i);//获得起始处空格数量
        putSpace(fp, number);//打印起始处空格
        //处理换行
        putc('\n', fp);
    }
    
    for (i = 0; i < row-1; i++) {
        toLastLine(fp);
    }
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
        //文件指针返回上一行末尾
        toLastLine(fp);
		return;
	} else {
        if(!(*option)) {
            //插入空格,不能直接写入,以防覆盖原有内容
            int number = (int)pow(2, row-1-*floor) * WIDTH;
            //生成空格
            char spaces[number+1];
            int i;
            for (i = 0; i < number; i++) {
                spaces[i] = ' ';
            }
            spaces[i] = '\0';
            //插入空格
            fileInsert(fp, spaces);
        }

        //插入数据, 注意:是插入,如果直接写入,那将会覆盖部分原有内容
        //生成待插入数据
        char str[NAME_LENGTH+10];
        sprintf(str, "%s:%d", (p->item).name, (p->item).value);
        printf("插入%s\n", (p->item).name);
        //插入数据
        fileInsert(fp, str);
        
        //继续遍历
		if (p->left != NULL) {  //左边有路,往左走
			tempTree.root = p->left;
            (*floor)++;
            //文件指针指向下一行末尾
            toNextLine(fp);  //注意:此处要保证能够到达下一行,否则不能继续运行
            printTree(&tempTree, fp, row, floor, option);
		} else {
            
        }
		if (NULL != p->right) {  //右边有路,往右走
			tempTree.root = p->right;
            (*floor)++;
            //文件指针指向下一行末尾
            toNextLine(fp);
            printTree(&tempTree, fp, row, floor, option);
		}
	}

    (*floor)--;
    //文件指针返回上一行末尾
    toLastLine(fp);
	return ;
}

void showTree(const Tree *tree)
{
    //打开数据文件
    FILE *fp = fopen("./tree.txt", "w+");
    
    int row = 1;
    int floor = 1;
    bool option = true;

    countRow(tree, &floor, &row);

    //开始输出到文件
    initializeFile(fp, row);
    printTree(tree, fp, row, &floor, &option);

    //结束,关闭文件
    fclose(fp);
}
