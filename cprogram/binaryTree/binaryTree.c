/*二叉树实现*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "binaryTree.h"


static void toLowerString(char *name, const char *name0);
static bool toLeft(const char *originName, const char *targetName);
static bool toRight(const char *originName, const char *targetName);
static bool atLeft(const Trnode *plast, const Trnode *pnode);
static void toLeftEnd(Tree *tree);
static void toRightEnd(Tree *tree);
static void freeTrnodes(Tree *tree);

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

/*增加节点*/
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
/*查找节点*/
bool SearchTrnode(const Tree *tree, Item item, Trnode **pnode, Trnode **plast)
{
    Trnode *temp = tree->root;
    char name[NAME_LENGTH];
    strcpy(name, item.name);

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
/*删除节点*/
bool DeleteTrnode(Tree *tree, Item item)
{
    Trnode *pnode = NULL, *plast = NULL;
    Trnode *pleft = NULL, *pright = NULL;
    if ( !SearchTrnode(tree, item, &pnode, &plast) ) {
        return false;
    }

    Tree tempTree;
    InitializeTree(&tempTree);
    tempTree.root = pnode;

    //没有子树时
    if (TreeHasEmpty(&tempTree)) {
        //删除的是根节点
        if (NULL == plast) {
            tree->root = NULL;
        } else {  //父节点的相应子节点归空
            if (atLeft(plast, pnode)) {
                plast->left = NULL;
            } else {
                plast->right = NULL;
            }
        }
    }
    //左右子树都有
    else if (TreeHasFull(&tempTree)) {
        //储存当前节点的左右子树地址
        pleft = pnode->left;
        pright = pnode->right;
        //删除的是根节点
        if (NULL == plast) {
            //将左子树根节点作为主树根节点
            tree->root = pleft;
            //将右子树接到左子树的右支最下端的最右端
            tempTree.root = pleft;
            toRightEnd(&tempTree);
            (tempTree.root)->right = pright;
        } else {
            //在左边
            if (atLeft(plast, pnode)) {
                //将右子树作为父节点的左子树
                plast->left = pright;
                //将左子树接到右子树的左支最下端的最左端
                tempTree.root = pright;
                toLeftEnd(&tempTree);
                (tempTree.root)->left = pleft;
            } else {  //在右边
                //将左子树作为父节点的右子树
                plast->right = pleft;
                //将右子树接到左子树的右支最下端的最右端
                tempTree.root = pleft;
                toRightEnd(&tempTree);
                (tempTree.root)->right = pright;
            }
        }
    }
    //左右子树只有一个
    else {
        //删除的是根节点
        if (NULL == plast) {
            if (NULL != pnode->left) {
                tree->root = pnode->left;
            } else {
                tree->root = pnode->right;
            }
        } else {
            //确定有的是左子树还是右子树
            if (atLeft(plast, pnode)) {
                //将其作为父节点的子树
                if (NULL != pnode->left) {
                    plast->left = pnode->left;
                } else {
                    plast->left = pnode->right;
                }
            } else {
                if (NULL != pnode->left) {
                    plast->right = pnode->left;
                } else {
                    plast->right = pnode->right;
                }
            }
        }
    }
    free(pnode);
    (tree->total)--;
    return true;
}
/*打印节点*/
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
/*删除所有节点*/
void DeleteAllTrnode(Tree *tree)
{
    freeTrnodes(tree);
    tree->root = NULL;
    tree->total = 0;
}


/*私有方法,不作为接口开放*/
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
static bool atLeft(const Trnode *plast, const Trnode *pnode)
{
    if (pnode == plast->left) {
        return true;
    } else {
        return false;
    }
}

static void toRightEnd(Tree *tree)
{
	//记录临时树的根节点
	Trnode *p = tree->root;

    if (TreeHasEmpty(tree)) {
        return;
    }
    if (NULL != p->right) {
        tree->root = p->right;
        toRightEnd(tree);
    }
    else {
        return;
    }
}
static void toLeftEnd(Tree *tree)
{
	//记录临时树的根节点
	Trnode *p = tree->root;

    if (TreeHasEmpty(tree)) {
        return;
    }
    if (NULL != p->left) {
        tree->root = p->left;
        toLeftEnd(tree);
    }
    else {
        return;
    }
}
//释放节点
static void freeTrnodes(Tree *tree)
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
        free(p);
		return ;
	} else {
		if (p->left != NULL) {  //左边有路,往左走
			tempTree.root = p->left;
		    freeTrnodes(&tempTree);
		}
		if (NULL != p->right) {  //右边有路,往右走
			tempTree.root = p->right;
			freeTrnodes(&tempTree);
		}
	}
    
    //递归处理节点都在递归后(返回前)处理, 或者在递归前处理, 避免重复调用
    free(p);
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
