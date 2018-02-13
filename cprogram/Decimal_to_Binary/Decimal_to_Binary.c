#include "db.h"

void preConvert(int option)
{
  //the #define part
  if (option == 1){
    #define FIRST "Decimal"
    #define SECOND "Binary"
  }
  else if (option == 2){
    #ifndef FIRST
    #define FIRST "Binary"
    #endif
    #ifndef SECOND
    #define SECOND "Decimal"
    #endif
  }
  else {
    return;
  }

  int d_num = 0, status = 0, i = 0, c_flag = 1, b_num[LEN] = {'0'};
  char c;

  while (1){
    d_num = 0;
    status = 0;
    c_flag = 1;
    for (i = 0; i < LEN; i++){
      b_num[i] = 0;
    }
    //get input
    printf("Please input a %s number(only interger, and enter 'q' to quit): ", FIRST);
    if (option == 1){
      status = scanf("%d", &d_num);
    }
    else if (option == 2){
      for (i = 0; i < LEN; i++){
        status = scanf("%1d", &b_num[i]);
        if (b_num[i] == 2) {
          b_num[i] = -1;
          break;
        };
      }
    }
    //the good input
    if (status == 1){
      while (getchar() != '\n'){
        ;
      }
      //print begin
      printf("%s:", FIRST);

      if (option == 1){
        db_convert(d_num, b_num);
        printf("%d", d_num);
      }
      else if (option == 2){
        d_num = bd_convert(b_num);
        for (i = 0; i < LEN && b_num[i] != -1; i++){
        printf("%d", b_num[i]);
        }
      }

      printf(" --> %s:", SECOND);

      if (option == 1){
  	    for (i = 0; i < LEN; i++) {
  			  printf("%d", b_num[i]);
  			  if ((i+1) % 8 == 0) {
  				putchar(' ');
  			  }
  	    }
      }
      else if (option == 2){
        printf("%d", d_num);
      }

	    putchar('\n');
    }
    //print end
    //the bad input
    else{
      while (c = getchar()){
        if (c == 'q' && c_flag == 1){
          while (getchar() != '\n') {
            ;
          }
          printf("Goodbye!\n");
          c_flag = 0;
          return;  //it's the end way
        }
		    else if (c == '\n') {
			    break;
		    }
		    else{
          putchar(c);
        }
      }
      printf(" is not a interger, please try again.\n");
    }
    //back to get input
  }
}

void db_convert(int d_num, int b_num[])
{
  int i = 0, pre_num = d_num;
  for(i = 0; pre_num != 1; i++){
    pre_num = d_num / (int)pow(2, i);
    if (pre_num % 2){
      *(b_num + LEN - 1 - i) = 1;
    } else{
      *(b_num + LEN - 1 - i) = 0;
    }
  }
}

int bd_convert(int b_num[])
{
  int i = 0, d_num = 0, b_num_lenth = 0;
  for (i = 0; i < LEN && b_num[i] != -1; i++){
    b_num_lenth++;
  }
  for (i = 0; i < b_num_lenth; i++){
    d_num += b_num[i] * pow(2, b_num_lenth - 1 - i);
  }
  return d_num;
}
