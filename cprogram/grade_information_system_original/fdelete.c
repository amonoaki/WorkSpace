int fdelete(STU *p)
{
	int i;
	char name1[20];
	printf("Now you can input the student's name that you want to delete: ");
	gets(name1);
	while (1){
        i = ffind(p, name1);
        if (i == -1)
            return 0;
        (p + i)->SUB_ONE = 0;
	    (p + i)->SUB_TWO = 0;
	    (p + i)->SUB_THREE = 0;
	    (p + i)->total = 0;
	    (p + i)->aver = 0;
        strcpy((p + i)->id, "\0");
        strcpy((p + i)->name, "\0");

        fsort(p);
	}
	return 0;
}

/*
增加 按其他方式删除 功能 ---->  与 ffind() 结合， 因此改造 ffind() 即可

*/
