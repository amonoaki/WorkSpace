void fsort(STU *p)
{
	STU t;
	int i, j, pm, m;
	for (i = 0; i < N-1; i++) {
		pm = (p + i)->grade;
		m = i;
		for (j = i + 1; j < N; j++) {
			if (pm < (p + j)->grade) {
				pm = (p + j)->grade;
				m = j;
			}
		}
		if (m != i) {
            t = *(p + i);
            *(p + i) = *(p + m);
            *(p + m) = t;
        }
	}
}
