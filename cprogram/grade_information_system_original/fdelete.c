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
        (p + i)->grade = 0;
        strcpy((p + i)->id, "\0");
        strcpy((p + i)->name, "\0");
        strcpy((p + i)->clas, "\0");
        strcpy((p + i)->tel, "\0");
        fsort(p);
	}
}
