#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    List list;
    list.phead = list.ptail = NULL;
    int total = 0;

    int opt = -1, statu = -1;

    printf("欢迎来到链表测试系统！\n");
    readData(&list, &total);
    prtTips();
    
    do {
        statu = getInt(&opt, "你的选项");

        switch(opt) {
            case TIP: prtTips(); break;
            case ADD: addData(&list, &total); break;
            case PRT: prtData(&list); break;
            case DEL: delData(&list, &total); break;
            case EXIT: statu = quit(&list); break;
            default: printf("抱歉，%d为非法选项。忘记选项了？尝试[0]显示系统帮助。\n", opt);
        }
    } while(statu == 1);
    printf("已退出。\n");

    return 0;
}

/*数据准备*/
//保存数据（文件输出）
void saveData(const List *list)
{
    FILE *pf;
    Node *p = list->phead;

    //以覆盖模式w打开文件linkedList.data，此模式会处理文件不存在的情况（即新建）
    if ((pf = fopen("./linkedList.data", "w")) == NULL) {
        printf("打开文件失败\n");
        exit(EXIT_FAILURE);
    }
    //将数据写入文件
    for (; p; p = p->pnext) {
        fprintf(pf, "%d ",p->value);
    }
    fclose(pf);
}
//读入数据（文件读入）
void readData(List *list, int *total)
{
    FILE *pf;
    int value;
        
    //以只读模式r打开文件linkedList.data
    if ((pf = fopen("./linkedList.data", "r")) == NULL) {
        printf("未检测到已有数据，欢迎首次使用...\n");
        saveData(list);
    } else {
        while (fscanf(pf, "%d", &value) == 1) {
                addNode(list, value);
                (*total)++;
        }
        printf("数据已读入...\n");
    }
    fclose(pf);
}

/*系统功能*/
//显示提示
void prtTips()
{
    printf("[0]显示提示\t [1]增加数据\t [2]显示数据\t [3]删除数据\t [-1]退出\t\n");
}
//退出
int quit(const List *list)
{
    char choice;

    printf("确认退出？[y/n] ");
    scanf("%c", &choice);
    if (choice == 'y' || choice == 'Y') {
        saveData(list);
        return -1;   
    } else {
        return 1;
    }
}
//显示数据（标准输出）
void prtData(const List *list)
{
    int cnt = 0;
    Node *p = list->phead;

    printf("节点序号\t 当前节点地址\t 上一个节点地址\t 当前节点的值\t 下一个节点的地址\n");
    for (; p; p = p->pnext) {
        printf("%-10d\t %-12p\t %-12p\t %-10d\t %-12p\n", cnt++, p, p->plast, p->value, p->pnext);
        // printf("%d ", p->value);
    }
    putchar('\n');
}
//核心功能
//增
void addData(List *list, int *total)
{
    int number = 0, statu = 0, cnt_y = 0, cnt_n = 0;

    printf("请输入要添加的数据(-1结束):\n");
    statu = scanf(" %d", &number);
    while(number != -1) {
        if (statu != 1) {
            cnt_n++;
            while (getchar() != '\n');  //消耗剩余整行字符
            printf("你输入了无效字符，%d以后的所有字符已被跳过\n请继续输入(-1结束):\n", number);
        } else {
            addNode(list, number);
            cnt_y++;
            (*total)++;
        }
        statu = scanf(" %d", &number);
    }
    while (getchar() != '\n');  //消耗剩余整行字符
    saveData(list);
    printf("成功添加%d个数据， 其中%d处忽略了无效数据\n", cnt_y, cnt_n);
}
//删
void delData(List* list, int *total)
{
    int cnt = 0, opt = 0;
    int value, lowerLimit, upperLimit;

    printf("[1]按值查找删除, [2]按索引区间删除; \n");
    while(getInt(&opt, "你的删除方式")) {
        if (opt == 1) {
            getInt(&value, "待删除节点的值");
            cnt = rmNodeValued(list, value);
            break;
        } else if (opt == 2) {
            getInt(&lowerLimit, "开始删除的索引值");
            getInt(&upperLimit, "停止删除的索引值");
            cnt = rmNodeIndex(list, *total, lowerLimit, upperLimit);
            break;
        } else {
            printf("抱歉，选项无效，请重试。\n");
            printf("[1]按值查找删除, [2]按索引区间删除; \n");
            continue;
        }
    }
    if (cnt == -1) {
        cnt = 0;
    }
    *total -= cnt;
    saveData(list);
    printf("成功删除%d个节点\n", cnt);
}

/*数据结构支持-链表*/
void addNode(List *list, int value)
{
    //申请一块新内存，用于创建新节点
    Node *p = (Node*)malloc(sizeof(Node));
    p->plast = list->ptail;
    p->value = value;
    p->pnext = NULL;
    
    if(list->phead == NULL) {   //无头节点时
        list->phead = list->ptail = p;
    } else {                    //存在头节点时
        list->ptail = (list->ptail)->pnext = p;
    }
}
//遍历删除值为value的节点
int rmNodeValued(List *list, int value)
{
    Node *p;
    int cnt = 0;

    for (p = list->phead; p; p = p->pnext) {
        if (p->value == value) {
            freeNode(list, p);
            cnt++;
        }
    }

    return cnt;
}
//按索引区间删除数据
int rmNodeIndex(List *list, int total, int lowerLimit, int upperLimit)
{
    int i, cnt = 0;
    Node *p = list->phead;

    if ( lowerLimit > 0 && upperLimit < total && lowerLimit <= upperLimit ) {
        //定位
        for (i = 0; i < lowerLimit; i++) {
            p = p->pnext;
        }
        //删除
        for (i = lowerLimit; i <= upperLimit; i++) {
            freeNode(list, p);
            cnt++;
            p = p->pnext;
        }
        return cnt;
    } else {
        printf("lowerLimit=%d, upperLimit=%d, total=%d\n", lowerLimit, upperLimit, total);
        printf("索引无效，请检查重试\n");
        return -1;
    }
}

/*工具*/
//释放节点空间并拼接链表
void freeNode(List *list, Node *p)
{
    if (p->plast != NULL) {
        (p->plast)->pnext = p->pnext;
    } else {
        list->phead = p->pnext;
    }
    if (p->pnext != NULL) {
        (p->pnext)->plast = p->plast;
    } else {
        list->ptail = p->plast;
    }
    free(p);
}
//获得一个整数
int getInt(int *tar, char *tip)
{
    int statu;

    printf("请输入%s：", tip);
    while ((statu = scanf("%d", tar)) != 1) { //获得符合要求的输入为止
        printf("抱歉，%c非法。此处需要一个整数。\n", getchar());
        while (getchar() != '\n');  //消耗剩余整行字符
        printf("请输入你的选项：");
    }
    while (getchar() != '\n');  //消耗剩余整行字符

    return statu;
}