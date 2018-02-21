void fappend(STU *p)
{
    int i, status;
    for (i=0; i < N; i++){
        if (strcmp( (p + i)->name, "\0") != 0)
            continue;
        else{
            printf("Now you can input the information that you want to append: \n");
            status = scanf("%s %s %f %f %f", &(p+i)->id, &(p + i)->name, &(p + i)->SUB_ONE,
    		&(p + i)->SUB_TWO, &(p + i)->SUB_THREE);
            if (status != 5) {
                printf("Input error!\n");
            }
            break;
        }
    }
}
