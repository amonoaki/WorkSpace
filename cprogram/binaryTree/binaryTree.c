/*二叉树实现*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "binaryTree.h"

void InitializeTree(Tree *tree)
{
    tree->root = NULL;
    tree->total = 0;
}

bool TreeIsEmpty(const Tree *tree)
{
    if (NULL == tree->root) {
        return true;
    } else {
        return false;
    }
}

bool TreeHasEmpty(const Tree *tree)
{
    if ( NULL == (tree->root)->left && NULL == (tree->root)->right ) {
        return true;
    } else {
        return false;
    }
}

bool TreeHasFull(const Tree *tree) 
{
    if ( NULL != (tree->root)->left && NULL != (tree->root)->right ) {
        return true;
    } else {
        return false;
    }
}

bool TreeIsFull(const Tree *tree)
{
    if (MAX_TRNODES == tree->total) {
        return true;
    } else {
        return false;
    }
}

int TrnodesCount(const Tree *tree)
{
	return tree->total;
}


static void toLowerString(char *name, const char *name0)
{
    strcpy(name, name0);

    int i;
    for (i=0; name[i] != '\0'; i++) {
        name[i] = tolower(name[i]);
    }
}

static bool toLeft(const char *originName, const char *targetName)
{
    char name0[NAME_LENGTH], name[NAME_LENGTH];

    //忽略大小写,一律转换为小写进行比较
    toLowerString(name0, originName);
    toLowerString(name, targetName);

    if (strcmp(name0, name) > 0) {
        return true;
    } else {
        return false;
    }
}

static bool toRight(const char *originName, const char *targetName)
{
    char name0[NAME_LENGTH], name[NAME_LENGTH];
  
    //忽略大小写,一律转换为小写进行比较
    toLowerString(name0, originName);
    toLowerString(name, targetName);

    if (strcmp(name0, name) < 0) {
        return true;
    } else {
        return false;
    }
}

bool AddTrnode(Tree *tree, Item item)
{
    //申请一块新内存
    Trnode *p = (Trnode*) malloc(sizeof(Trnode));

    //空间有效
    if (NULL != p) {
        p->item = item;
        if (TreeIsFull(tree)) {
            fprintf(stderr, "Sorry, space is full.\n");  //空间已满
            return false;
        } else {
            if (TreeIsEmpty(tree)) {  //空树
                tree->root = p;
                p->left = NULL;
                p->right = NULL;
            } else {
                //找到节点添加的位置
                Trnode *temp = tree->root;
                do {
                    if (toLeft((temp->item).name, item.name)) {  //往左走
                        if (temp->left != NULL) {
                            temp = temp->left;  //继续往下遍历
                        } else {
                            temp->left = p;  //添加节点
                            p->left = NULL;
                            p->right = NULL;
                            break;
                        }
                    }
                    else if (toRight((temp->item).name, item.name)) {  //往右走
                        if (temp->right != NULL) {
                            temp = temp->right;
                        } else {
                            temp->right = p;
                            p->left = NULL;
                            p->right = NULL;
                            break;
                        }
                    }
                    else {  //关键值重复
                        fprintf(stderr, "Sorry, name: %s already exists.\n", item.name);
                        return false;
                    }
                }while (temp != NULL);
            }
        }
    }
    tree->total++;
    return true;
}

bool SearchTrnode(const Tree *tree, const char *name, Trnode **pnode, Trnode **plast)
{
    Trnode *temp = tree->root;

    if (TreeIsEmpty(tree)) {
        fprintf(stderr, "Empty tree, no data.\n");
        return false;
    } else {
        do {
            if (toLeft((temp->item).name, name)) {
                /*printf("to left...\n");*/
                *plast = temp;  //记录上一个节点的地址
                temp = temp->left;
            }
            else if (toRight((temp->item).name, name)) {
                /*printf("to right...\n");*/
                *plast = temp;  //记录上一个节点的地址
                temp = temp->right;
            }
            else {
                *pnode = temp;  //返回当前节点的地址
                return true;
            }
        }while (NULL != temp);
    }
    return false;
}

void printTrnode(const Tree *tree)
{
    if (TreeIsEmpty(tree)) {
        fprintf(stderr, "Empty tree, no data.\n");
        return;
    }

	//创建临时树作为参数树的拷贝
	Tree tempTree;
	InitializeTree(&tempTree);
	tempTree = *tree;

	//记录临时树的根节点
	Trnode *p = tempTree.root;

	//递归遍历
	if (TreeHasEmpty(&tempTree)) {  //无路可走,返回上一层
        printf("%-20s\t %-10d\t %-15p\t %-15p\t %-15p\n",(p->item).name, (p->item).value, p, p->left, p->right);
		return ;
	} else {
		if (p->left != NULL) {  //左边有路,往左走
			tempTree.root = p->left;
		    printTrnode(&tempTree);
		}
		if (NULL != p->right) {  //右边有路,往右走
			tempTree.root = p->right;
			printTrnode(&tempTree);
		}
	}
    
    //递归处理节点都在递归后(返回前)处理, 或者在递归前处理, 避免重复调用
    printf("%-20s\t %-10d\t %-15p\t %-15p\t %-15p\n",(p->item).name, (p->item).value, p, p->left, p->right);
	return ;
}

/*
void TraverseWithParameter(const Tree *tree, void(*pfun)(Item item))
{
	//创建临时树作为参数树的拷贝
	Tree tempTree;
	InitializeTree(&tempTree);
	tempTree = *tree;

	//记录临时树的根节点
	Trnode *p = tempTree.root;

	//递归遍历
	if (TreeHasEmpty(&tempTree)) {  //无路可走,返回上一层
	    (*pfun)(p->item);  //调用一次参数函数
        printf("p: %p, left: %p, right: %p\n", p, p->left, p->right);
		return ;
	} else {
		if (p->left != NULL) {  //左边有路,往左走
			tempTree.root = p->left;
			TraverseWithParameter(&tempTree, pfun);
		}
		if (NULL != p->right) {  //右边有路,往右走
			tempTree.root = p->right;
			TraverseWithParameter(&tempTree, pfun);
		}
	}
    //递归处理节点都在递归后(返回前)处理, 或者在递归前处理, 避免重复调用
    (*pfun)(p->item);  //调用一次参数函数
    printf("p: %p, left: %p, right: %p\n", p, p->left, p->right);
	return ;
}
*/
