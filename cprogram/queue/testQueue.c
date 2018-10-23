#include "testQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void)
{
    Queue queue;
    bool quit = true;
    int option = 0;

    InitializeQueue(&queue);

    while(quit) {
        printf("输入选项(1:追加 2:头删除 3:打印数据 -1:退出): ");
        scanf("%d", &option);

        switch (option) {
            case 1: appendData(&queue, "追加"); break;
            case 2: removeData(&queue); break;
            case 3: printData(&queue); break;
            case -1: quit = false; break;
            default: printf("无效选项\n"); break;
        }
    }

    return 0;
}

//给一段队列追加数据，输入提示字符
void appendData(Queue *queue, char* tips)
{
    int number = 0, statu = 0, cnt_y = 0, cnt_n = 0;

    printf("请输入要%s的数据(-1结束):\n", tips);
    statu = scanf(" %d", &number);
    while(number != -1) {
        if (statu != 1) {
            cnt_n++;
            while (getchar() != '\n');  //消耗剩余整行字符
            printf("你输入了无效字符，%d以后的所有字符已被跳过\n请继续输入(-1结束):\n", number);
        } else {
            Data data = NewData("test", number);
            Append(queue, data);
            cnt_y++;
        }
        statu = scanf(" %d", &number);
    }
    while (getchar() != '\n');  //消耗剩余整行字符
    printf("成功%s%d个数据， 其中%d处忽略了无效数据\n", tips, cnt_y, cnt_n);
}

//删除队列头数据
void removeData(Queue *queue)
{
    if (GetLength(queue) != 0) {
        Data data = Remove(queue);
        printf("删除了值%d\n", data.value);
    } else {
        return;
    }
}

void print(Node *node)
{
    printf("p:%p\t value:%d\t pnext:%p\n", node, node->data.value, node->pnext);
}

void printData(Queue *queue)
{
    Traverse(queue, print);
    printf("total:%d\n", GetLength(queue));
}
