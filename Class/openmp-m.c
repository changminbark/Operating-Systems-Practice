/**
 * Example of openmp parallel region
 * 
 * To compile, enter:
 *
 *	gcc -fopenmp openmp-m.c -o openmp-m
 *
 * You should see the message "I am a parallel region" for each
 * processing core on your system.
 *
 * For those using a virtual machine, make sure you set the number of
 * processing cores > 1 to see parallel execution of the parallel region.
 *
 * The number of threads can be set either through a call to "omp_set_threads()"
 * or through the environment variable OMP_NUM_THREADS
 * e.g., in bashrc: "export OMP_NUM_THREADS=val"
 * The system deafault is 16.
 */

#include <omp.h>
#include <stdio.h>

int v = 0;

int main(int argc, char *argv[])
{
	/* sequential code */

  int tid;
  int nthreads;

#pragma omp parallel shared(v, nthreads) private(tid)
  {
	tid = omp_get_thread_num();
	if (tid == 0)
	  {
		nthreads = omp_get_num_threads();
		printf("Number of threads = %d\n", nthreads);
	  }

	#pragma omp critical
	{
		v++;
	}
	
	printf("I am a parallel region (thread id == %d)\n", tid);
  }

  /* sequential code */

  printf("value of v = %d\n", v);
  return 0;
}
