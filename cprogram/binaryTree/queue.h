#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <stdbool.h>
#include "binaryTree.h"


typedef struct _node
{
    struct _item item;
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
Item* NewData(const char* name, int number);
Queue* NewQueue();
bool IsEmpty(const Queue *queue);  //检查队列是否为空
int GetLength(const Queue *queue);  //得到队列长度

void Append(Queue *queue, Item item);  //队列增加值，只能在末尾追加
Item Remove(Queue *queue);  //队列删除值，只能在头部删除

void Traverse(Queue *queue, void (*fun)(Node *node));  //遍历节点并执行回调函数

#endif