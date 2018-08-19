#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "binaryTree.h"
#include "testBinaryTree.h"
//#include "showTree.h"

static void help()
{
    printf("可用选项: -1:退出 0:显示帮助 1:增加数据 2:显示数据 3:查找数据\n");
}

int main(void)
{
    bool quit = false;
    int option;

    Tree tree;
    InitializeTree(&tree);

    printf("欢迎来到二叉树测试系统");
    help();

    do {
        printf("输入你的选项:");
        scanf("%d", &option);

        switch (option) {
            case HELP: help(); break;
            case SHOW: printItems(&tree); break;
            case ADD: addItems(&tree); break;
            case SEARCH: searchItem(&tree); break;
            case QUIT: quit = true; break;
            default: printf("无效选项\n"); break;
        }
    } while(!quit);
    
    printf("已退出\n");

    return 0;
}
void printItems(const Tree *tree)
{
    printf("\nname\t\t\t value\t\t Trnode\t\t\t left\t\t\t right\n\n");
    printTrnode(tree);
    printf("共%d条记录\n\n", TrnodesCount(tree));
}

void addItems(Tree *tree)
{
    char name[NAME_LENGTH];
    int value = 0;
    Item item;

    printf("增加: 输入name, value. 空格隔开, 任意字符串加-1 结束\n");

    scanf("%s %d", name, &value);
    while (value != -1) {
        
        strcpy(item.name, name);
        item.value = value;

        AddTrnode(tree, item);
        
        scanf("%s %d", name, &value);

    }
}

void searchItem(const Tree *tree)
{
    char name[NAME_LENGTH];
    Trnode *pnode = NULL, *plast = NULL;

    printf("查找: 输入name:");
    scanf("%s", name);
    
    if (SearchTrnode(tree, name, &pnode, &plast)) {
        printf("\nname\t\t\t value\t\t left\t\t\t right\n\n");
        printf("%-20s\t %-10d\t %-15p\t %-15p\n",(pnode->item).name, (pnode->item).value, pnode->left, pnode->right);
    } else {
        printf("无结果\n");
    }
}

void readTreeFromFile()
{

}

void saveTreeToFile()
{

}

/*
int main(void)
{
    Tree tree;
    int i;

    Item items[5];
//    items[5]{"AAA", 0, "bbb", 1, "Abb", 2, "bAa", 3, "AbA", 4};
    strcpy(items[0].name, "AAA");
    strcpy(items[1].name, "bbb");
    strcpy(items[2].name, "Abb");
    strcpy(items[3].name, "bAa");
    strcpy(items[4].name, "AbA");

    items[0].value = 0;
    items[1].value = 1;
    items[2].value = 2;
    items[3].value = 3;
    items[4].value = 4;

    InitializeTree(&tree);
    for (i = 0; i < 5; i++) {
        AddTrnode(&tree, &items[i]);
    }

    printf("TreeIsEmpty: %d\n", TreeIsEmpty(&tree));
    printf("TreeHasEmpty: %d\n", TreeHasEmpty(&tree));
    printf("TreeIsFull: %d\n", TreeIsFull(&tree));
    printf("TreeHasFull: %d\n", TreeHasFull(&tree));


    printf("TrnodesCount: %d\n", TrnodesCount(&tree));

    printItems(&tree);

//    int floor = 1, maxrow = 1;
//    countRow(&tree, &floor, &maxrow);
//    printf("maxrow: %d\n", maxrow);

//    showTree(&tree);

    return 0;
}
*/


