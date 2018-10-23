#ifndef _QUEUEQUEUE_H_
#define _QUEUEQUEUE_H_
#include <stdbool.h>
#include "queue.h"

#define NAME_LENGTH 20

//定义基本数据类型
typedef struct _itemQueue
{
    struct Queue *queue;
}ItemQueue;

typedef struct _nodeQueue
{
    struct _itemQueue item;
    struct _nodeQueue *pnext;
}NodeQueue;

typedef struct _queueQueue
{
    struct _nodeQueue *phead;
    struct _nodeQueue *ptail;
    int total;
}QueueQueue;


//声明队列具有的操作
void InitializeQueueQueue(QueueQueue *queue);
ItemQueue* NewDataQueue(Queue *item);
bool IsEmptyQueue(const QueueQueue *queue);  //检查队列是否为空
int GetLengthQueue(const QueueQueue *queue);  //得到队列长度

ItemQueue GetItemQueue(const QueueQueue *queue, int index);
void AppendQueue(QueueQueue *queue, ItemQueue item);  //队列增加值，只能在末尾追加
ItemQueue RemoveQueue(QueueQueue *queue);  //队列删除值，只能在头部删除

void TraverseQueue(QueueQueue *queue, void(*fun)(NodeQueue *node));  //遍历节点并执行回调函数

#endif
