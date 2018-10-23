/*驱动程序头文件*/
#ifndef _TEST_BINARY_TREE_H_
#define _TEST_BINARY_TREE_H_

#include "binaryTree.h"

enum options {QUIT=-1, HELP=0, ADD=1, SHOW=2, SEARCH=3, DELETE=4, PRINT_TO_SCREEN=5, PRINT_TO_FILE=6};

//函数原型
void printItems(const Tree *tree);  //遍历打印所有项
void addItems(Tree *tree);
void searchItem(const Tree *tree);
void deleteItem(Tree *tree);

void help();
bool quitConfirm ();

void readTreeFromFile(Tree *tree);
void saveTreeToFile(const Tree *tree);
#endif
