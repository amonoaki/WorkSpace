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
enum options{EXIT=-1, TIP=0, ADD=1, PRT=2, DEL=3, SEA=4};

//链表(Node-Link)
void addNode(List *list, int value);

int rmNodeValued(List *list, int total, int value);
int rmNodeIndex(List *list, int total, int lowerNumber, int upperNumber);
int searchNodeValued(const List *list, int value, Node** pnodes);
int searchNodeIndex(const List *list, int total, int lowerNumber, int upperNumber, Node **pnodes);

//数据(user's data)
void prtTips();
void prtData(const List *list);
void prtDataInArray(const List *list, Node** pnodes, int length, int beginNum);

void readData(List *list, int *total);
void saveData(const List *list);

void addData(List *list, int *total);
void delData(List* list, int *total);
void seaData(const List *list, int total);

//工具
void freeNode(List *list, Node *p);
int getInt(int *tar, char *tip);
int confirm();
#endif