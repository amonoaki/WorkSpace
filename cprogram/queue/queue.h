#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <stdbool.h>

#define NAME_LENGTH 20

//定义基本数据类型
typedef struct _data
{
    char name[NAME_LENGTH];
    int value;
} Data;

typedef struct _node
{
    struct _data data;
    struct _node *pnext;
} Node;

typedef struct _queue
{
    struct _node *phead;
    struct _node *ptail;
    int total;
} Queue;


//声明队列具有的操作
void InitializeQueue(Queue *queue);
Data NewData(const char* name, int number);
bool IsEmpty(const Queue *queue);  //检查队列是否为空
int GetLength(const Queue *queue);  //得到队列长度

void Append(Queue *queue, Data data);  //队列增加值，只能在末尾追加
Data Remove(Queue *queue);  //队列删除值，只能在头部删除

void Traverse(Queue *queue, void (*fun)(Node *node));  //遍历节点并执行回调函数

#endif
