int fshow(STU *p, int i, int j)
{
    if (i < 0 || i > j || j < i || j >= N){
        printf(" Not found. Error\n");
        return -1;
    }
	for (; i <= j; i++) {
        if (strcmp( (p + i)->name, "\0") == 0)
            continue;
        else
            printf("%s \t%s \t%.2f \t%.2f \t%.2f \t%.2f \t%.2f\n", (p + i)->id, (p + i)->name,
            (p + i)->SUB_ONE, (p + i)->SUB_TWO, (p + i)->SUB_THREE,
            (p + i)->total, (p + i)->aver);
	}
	return 0;
}
