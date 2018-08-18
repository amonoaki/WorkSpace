#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "binaryTree.h"
#include "testBinaryTree.h"
//#include "showTree.h"




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

static void printItem(const Item item)
{
	printf("name: %s, value: %d\n", item.name, item.value);
}

void printItems(const Tree *tree)
{
	TraverseWithParameter(tree, &printItem);
}

void readTreeFromFile()
{

}

void saveTreeToFile()
{

}
