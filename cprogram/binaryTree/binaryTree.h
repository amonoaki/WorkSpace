/*二叉树接口*/

#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_
#include <stdbool.h>

#define NAME_LENGTH 20

/*实体定义*/
typedef struct _item
{
    char name[NAME_LENGTH];
    int value;
} Item;

#define MAX_TRNODES 10  //定义的最大节点数量，可更改

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
//树的两个节点都是空的吗
bool TreeHasEmpty(const Tree *tree);
//树是满的吗
bool TreeIsFull(const Tree *tree);
//树的两个节点都是满的吗
bool TreeHasFull(const Tree *tree);
//获得树的项数
int TrnodesCount(const Tree *tree);
//添加一个树节点
bool AddTrnode(Tree *tree, const Item *item);
//查找一个树节点
Trnode* SearchTrnode(const Tree *tree, const Item *item);
//项在树里吗
bool InTree(const Tree *tree, const Item *item);
//删除一个树节点
bool DeleteTrnode(Tree *tree, const Item *item);
//删除所有树节点
void DeleteAllTrnode(Tree *tree);


Trnode* SearchPlaceToAdd(const Tree *tree, const char *name);

#endif
