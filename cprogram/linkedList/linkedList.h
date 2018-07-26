#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct _node
{
    struct _node *plast;
    int value;
    struct _node *pnext;
} Node;

typedef struct _list
{
    struct _node *phead;
    struct _node *ptail;
} List;

//可被系统识别的选项
enum options{EXIT=-1, TIP=0, ADD=1, PRT=2, DEL=3};

//链表(Node-Link)
void addNode(List *list, int value);

int rmNodeValued(List *list, int value);
int rmNodeIndex(List *list, int total, int lowerLimit, int upperLimit);

//数据(user's data)
void prtTips();
int quit(const List *list);

void readData(List *list, int *total);
void saveData(const List *list);

void addData(List *list, int *total);
void prtData(const List *list);
void delData(List* list, int *total);

//工具
void freeNode(List *list, Node *p);
int getInt(int *tar, char *tip);
#endif