int calculate(STU *p)
{
    int i = 0;
    float sum = 0, aver = 0;
    for (i = 0; i < N; i++) {
	    sum = 0;
        sum = (p + i)->SUB_ONE + (p + i)->SUB_TWO + (p + i)->SUB_THREE;
        aver = sum / (float)SUB;
	    (p + i)->total = sum;
	    (p + i)->aver = aver;
    }
    return 0;
}
