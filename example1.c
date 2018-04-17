/* From this example, you can learn different ways of controlling the number of OpenMP threads */

#include <stdio.h>
#include <omp.h>

int main()
{
  int number = 1;

  /* use the default number of threads */
  #pragma omp parallel
  {
    int ID = omp_get_thread_num();
	int total = omp_get_num_threads();
    printf("hello world (%3d of %3d)\n", ID, total);
  }

  /* now let's control the number of threads */
  printf("How many threads do you want: \n");
  scanf("%d", &number);
  omp_set_num_threads(number);

  #pragma omp parallel
  {
    int ID = omp_get_thread_num();
	int total = omp_get_num_threads();
    printf("hello world (%3d of %3d)\n", ID, total);
  }

  /* Try a different way to control the number of threads */
  printf("How many threads do you want: \n");
  scanf("%d", &number);

  #pragma omp parallel num_threads(number)
  {
    int ID = omp_get_thread_num();
	int total = omp_get_num_threads();
    printf("hello world (%3d of %3d)\n", ID, total);
  }

  return 0;
}
