//show.c
int show(FILE *fp)
{
    char c;
    while(( c = getc(fp) ) != EOF) {
        putchar(c);
    }
    return 0;
}
