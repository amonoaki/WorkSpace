#include <stdio.h>
#include <math.h>
#define LEN 32

void convert(int d_num, char b_num[]);

int main(void)
{
  int d_num = 0, status = 0, i = 0, c_flag = 1;
  char c, b_num[LEN] = {'0'};
  while (1){
    d_num = 0;
    status = 0;
    c_flag = 1;
    for (i = 0; i < LEN - 1; i++){
      b_num[i] = '0';
    }
    //get input
    printf("Please input a Decimal number(only interger, and enter 'q' to quit): ");
    status = scanf("%d", &d_num);
    //the good input
    if (status == 1){
      while (getchar() != '\n'){
        ;
      }
      convert(d_num, b_num);
      printf("Decimal:%d --> Binary:", d_num);
	  for (i = 0; i < LEN && b_num[i] != '\0'; i++) {
			 putchar(b_num[i]);
			 if ((i+1) % 8 == 0) {
				 putchar(' ');
			 }
	  }
	  putchar('\n');
    }
    //the bad input
    else{
      while (c = getchar()){
        if (c == 'q' && c_flag == 1){
          printf("Goodbye!\n");
          c_flag = 0;
          return 0;  //it's the end way
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
  return 0;
}

void convert(int d_num, char b_num[]){
  int i, pre_num = d_num;
  for(i = 0; pre_num != 1; i++){
    pre_num = d_num / (int)pow(2, i);
    if (pre_num % 2){
      *(b_num + LEN - 1 - i) = '1';
    } else{
      *(b_num + LEN - 1 - i) = '0';
    }
  }
}
