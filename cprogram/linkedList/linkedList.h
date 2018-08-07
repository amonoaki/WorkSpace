#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

typedef struct _node
{
    struct _node *plast;
    int value;  //可以加入其他各种属性
    struct _node *pnext;
} Node;

typedef struct _list
{
    struct _node *phead;
    struct _node *ptail;
    int total;
} List;

//可被系统识别的选项
enum options{EXIT=-1, TIP=0, ADD=1, PRT=2, DEL=3, SEA=4, MOD=5, INS=6};

//链表(Node-Link)
void InitializeList(List *list);

void AddNode(List *list, int value);

void InsertNode(List *list, int index);

int RmNodeValued(List *list, int value);
int RmNodeIndex(List *list, int lowerNumber, int upperNumber);

int SearchNodeValued(const List *list, int value, Node** pnodes);
int SearchNodeIndex(const List *list, int lowerNumber, int upperNumber, Node **pnodes);

void ModifyNode(Node **pnodes, int length, int beginNum);

void FreeAllNodes(const List *list);

//数据(user's data)
void prtTips();
void prtData(const List *list);
void prtDataInArray(const List *list, Node** pnodes, int length, int beginNum);

void readData(List *list);
void saveData(const List *list);

void addData(List *list);       //增
void delData(List* list);       //删（加入ID属性，可以根据ID删除）（目前根据序号、值删除）
void seaData(const List *list);  //查（同上）（目前根据序号、值查找）
void modData(const List *list);  //改（同上）（目前根据序号修改）
void insertData(List *list);    //插入

//工具
void freeNode(List *list, Node *p);
int getInt(int *tar, char *tip);
int confirm();
void addValue(List *list, char* tips);
void freeAllNodes(const List *list);
#endif