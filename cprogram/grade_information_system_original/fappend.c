void fappend(STU *p)
{
    int i;
    for (i=0; i < N; i++){
        if (strcmp( (p + i)->name, "\0") != 0)
            continue;
        else{
            printf("Now you can input the information that you want to append: \n");
            scanf("%s %s %s %s %d", &(p+i)->id, &(p + i)->name, &(p + i)->clas, &(p + i)->tel, &(p + i)->grade);
            getchar();
            break;
        }
    }
}
