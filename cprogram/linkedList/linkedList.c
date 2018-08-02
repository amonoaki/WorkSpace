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
        statu = getInt(&opt, "要使用功能的序号");

        switch(opt) {
            case TIP: prtTips(); break;
            case ADD: addData(&list, &total); break;
            case PRT: prtData(&list); break;
            case DEL: delData(&list, &total); break;
            case SEA: seaData(&list, total); break;
            case MOD: modData(&list, total); break;
            case INS: insertData(&list, &total); break;
            case EXIT: 
                printf("确认退出？[y/n] ");
                statu = confirm(); 
                freeAllNodes(&list); break;
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
    printf("[0]显示提示\t [1]增加数据\t [2]显示数据\t [3]删除数据\t [4]查找数据\t [5]修改数据\t [6]插入数据\t [-1]退出\t\n");
}
//显示数据（标准输出）
void prtData(const List *list)
{
    int cnt = 0;
    Node *p = NULL;

    printf("序号\t 当前节点地址\t 上一个节点地址\t 当前节点的值\t 下一个节点的地址\n");
    for (p = list->phead; p; p = p->pnext) {
        printf("%-10d\t %-12p\t %-12p\t %-10d\t %-12p\n", cnt++, p, p->plast, p->value, p->pnext);
    }
    printf("共%d条记录\n\n", cnt);
}
//打印给定节点数组的数据，传入list, 节点数组，数组长度，开始的序号 （标准输出）
void prtDataInArray(const List *list, Node** pnodes, int length, int beginNum)
{
    int i, cnt = beginNum;

    printf("序号\t 当前节点地址\t 上一个节点地址\t 当前节点的值\t 下一个节点的地址\n");
    for (i = 0; i < length; i++) {
        printf("%-10d\t %-12p\t %-12p\t %-10d\t %-12p\n", cnt++, pnodes[i], pnodes[i]->plast, pnodes[i]->value, pnodes[i]->pnext);
    }
    printf("共%d条记录\n\n", cnt-beginNum);
}



//核心功能
//增
void addData(List *list, int *total)
{
    addvalue(list, total, "添加");
    saveData(list);
}
//插入
void insertData(List *list, int *total)
{
    int index;
    getInt(&index, "你要在哪个序号后添加?");

    if (index >= 0 && index < *total) {
        insertNode(list, total, index);
        saveData(list);
    } else if (index == *total) {
        addData(list, total);
    } else {
        printf("只有%d项数据，序号超出范围。\n", *total);
    }
}
//删
void delData(List* list, int *total)
{
    int cnt = 0, opt = 0;
    int value, lowerNumber, upperNumber;

    printf("[1]按值查找删除, [2]按索引区间删除; \n");
    while(getInt(&opt, "你的删除方式")) {
        if (opt == 1) {
            getInt(&value, "待删除节点的值");
            printf("确认删除？[y/n]");
            if (confirm() == -1) {
                cnt = rmNodeValued(list, *total, value);
                printf("删除了%d个节点\n", cnt);
            } else {
                printf("操作取消\n");
            }
            break;
        } else if (opt == 2) {
            getInt(&lowerNumber, "开始删除的索引值");
            getInt(&upperNumber, "停止删除的索引值");
            printf("确认删除？[y/n]");
            if (confirm() == -1) {
                cnt = rmNodeIndex(list, *total, lowerNumber, upperNumber);
                printf("删除了%d个节点\n", cnt);
            } else {
                printf("操作取消\n");
            }
            break;
        } else if (opt == -1) {
            break;
        } else {
            printf("抱歉，选项无效，请重试。\n");
            printf("[1]按值查找删除, [2]按索引区间删除; \n");
            continue;
        }
    }
    *total -= cnt;
    saveData(list);
}
//改
void modData(const List *list, int total)
{
    int lowerNumber, upperNumber, length, newValue;
    Node* pnodes[total];

    getInt(&lowerNumber, "开始修改的索引值");
    getInt(&upperNumber, "停止修改的索引值");
    if (length = searchNodeIndex(list, total, lowerNumber, upperNumber, pnodes)) {
        modifyNode(pnodes, length, lowerNumber);
        printf("全部修改完成\n");
        saveData(list);
    } else {
        printf("索引有误，操作取消\n");
    }
    
}
//查
void seaData(const List *list, int total)
{
    int opt, value, i, cnt = 0;
    Node* pnodes[total];
    int lowerNumber = 0, upperNumber = 0;

    printf("[1]按值查找查找, [2]按索引区间查找; \n");
    while(getInt(&opt, "你的查找方式")) {
        if (opt == 1) {
            getInt(&value, "待查找节点的值");
            cnt = searchNodeValued(list, value, pnodes);
            break;
        } else if (opt == 2) {
            getInt(&lowerNumber, "开始查找的索引值");
            getInt(&upperNumber, "停止查找的索引值");
            if ((cnt = searchNodeIndex(list, total, lowerNumber, upperNumber, pnodes)) == 0) {
                printf("索引有误\n");
            }
            break;
        } else if (opt == -1) {
            return;
        } else {
            printf("抱歉，选项无效，请重试。\n");
            printf("[1]按值查找查找, [2]按索引区间查找; \n");
            continue;
        }
    }
    prtDataInArray(list, pnodes, cnt, lowerNumber);
}





/*数据结构支持-链表*/
//新增一个节点，传入list，新增节点的值
void addNode(List *list, int value)
{
    //申请一块新内存，用于创建新节点
    Node *p = (Node*)malloc(sizeof(Node));
    if (p != NULL) {
        p->plast = list->ptail;
        p->value = value;
        p->pnext = NULL;
        
        if(list->phead == NULL) {   //无头节点时
            list->phead = list->ptail = p;
        } else {                    //存在头节点时
            list->ptail = (list->ptail)->pnext = p;
        }
    } else {
        exit(-1);
    }
}
//插入一个或多个节点（一段链表）, 传入插入位置的前节点地址、值value
void insertNode(List *list, int *total, int index)
{
    int i;
    Node *pindex = list->phead;

    //定位index指向的节点地址
    for (int i = 0; i < index; i++) {
        pindex = pindex->pnext;
    }

    //获得一段链表
    List tempList;
    tempList.phead = tempList.ptail = NULL;

    addvalue(&tempList, total, "插入");
    
    //更改临时链表首尾存储的地址
    (tempList.phead)->plast = pindex;
    (tempList.ptail)->pnext = pindex->pnext;
    //更改插入位置两个节点存储的地址
    (pindex->pnext)->plast = tempList.ptail;
    pindex->pnext = tempList.phead;
}
//遍历删除值为value的节点,传入list, total, 要删除的值
int rmNodeValued(List *list, int total, int value)
{
    Node* pnodes[total];
    int i, cnt = 0;

    cnt = searchNodeValued(list, value, pnodes);
    for (i = 0; i < cnt; i++) {
        freeNode(list, pnodes[i]);
    }

    return cnt;
}
//按索引区间删除数据，传入list,total，索引的上下限
//注意：在遍历删除的时候，把p给free掉以后，就无法通过p->pnext来找到p的下一个了，所以还是把要free的地址存到指针数组里比较方便
int rmNodeIndex(List *list, int total, int lowerNumber, int upperNumber)
{
    Node* pnodes[total];
    int i, cnt = 0;

    if (cnt = searchNodeIndex(list, total, lowerNumber, upperNumber, pnodes)) {
        for (i = 0; i < cnt; i++) {
            freeNode(list, pnodes[i]);
        }
        return cnt;
    } else {
        printf("索引有误\n");
        return 0;
    }
}
//按值查找，传入list, 传入要查找的值和节点地址数组，结果将保存在传入的节点地址数组中，返回查找的个数
int searchNodeValued(const List *list, int value, Node** pnodes)
{
    Node *p;
    int n = 0;

    for (p = list->phead; p; p = p->pnext) {
        if (p->value == value) {
            pnodes[n] = p;
            n++;
        }
    }

    return n;
}
//按索引区间查找，传入list,total，序号区间，一个指针数组，函数修改指针数组，由查找到的节点地址组成，越界返回0，成功返回数组长度
int searchNodeIndex(const List *list, int total, int lowerNumber, int upperNumber, Node **pnodes)
{
    int i, cnt = 0;
    Node *p = list->phead;
    
    //如果越界或索引错误，返回0;
    if ( lowerNumber < 0 || upperNumber > total-1 || lowerNumber > upperNumber ) {
        return 0;
    }

    //找出上下限之间的地址存入数组
    for (i = 0; i < lowerNumber; i++) {
        p = p->pnext;
    }

    for (i = lowerNumber; i <= upperNumber; i++) {
        pnodes[cnt] = p;
        cnt++;
        p = p->pnext;
    }
    
    return cnt;
}
//修改指定索引区间的节点的值
void modifyNode(Node **pnodes, int length, int beginNum)
{
    int i, newValue;

    for (i = 0; i < length; i++) {
        printf("这是原始值：\n序号：%-10d\t 值：%-12d\n", beginNum++, pnodes[i]->value);
        getInt(&newValue, "此项的新值");
        pnodes[i]->value = newValue;
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
//获得一个整数，传入目标变量地址和提示字符串，将最后一次scanf的返回值返回
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
//确认是否执行操作，用户输入y返回-1，否则返回1
int confirm()
{
    char choice;

    scanf("%c", &choice);
    if (choice == 'y' || choice == 'Y') {
        return -1;   
    } else {
        return 1;
    }
}
//给一段链表增加数据，输入链表及长度、提示字符
void addvalue(List *list, int *total, char* tips)
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
            addNode(list, number);
            cnt_y++;
            (*total)++;
        }
        statu = scanf(" %d", &number);
    }
    while (getchar() != '\n');  //消耗剩余整行字符
    printf("成功%s%d个数据， 其中%d处忽略了无效数据\n", tips, cnt_y, cnt_n);
}

void freeAllNodes(const List *list)
{
    Node *p = (list->phead)->pnext;

    for (; p->pnext != NULL; p = p->pnext) {
        free(p->plast);
    }
    free(p->plast);
    free(p);
}