#define LEN 32

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

void pre_db_convert()
{
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
    printf("Please input a Decimal number(only interger, \
and enter 'q' to quit): ");
    status = scanf("%d", &d_num);
    //the good input
    if (status == 1){
      while (getchar() != '\n'){
        ;
      }
      //print begin
      db_convert(d_num, b_num);

      printf("Decimal: %d --> Binary: ", d_num);

	    for (i = 0; i < LEN; i++) {
			  printf("%d", b_num[i]);
			  if ((i+1) % 8 == 0) {
				putchar(' ');
			  }
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
          printf("Return to the previous level.\n");
          return;  //it's the end way
        }
		    else if (c == '\n') {
			    break;
		    }
		    else{
          c_flag = 0;
          putchar(c);
        }
      }
      printf(" is not a interger, please try again.\n");
      c_flag = 1;
    }
    //back to get input
  }
}
