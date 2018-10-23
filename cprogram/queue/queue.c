#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//获取队列的状态
bool IsEmpty(const Queue *queue)
{
    if (0 == queue->total) {
        return true;
    } else {
        return false;
    }
}

int GetLength(const Queue *queue)
{
    return queue->total;
}

//初始化队列，传入Queue进行初始化
void InitializeQueue(Queue *queue)
{
    queue->phead = queue->ptail = NULL;
    queue->total = 0;
}

//新建数据
Data NewData(const char* name, int number)
{
    Data *data = (Data*) malloc(sizeof(Data));

    strcpy(data->name, name);
    data->value = number;

    return (*data);
}

//追加一个节点，传入queue和数据data
void Append(Queue *queue, Data data)
{
    //申请一块新内存，用于创建新节点
    Node *p = (Node*)malloc(sizeof(Node));
    if (p != NULL) {
        p->data = data;
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

//删除一个节点，从头部。使用时要排除没有节点时的情况。
Data Remove(Queue *queue)
{
    if (!IsEmpty(queue)) {
        Node *p = queue->phead;
        Data data = p->data;

        if (p != queue->ptail) {
            queue->phead = p->pnext;
        } else {
            queue->phead = queue->ptail = NULL;
        }
        free(p);
        (queue->total)--;
     
        return data;
    }
}

//把函数fun应用于每一个节点
void Traverse(Queue *queue, void (*fun)(Node *node))
{
    Node *p = queue->phead;

    while(p != NULL) {
        fun(p);
        p = p->pnext;
    }
}
