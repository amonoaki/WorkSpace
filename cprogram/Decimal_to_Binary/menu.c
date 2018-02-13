#include <stdio.h>

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
      case '1': preConvert(1); break;
      case '2': preConvert(2); break;
      case 'h': menu(); break;
      default: printf("Input error. Please input '1', '2' or 'q'.\n"); break;
    }
    printf("Please choose an Option: ");
  }
  return 0;
}
