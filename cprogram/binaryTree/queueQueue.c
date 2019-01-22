#include "queueQueue.h"
#include <stdio.h>
#include <stdlib.h>

//获取队列的状态
bool IsEmptyQueue(const QueueQueue *queue)
{
    if (0 == queue->total) {
        return true;
    } else {
        return false;
    }
}

int GetLengthQueue(const QueueQueue *queue)
{
    return queue->total;
}

//初始化队列，传入Queue进行初始化
void InitializeQueueQueue(QueueQueue *queue)
{
    queue->phead = queue->ptail = NULL;
    queue->total = 0;
}

//新建数据
ItemQueue* NewDataQueue(Queue *data)
{
    ItemQueue *item = (ItemQueue*) malloc(sizeof(ItemQueue));

    item->queue = data;

    return item;
}

//追加一个节点，传入queue和数据item
void AppendQueue(QueueQueue *queue, ItemQueue item)
{
    //申请一块新内存，用于创建新节点
    NodeQueue *p = (NodeQueue*)malloc(sizeof(NodeQueue));
    if (p != NULL) {
        p->item = item;
        p->pnext = NULL;
        
        if(queue->phead == NULL) {   //无头节点时
            queue->phead = queue->ptail = p;
        } else {                    //存在头节点时
            queue->ptail = (queue->ptail)->pnext = p;
        }
        (queue->total)++;  //计数器加一
    } else {
        printf("内存不足!\n");
        exit(1);
    }
}

ItemQueue GetItemQueue(const QueueQueue *queue, int index)
{
	if (index >= 0 && index < GetLengthQueue(queue)) {
		NodeQueue *p = queue->phead;

		while (index > 0) {
			p = p->pnext;
			index--;
		}

		return p->item;
	}
}

//删除一个节点，从头部。使用时要排除没有节点时的情况。
ItemQueue RemoveQueue(QueueQueue *queue)
{
    if (!IsEmptyQueue(queue)) {
        NodeQueue *p = queue->phead;
        ItemQueue item = p->item;

        if (p != queue->ptail) {
            queue->phead = p->pnext;
        } else {
            queue->phead = queue->ptail = NULL;
        }
        free(p);
        (queue->total)--;
     
        return item;
    }
}

//把函数fun应用于每一个节点
void TraverseQueue(QueueQueue *queue, void (*fun)(NodeQueue *node))
{
    NodeQueue *p = queue->phead;

    while(p != NULL) {
        fun(p);
        p = p->pnext;
    }
}
