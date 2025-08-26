#include <stdio.h>
#include <omp.h>

#define N 10

int main()
{
    int A[N];
    int i;

    for (i = 0; i < N; i++)
    {
        A[i] = i;
    }

    printf("Original Array:\n");
    for (i = 0; i < N; i++)
        printf("%d ", A[i]);
    printf("\n");
    double t0 = omp_get_wtime();

#pragma omp parallel for schedule(dynamic, 2)
    for (i = 0; i < N; i++)
    {
        A[i] = 3 * A[i] + 2;

        printf("Thread %d updated A[%d] = %d (Dynamic)\n",
               omp_get_thread_num(), i, A[i]);
    }
    double t1 = omp_get_wtime();
    printf("time = %f sec \n", t1 - t0);

    for (i = 0; i < N; i++)
    {
        A[i] = i;
    }

    t0 = omp_get_wtime();
#pragma omp parallel for schedule(static, 2)
    for (i = 0; i < N; i++)
    {
        A[i] = 3 * A[i] + 2;
        printf("Thread %d updated A[%d] = %d (Static)\n",
               omp_get_thread_num(), i, A[i]);
    }
    t1 = omp_get_wtime();
    printf("time = %f sec \n", t1 - t0);

    for (i = 0; i < N; i++)
    {
        A[i] = i;
    }

    t0 = omp_get_wtime();
#pragma omp parallel for schedule(guided, 2)
    for (i = 0; i < N; i++)
    {
        A[i] = 3 * A[i] + 2;
        printf("Thread %d updated A[%d] = %d (Guided)\n",
               omp_get_thread_num(), i, A[i]);
    }
    t1 = omp_get_wtime();
    printf("time = %f sec \n", t1 - t0);

    return 0;
}
