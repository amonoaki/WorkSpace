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
//    //创建临时树作为参数树的拷贝
//    Tree tempTree;
//    InitializeTree(&tempTree);
//    tempTree = *tree;
//
//    //记录临时树的根节点
//    Trnode *p = tempTree.root;
//
//    //创建计数器(静态)
//    static int cnt = 0;
//    cnt++;
//
//    //递归遍历
//    if (TreeHasEmpty(&tempTree)) {
//        return 0;
//    } else {
//        if (p->left != NULL) {
//            tempTree.root = p->left;
//            TrnodesCount(&tempTree);
//        }
//        if (NULL != p->right) {
//            tempTree.root = p->right;
//            TrnodesCount(&tempTree);
//        }
//    }
//
//    return cnt;
	return tree->total;
}


void toLowerString(char *name, const char *name0)
{
    strcpy(name, name0);

    int i;
    for (i=0; name[i] != '\0'; i++) {
        name[i] = tolower(name[i]);
    }
}


bool AddTrnode(Tree *tree, const Item *item)
{
    //申请一块新内存
    Trnode *p = (Trnode*) malloc(sizeof(Trnode));

    //空间有效
    if (NULL != p) {
        p->item = *item;
        if (TreeIsFull(tree)) {
            printf("Sorry, space is full.\n");  //空间已满
            return false;
        } else {
            if (TreeIsEmpty(tree)) {  //空树
                tree->root = p;
                p->left = NULL;
                p->right = NULL;
            } else {
                //找到节点添加的位置
                
                /*只存储小写,是大写则转换*/
                //忽略大小写,一律转换为小写
                char name[NAME_LENGTH], name0[NAME_LENGTH];
                toLowerString(name, item->name);

                //根据小写字母顺序确定添加的位置
                Trnode *temp = tree->root;
                int flag = 0;
                do {
                    /*每次和不同的节点比较,节点的名字也要转换成小写*/
                    toLowerString(name0, (temp->item).name);
                    flag = strcmp(name0, name);  //字符串1在字符串2前面,返回 负数;否则相反
                    if (0 == flag) {
                        printf("Sorry, name: %s already exists.\n", name);
                        return false;
                    }
                    if (flag > 0) {  //往左走
                        if (temp->left != NULL) {
                            temp = temp->left;  //继续往下遍历
                        } else {
                            temp->left = p;  //添加节点
                            p->left = NULL;
                            p->right = NULL;
                            break;
                        }
                    } else {  //往右走
                        if (temp->right != NULL) {
                            temp = temp->right;
                        } else {
                            temp->right = p;
                            p->left = NULL;
                            p->right = NULL;
                            break;
                        }
                    }
                }while (temp != NULL);
            }
        }
    }
    tree->total++;
    return true;
}

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
    /*递归处理节点都在递归后(返回前)处理, 或者在递归前处理, 避免重复调用*/
    (*pfun)(p->item);  //调用一次参数函数
    printf("p: %p, left: %p, right: %p\n", p, p->left, p->right);
	return ;
}
