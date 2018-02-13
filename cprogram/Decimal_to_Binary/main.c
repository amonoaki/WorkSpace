#include "db.h"
#include "db_convert.c"
#include "bd_convert.c"

void menu() {
  printf("1-Convert Decimal to Binary;\n");
  printf("2-Convert Binary to Decimal;\n");
  printf("'h'-Help;\n");
  printf("'q'-Quit.\n");
}

int main(void)
{
  char option;
  menu();
  printf("Please choose an Option: ");
  while(( option = getchar() ) != 'q'){
    while (getchar() != '\n'){
      ;
    }
    switch (option) {
      case '1': pre_db_convert(); break;
      case '2': pre_bd_convert(); break;
      case 'h': menu(); break;
      default: printf("Input error. Please input '1', '2' or 'q'.\n"); break;
    }
    printf("Please choose an Option: ");
  }
  printf("Goodbye!\n");
  return 0;
}
