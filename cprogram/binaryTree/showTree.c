#define _CRT_SECURE_NO_WARNINGS  //使用了scanf，strcp等被VS判定为不安全的函数，以此句将安全警告暂行忽略

#include <stdio.h>
#include <math.h>
#include "showTree.h"
#include "binaryTree.h"
#include "queue.h"
#include "queueQueue.h"

static void traverseTree(const Tree *tree, int *floor, QueueQueue *queueQueue);
static void printBlocks(FILE *fp, char opt, int num);
static void printLines(FILE *fp, char opt, int num);


/*
  数据结构说明：
  此程序使用了两层队列，每层二叉树对应一个内队列Queue，存储着同一层中的数据；
  各个内队列的head节点由外队列QueueQueue负责存储。
*/
void showTree(const Tree *tree, FILE *fp)
{
	int floor = 0;

	if (fp == NULL) {
		fp = fopen("./tree.txt", "w");
	}  //如果未指定文件句柄则默认输出到程序当前执行路径

	//外层队列
	QueueQueue queueQueue;
	InitializeQueueQueue(&queueQueue);

	//递归遍历二叉树
    traverseTree(tree, &floor, &queueQueue);

	while (queueQueue.total != 0)
	{  //处理外队列，将节点逐个弹出
		Queue *queue = RemoveQueue(&queueQueue).queue;

		while (queue->total != 0)
		{  //处理内队列，将节点逐个弹出
			Item item = Remove(queue);

			//计算需要多少块空白(短横线)，num=2^(floor-1)，num为空白块(短横线)数量，floor为层数，也是节点数
			int num = (int)pow(2, queueQueue.total-1);
			num = (num < 0) ? 0 : num;

			printBlocks(fp, 'l', num);  //打印数据前的空白，'l'表示"left"
			printLines(fp, 'l', num);  //打印数据前的短横线
			fprintf(fp, "%d", item.value);  //打印当前队列节点的数据
			printLines(fp, 'r', num);  //打印数据后的短横线，'r'表示"right"
			printBlocks(fp, 'r', num);  //打印数据后的空白
		}
		fprintf(fp, "\n");  //换行
	}

	if (fp != stdout) {
		fclose(fp);  //关闭文件句柄
		if (fp == NULL) {
			printf("tree.txt数据文件已保存到程序当前执行路径\n");
		}
		else {
			printf("数据已保存到指定文件\n");
		}
	}
}

//递归遍历二叉树，tree为 以当前节点为根节点 的子树，floor记录当前所在层数，queueQueue为外队列
static void traverseTree(const Tree *tree, int *floor, QueueQueue *queueQueue)
{
	//空树打印提示到错误流
    if (TreeIsEmpty(tree)) {
            fprintf(stderr, "Empty tree, no data.\n");
            return;
    }

	//临时树节点，存储以当前节点为根节点的子树
	Tree tempTree;
    InitializeTree(&tempTree);
    tempTree = *tree;

	Trnode *p = tempTree.root;  //存储当前节点，也是临时子树的根节点

	//层数初始值为0，当层数>=外队列长度的时候，说明这是第一次进入这一层，所以要为这一层新建一个节点
	if (*floor >= GetLengthQueue(queueQueue)) {
		AppendQueue(queueQueue, *NewDataQueue(NewQueue()));
	}

	//获取与当前层对应的内队列，将当前树节点数据追加到内队列末尾
	Queue *queue = GetItemQueue(queueQueue, *floor).queue;
	Append(queue, p->item);

	//递归操作
    if (TreeHasEmpty(&tempTree)) {  //到达树的末梢，往回走
		(*floor)--;
        return;
    }
    else {
        if (p->left != NULL) {  //左边不为空，往左走
            tempTree.root = p->left;
			(*floor)++;
            traverseTree(&tempTree, floor, queueQueue);
        }
        if (NULL != p->right) {  //右边不为空，往右走
            tempTree.root = p->right;
			(*floor)++;
            traverseTree(&tempTree, floor, queueQueue);
        }
    }
	(*floor)--;  //两边都走过了，往回走
    return;
}

//打印空白块的函数，此方法不用对外开放
static void printBlocks(FILE *fp, char opt, int num)
{
	num *= BLOCK_LENGTH;  //宏定义每块空白的长度，默认为1

	if (opt == 'l') {  //打印数据左边的空白
		while (num > 0)
		{
			fprintf(fp, " ");
			num--;
		}
	}
	else if (opt == 'r') {  //打印数据右边的空白
		while (num > 1)
		{
			fprintf(fp, " ");
			num--;
		}
	}
}

static void printLines(FILE *fp, char opt, int num)
{
	num *= BLOCK_LENGTH;  //宏定义每块短横线的长度，默认为1

	if (opt == 'l') {  //打印数据左边的短横线
		if (num > 0) fprintf(fp, "|");
		while (num > 1)
		{
			fprintf(fp, "-");
			num--;
		}
	}
	else if (opt == 'r') {  //打印数据右边的短横线
		while (num > 1)
		{
			fprintf(fp, "-");
			num--;
		}
		fprintf(fp, "|");
	}
}