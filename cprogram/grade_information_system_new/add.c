//add.c
int add(FILE *fp)
{
    char str[20] = {'\0'};
    int grade;
    fseek(fp, 0L, SEEK_END);
    printf("Enter your input:\n");
    scanf("%d", &grade);
    fprintf(fp, "%d", grade);
    return 0;
}
