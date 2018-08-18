#ifndef _SHOW_TREE_H_
#define _SHOW_TREE_H_

#define WIDTH 4  //单位宽度空格数

#include "binaryTree.h"
#include "stdio.h"

void countRow(const Tree *tree, int *floor, int *maxrow);
void showTree(const Tree *tree);

void fileInsert(FILE *fp, const char *str);

#endif
