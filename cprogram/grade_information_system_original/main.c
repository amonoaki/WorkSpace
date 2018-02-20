#include <stdio.h>
#include <string.h>

#define N 50

typedef struct Student {
	char id[20];
	char name[20];
	char clas[10];
	char tel[15];
	int grade;
}STU;

#include "finsert.c"
#include "ffind.c"
#include "fsort.c"
#include "fdelete.c"
#include "fappend.c"
#include "foutput.c"

void fhelp()
{
	printf("Options:\ni/I(����¼��)\tf/F(���ݲ���)\ts/S(��������)\nd/D(����ɾ��)\ta/A(����׷��)\to/O(����������ʾ)\nh/H(������ʾ)\t#(�˳�����)\n");
}


int main(void)
{
	char c, name1[20];
    int t;
	STU stu[N]={"\0"};
	STU *p = stu;
	fhelp();
	printf("Choose one option: ___\b\b");
	c = getchar();
	getchar();
	while (c != '#'){
		switch (c) {
		case 'i':
		case 'I': finsert(p); break;
		case 'f':
		case 'F':
			printf("Now you can input the student's name you want to find: ");
			gets(name1);
			t = ffind(p, name1);
			foutput( p, t, t); break;
		case 's':
		case 'S': fsort(p); break;
		case 'd':
		case 'D': fdelete(p); break;
		case 'a':
		case 'A': fappend(p); break;
		case 'o':
		case 'O':
		    printf("ѧ�� \t\t���� \t�༶ \t��ϵ�绰 \tѧ��\n");
		    foutput(p, 0, N-1); break;
		case 'h':
		case 'H': fhelp();break;
		default: printf("Sorry. Nothing to do. Try again.\n");
		}
		printf("---Completed---\n");
		printf("Choose one option: ___\b\b");
		c = getchar();
		getchar();
	}
	printf("Bye!\n");
	return 0;
}


//00205332 Bill S306 559-32665 45
/*
00101125 Amy S102 330-22568 32
00302132 Gate E326 111-35253 43
00214121 Linda V213 253-32265 50
*/
