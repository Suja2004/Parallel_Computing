#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

int is_prime(int num)
{
    if (num <= 1)
        return 0;
    if (num == 2)
        return 1;
    if (num % 2 == 0)
        return 0;
    int i;
    for (i = 3; i <= sqrt(num); i += 2)
    {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

int main()
{
    int n, i;
    printf("Enter the upper limit (n) to find prime numbers: ");
    scanf("%d", &n);

    if (n < 2)
    {
        printf("There are no prime numbers up to %d.\n", n);
        return 0;
    }

    printf("\nFinding prime numbers from 1 to %d...\n", n);

    double serial_start_time = omp_get_wtime();
    int sequential_prime_count = 0;
    for (i = 1; i <= n; i++)
    {
        if (is_prime(i))
            sequential_prime_count++;
    }
    double time_seq = omp_get_wtime() - serial_start_time;

    double parallel_start_time = omp_get_wtime();
    int parallel_prime_count = 0;
#pragma omp parallel for reduction(+ : parallel_prime_count) schedule(dynamic)
    for (i = 1; i <= n; i++)
    {
        if (is_prime(i))
            parallel_prime_count++;
    }
    double time_par = omp_get_wtime() - parallel_start_time;

    printf("\nSerial Count of primes = %d", sequential_prime_count);
    printf("\nParallel Count of primes = %d", parallel_prime_count);
printf("\nExecution time (serial): %f seconds", time_seq);
printf("\nExecution time (parallel): %f seconds", time_par);


    if (time_par > 0 && time_seq > 0)
    {
        printf("\nSpeedup: %.2fx\n", time_seq / time_par);
    }

    return 0;
}