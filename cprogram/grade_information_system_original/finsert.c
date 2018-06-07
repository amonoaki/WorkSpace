void finsert(STU *p)
{
	int i, status;
	printf("Now you can input the students' information(Enter 'CTRL-Z' to end your input):\n");
	for (i = 0; i < N && status != EOF; i++) {
		status = scanf("%s %s %f %f %f", &(p+i)->id, &(p + i)->name, &(p + i)->SUB_ONE,
		&(p + i)->SUB_TWO, &(p + i)->SUB_THREE);
		if (status != 5 && status != EOF) {
			printf("Input error!\n");
			break;
		}
	}
	while (getchar() != '\n') {
		;
	}
}

/*
与 append() 整合
-------->
可精确插入数据

*/
