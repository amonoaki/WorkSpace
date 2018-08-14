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
    //创建临时树作为参数树的拷贝
    Tree tempTree;
    InitializeTree(&tempTree);
    tempTree = *tree;

    //记录临时树的根节点
    Trnode *p = tempTree.root;

    //创建计数器(静态)
    static int cnt = 0;
    cnt++;

    //递归遍历
    if (TreeHasEmpty(&tempTree)) {
        return 0;
    } else {
        if (p->left != NULL) {
            tempTree.root = p->left;
            TrnodesCount(&tempTree);
        } 
        if (NULL != p->right) {
            tempTree.root = p->right;
            TrnodesCount(&tempTree);
        }
    }
    
    return cnt;
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
        } else {
            if (TreeIsEmpty(tree)) {  //空树
                tree->root = p;
                p->left = NULL;
                p->right = NULL;
            } else {
                //找到节点添加的位置
                
                /*只存储小写,是大写则转换*/
                //忽略大小写,一律转换为小写
                char name[NAME_LENGTH];
                strcpy(name, item->name);

                int i;
                for (i=0; i<NAME_LENGTH; i++) {
                    name[i] = tolower(name[i]);
                }

                //根据小写字母顺序确定添加的位置
                Trnode *temp = tree->root;
                int flag = 0;
                do {
                    flag = strcmp((temp->item).name, name);
                    if (0 == flag) {
                        printf("Sorry, name: %s already exists.\n", name);
                        break;
                    }
                    if (flag < 0) {  //往左走
                        if (temp->left != NULL) {
                            temp = temp->left;  //继续往下遍历
                        } else {
                            temp->left = p;  //添加节点
                            break;
                        }
                    } else {  //往右走
                        if (temp->right != NULL) {
                            temp = temp->right;
                        } else {
                            temp->right = p;
                            break;
                        }
                    }
                }while (temp != NULL);
                
            }
        }
    }

    tree->total++;
}

