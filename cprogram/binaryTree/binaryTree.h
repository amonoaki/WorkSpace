#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_
#include <stdbool.h>

/*实体定义*/
typedef struct _item
{
    int id;
    int value;
} Item;

#define MAX_TRNODES 10

typedef struct _trnode
{
    struct _trnode *left;
    struct _item item;
    struct _trnode *right;
} Trnode;

typedef struct _tree
{
    struct _trnode *root;
    int total;
} Tree;


/*函数原型*/
//初始化树
void InitializeTree(Tree *tree);
//树是空的吗
bool TreeIsEmpty(const Tree *tree);
//树是满的吗
bool TreeIsFull(const Tree *tree);
//获得树的项数
int TrnodesCount(const Tree *tree);
//添加一个树节点
bool AddTrnode(Tree *tree, const Item *item);
//查找一个树节点

//项在树里吗
//删除一个树节点
//删除所有树节点

#endif