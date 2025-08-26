#include <stdio.h>
#include <omp.h>

int main()
{
#pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int threads = omp_get_num_threads();

        printf("Hello from thread %d out of %d threads\n", tid, threads);
    }
    return 0;
}
