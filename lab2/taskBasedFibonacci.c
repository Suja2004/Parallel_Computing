#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

int fib(int n)
{
    int i, j;
    if (n < 2)
        return n;
    else
    {
#pragma omp task shared(i) firstprivate(n)
        i = fib(n - 1);
#pragma omp task shared(j) firstprivate(n)
        j = fib(n - 2);
#pragma omp taskwait
        return i + j;
    }
}

int main()
{
    int n;
    printf("Enter the Fibonacci number to calculate:");
    scanf("%d", &n);
    omp_set_dynamic(0);
    omp_set_num_threads(4);

    srand(time(0));
    #pragma omp parallel shared(n)
    {
        double start_time = omp_get_wtime();
        #pragma omp single
        printf("fib(%d) = %d\n", n, fib(n));
        double end_time = omp_get_wtime();
        printf("Time taken: %f seconds by thread %d\n", end_time - start_time, omp_get_thread_num());
    }
    return 0;
}