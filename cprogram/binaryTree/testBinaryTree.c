#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "binaryTree.h"
#include "testBinaryTree.h"
#include "showTree.h"

static int getInt(int *tar, char *tip);
static bool confirm();
static void saveTree(FILE *pdata, const Tree *tree);

int main(void)
{
    bool quit = false;
    int option;

    Tree tree;
    InitializeTree(&tree);

    readTreeFromFile(&tree);

    printf("欢迎来到二叉树测试系统");
    help();

    do {
        getInt(&option, "你的选项");

        switch (option) {
            case HELP: help(); break;
            case SHOW: printItems(&tree); break;
            case ADD: addItems(&tree);  break;
            case SEARCH: searchItem(&tree); break;
            case DELETE: deleteItem(&tree); break;
            case QUIT: quit = quitConfirm(); break;
			case PRINT_TO_FILE: showTree(&tree, NULL); break;
			case PRINT_TO_SCREEN: showTree(&tree, stdout); break;
            default: printf("无效选项\n"); break;
        }
    } while(!quit);
    DeleteAllTrnode(&tree);
    printf("已退出\n");

    return 0;
}

//打印数据
void printItems(const Tree *tree)
{
    printf("\nname\t\t\t value\t\t Trnode\t\t\t left\t\t\t right\n\n");
    printTrnode(tree);
    printf("共%d条记录\n\n", TrnodesCount(tree));
}
//增加数据
void addItems(Tree *tree)
{
    if (TreeIsFull(tree)) {
        printf("空间已满, 无法继续输入\n");
        return;
    }

    char name[NAME_LENGTH];
    int value = 0;
    Item item;

    printf("增加: 输入name, value. 空格隔开, # 回车 结束\n");

    scanf("%s", name);
    while (0 != strcmp(name, "#")) {
        scanf("%d", &value);

        strcpy(item.name, name);
        item.value = value;

        if (false == AddTrnode(tree, item)) {
            break;
        }
        
        scanf("%s", name);
    }
    saveTreeToFile(tree);
}
//查找数据
void searchItem(const Tree *tree)
{
    char name[NAME_LENGTH];
    Trnode *pnode = NULL, *plast = NULL;

    printf("查找: 输入name:");
    scanf("%s", name);
    
    Item item;
    strcpy(item.name, name);
    item.value = -1;

    if (SearchTrnode(tree, item, &pnode, &plast)) {
        printf("\nname\t\t\t value\t\t left\t\t\t right\n\n");
        printf("%-20s\t %-10d\t %-15p\t %-15p\n",(pnode->item).name, (pnode->item).value, pnode->left, pnode->right);
    } else {
        printf("无结果\n");
    }
}
//删除数据
void deleteItem(Tree *tree)
{
    char name[NAME_LENGTH];

    printf("删除: 输入name:");
    scanf("%s", name);
    
    Item item;
    strcpy(item.name, name);
    item.value = -1;

    DeleteTrnode(tree, item);

    saveTreeToFile(tree);
}

//打印提示
void help()
{
    printf("可用选项: -1:退出 0:显示帮助 1:增加数据 2:显示数据 3:查找数据 4:删除数据 5:图形化打印数据到终端 6:图形化打印数据到文件\n");
}
//退出
bool quitConfirm ()
{
    printf("确认退出?[y/n]");
    return confirm();
}


//从文件读取数据 data.txt
void readTreeFromFile(Tree *tree)
{
    FILE *pdata = fopen("./data.txt", "a+");
    fseek(pdata, 0L, SEEK_SET);

    char name[NAME_LENGTH];
    int value, statu = -1;

    while ((statu = fscanf(pdata, "%s", name)) != EOF) {
        statu = fscanf(pdata, "%d", &value);

        Item item;
        strcpy(item.name, name);
        item.value = value;

        AddTrnode(tree, item);
    }

    fclose(pdata);
    printf("数据读取完毕, 共%d条记录\n", TrnodesCount(tree));
}

//保存数据到文件 data.txt
static void saveTree(FILE *pdata, const Tree *tree)
{

    if (TreeIsEmpty(tree)) {
        // fprintf(stderr, "Empty tree, no data.\n");
        return;
    }

	//创建临时树作为参数树的拷贝
	Tree tempTree;
	InitializeTree(&tempTree);
	tempTree = *tree;

	//记录临时树的根节点
	Trnode *p = tempTree.root;

	//递归遍历
	if (TreeHasEmpty(&tempTree)) {  //无路可走,返回上一层
        fprintf(pdata, "%s %d ",(p->item).name, (p->item).value);
		return ;
	} else {
        //这里必须在递归前处理, 打印的顺序要和当初输入的顺序相同, 否则树的结构将被改变
        fprintf(pdata, "%s %d ",(p->item).name, (p->item).value);
		if (p->left != NULL) {  //左边有路,往左走
			tempTree.root = p->left;
		    saveTree(pdata, &tempTree);
		}
		if (NULL != p->right) {  //右边有路,往右走
			tempTree.root = p->right;
			saveTree(pdata, &tempTree);
		}
	}  
	return ;
}
void saveTreeToFile(const Tree *tree)
{
    FILE *pdata = fopen("./data.txt", "w");

    saveTree(pdata, tree);

    fclose(pdata);
}



/*工具*/
//获得一个整数，传入目标变量地址和提示字符串，将最后一次scanf的返回值返回
static int getInt(int *tar, char *tip)
{
    int statu;

    printf("请输入%s：", tip);
    while ((statu = scanf("%d", tar)) != 1) { //获得符合要求的输入为止
        printf("抱歉，%c非法。此处需要一个整数。\n", getchar());
        while (getchar() != '\n');  //消耗剩余整行字符
        printf("请输入%s：", tip);
    }
    while (getchar() != '\n');  //消耗剩余整行字符

    return statu;
}
//确认是否执行操作，用户输入y返回-1，否则返回1
static bool confirm()
{
    char choice;

    scanf("%c", &choice);
    if (choice == 'y' || choice == 'Y') {
        return true;   
    } else {
        return false;
    }
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


