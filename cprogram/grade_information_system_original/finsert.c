void finsert(STU *p)
{
	int i;
	char c = '\0';
	printf("Now you can input the students' information(Enter 'CTRL-Z' to end your input):\n");
	for (i = 0; i < N && c != EOF; i++) {
		c = scanf("%s %s %s %s %d", &(p+i)->id, &(p + i)->name, &(p + i)->clas, &(p + i)->tel, &(p + i)->grade);
	}
}
