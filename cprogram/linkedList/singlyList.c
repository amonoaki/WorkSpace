#include <stdio.h>
#include <stdlib.h>

/*
 * 循环单链表
 */

//node
typedef struct __node {
    int value;
    struct __node *next;
} Node;

//singlyLink
typedef struct __singlyLink{
    struct __node *head;
    struct __node *tail;
} SinglyList;

//initiate
void initiate(SinglyList *singlyList)
{
    singlyList->head = NULL;
    singlyList->tail = NULL;
}

//add
void insert(int num, SinglyList *singlyList)
{
    Node *p = (Node*) malloc(sizeof(Node));
    p->value = num;
    p->next = singlyList->head;

    if (singlyList->head == NULL) {
        singlyList->head = singlyList->tail = p;
    } else {
        singlyList->tail->next = p;
        singlyList->tail = p;
    }
}

//print list
void print(SinglyList *singlyList)
{
    Node *p = singlyList->head;
    while (p != NULL) {
        printf("p:%p, value:%d, next:%p\n", p, p->value, p->next);
        if (p == singlyList->tail) break;
        p = p->next;
    }
}

int main(void)
{
    SinglyList singlyList;
    initiate(&singlyList);

    int nums[10]={1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int i = 0; i < 10; i++) {
        insert(nums[i], &singlyList);
    }
    print(&singlyList);

    return 0;
}
