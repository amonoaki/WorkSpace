int ffind(STU *p, char name1[])
{
	int i;
	for (i = 0; i < N; i++) {
		if (strcmp((p + i)->name, name1) == 0) {
			return i;
		}
	}
	return -1;
}

/*
按学号查找
------->
按总分、 平均分查找
------->
按单科成绩查找

*/
