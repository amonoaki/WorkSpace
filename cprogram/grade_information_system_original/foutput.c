int foutput(STU *p, int i, int j)
{
    if (i < 0 || i > j || j < i || j >= N){
        printf(" Not found. Error\n");
        return -1;
    }
	for (; i <= j; i++) {
        if (strcmp( (p + i)->name, "\0") == 0)
            continue;
        else
            printf("%s \t%s \t%s \t%s \t%d\n", (p + i)->id, (p + i)->name, (p + i)->clas, (p + i)->tel, (p + i)->grade);
	}
	return 0;
}
