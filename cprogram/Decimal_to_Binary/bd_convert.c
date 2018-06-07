#define LEN 32

int bd_convert(int b_num[])
{
  int i = 0, d_num = 0, b_num_lenth = 0;
  for (i = 0; i < LEN && (b_num[i] == 0 || b_num[i] == 1); i++){
    b_num_lenth++;
  }
  for (i = 0; i < b_num_lenth; i++){
    d_num += b_num[i] * pow(2, b_num_lenth - 1 - i);
  }
  return d_num;
}

void pre_bd_convert()
{
  int d_num = 0, status = 0, i = 0, c_flag = 1, b_num[LEN] = {'0'};
  char c;

  while (1){
    d_num = 0;
    status = 0;
    for (i = 0; i < LEN; i++){
      b_num[i] = 0;
    }
    //get input
    printf("Please input a Binary number(Enter 'q' to quit, \
with the other numbers to end the input.): ");

    for (i = 0; i < LEN; i++){
      status = scanf("%1d", &b_num[i]);
      if (
           status != 1 ||
           (b_num[i] != 0 && b_num[i] != 1)
         ) {
        break;
      }
    }
    //the good input
    if (status == 1){
      while (getchar() != '\n'){
        ;
      }
      //print begin
      d_num = bd_convert(b_num);
      printf("Binary: ");
      for (i = 0; i < LEN && (b_num[i] == 0 || b_num[i] == 1); i++){
        printf("%d", b_num[i]);
      }
      printf(" --> Decimal: %d\n", d_num);
    }
    //print end
    //the bad input
    else{
      while (c = getchar()){
        if (c == 'q' && c_flag == 1){
          while (getchar() != '\n') {
            ;
          }
          printf("Return to the previous level.\n");
          return;  //it's the end way
        }
		    else if (c == '\n') {
			    break;
		    }
		    else{
          putchar(c);
          c_flag = 0;
        }
      }
      printf(" is not a interger, please try again.\n");
      c_flag = 1;
    }
    //back to get input
  }
}
