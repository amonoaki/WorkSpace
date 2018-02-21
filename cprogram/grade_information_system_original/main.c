#include <stdio.h>
#include <string.h>
#include "main.h"
#include "finsert.c"
#include "ffind.c"
#include "fsort.c"
#include "fdelete.c"
#include "fappend.c"
#include "fshow.c"
#include "calculate.c"

void fhelp()
{
	printf("Options:\n\
[1](insert data)        [2](find data)       [3](sort data)\n\
[4](delete data)        [5](append data)     [6](show data)\n\
[h](open help file)     [q](quit)\n");
}

int main(void)
{
	char option, name1[20];
    int t;
	STU stu[N] = {"\0"};
	STU *p = stu;
	fhelp();
	printf("Choose one option: ___\b\b");
	while (( option = getchar() ) != 'q'){
		while (getchar() != '\n') {
			;
		}
		switch (option) {
		case '1': finsert(p);
			  calculate(p); break;
		case '2':
			printf("Now you can input the student's name you want to find: ");
			gets(name1);
			t = ffind(p, name1);
			fshow( p, t, t); break;
		case '3': fsort(p); break;
		case '4': fdelete(p); break;
		case '5': fappend(p);
			  calculate(p); break;
		case '6':fshow(p, 0, N-1); break;
		case 'h': fhelp();break;
		default: printf("Sorry. No such option. Try again.\n");
		}
		printf("Choose one option: ___\b\b");
	}
	printf("Bye!\n");
	return 0;
}

/*
增加 使数据存入文件 功能

*/
//00205332 Bill 89 89 78
/*
00101125 Amy 88 98 67
00302132 Gate 89 67 87
00214121 Linda 90 97 68
*/
