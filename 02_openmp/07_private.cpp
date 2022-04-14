#include <cstdio>

int main() {
  int a = 1, b = 1, c = 1;
#pragma omp parallel num_threads(4)
  {
#pragma omp for private(a)
    for(int i=0; i<4; i++)
      printf("a=%d ",++a);
#pragma omp single
    printf("\n");
#pragma omp for firstprivate(b)
    for(int i=0; i<4; i++)
      printf("b=%d ",++b);
#pragma omp single
    printf("\n");
#pragma omp for lastprivate(c)
    for(int i=0; i<4; i++)
      printf("c=%d ",++c);
#pragma omp single
    printf("\n");
  }
  printf("a= %d b= %d c= %d\n",a,b,c);
}
