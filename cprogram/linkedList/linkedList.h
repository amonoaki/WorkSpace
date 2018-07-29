#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct _node
{
    struct _node *plast;
    int value;
    //还可以加入其他各种属性
    struct _node *pnext;
} Node;

typedef struct _list
{
    struct _node *phead;
    struct _node *ptail;
} List;

//可被系统识别的选项
enum options{EXIT=-1, TIP=0, ADD=1, PRT=2, DEL=3, SEA=4, MOD=5};

//链表(Node-Link)
void addNode(List *list, int value);

int rmNodeValued(List *list, int total, int value);
int rmNodeIndex(List *list, int total, int lowerNumber, int upperNumber);
int searchNodeValued(const List *list, int value, Node** pnodes);
int searchNodeIndex(const List *list, int total, int lowerNumber, int upperNumber, Node **pnodes);
void modifyNode(Node **pnodes, int length, int beginNum);

//数据(user's data)
void prtTips();
void prtData(const List *list);
void prtDataInArray(const List *list, Node** pnodes, int length, int beginNum);

void readData(List *list, int *total);
void saveData(const List *list);

void addData(List *list, int *total);       //增
void delData(List* list, int *total);       //删（加入ID属性，可以根据ID删除）（目前根据序号、值删除）
void seaData(const List *list, int total);  //查（同上）（目前根据序号、值查找）
void modData(const List *list, int total);  //改（同上）（目前根据序号修改）

//工具
void freeNode(List *list, Node *p);
int getInt(int *tar, char *tip);
int confirm();
#endif