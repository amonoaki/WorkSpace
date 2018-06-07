//menu.c
#include <stdio.h>
#include <stdlib.h>
#include "show.c"
#include "add.c"

void help() 
{
    printf("Options:\n");
    printf("*****\n");
}

int main(void)
{
    FILE *fp;
   
    char option;
    help();
    while (( option = getchar() ) != 'q') {
        while(getchar() != '\n') {
	    ;
	}
	if (( fp = fopen("grade.txt", "r+") ) == NULL) {
            printf("Open file error!\n");
	    exit(1);
        }
	switch(option) {
	    case 'a':
	    case 'A': add(fp);
		      break;
	    case 'h':
	    case 'H': help();
		      break;
	    case 's':
	    case 'S': show(fp);
		      break;
	    default: printf("Invalid option, please try again.\n");
		     break;
	}
	if (fclose(fp) != 0) {
	    printf("Close file error!\n");
	}
    }
    printf("Goodbye!\n");
    return 0;
}
