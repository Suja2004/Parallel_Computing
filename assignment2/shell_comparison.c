#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int i, gap, t;

void shellSortSerial(int arr[], int n) {
    for( gap = n / 2; gap > 0; gap /= 2) {
        for( i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

void shellSortParallel(int arr[], int n) {
    for( gap = n / 2; gap > 0; gap /= 2) {
        #pragma omp parallel for shared(arr, gap, n)
        for( i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

int main() {
    int n = 100000;
    int *arr = (int *)malloc(n * sizeof(int));
    int *temp = (int *)malloc(n * sizeof(int));
    double start, end, serial_time, parallel_time;
    int max_threads = 8;

    srand(time(NULL));
    for( i = 0; i < n; i++)
        arr[i] = rand();

    // SERIAL EXECUTION 
    for( i = 0; i < n; i++) temp[i] = arr[i];
    start = omp_get_wtime();
    shellSortSerial(temp, n);
    end = omp_get_wtime();
    serial_time = end - start;
    printf("\n===== SHELL SORT PERFORMANCE ANALYSIS =====\n");
    printf("Array size: %d\n", n);
    printf("Serial Execution Time: %.6f sec\n\n", serial_time);

    // PARALLEL EXECUTION
    printf("Threads\tTime(sec)\tSpeedup\t\tEfficiency(%%)\n");
    printf("-----------------------------------------------------\n");

    for( t = 1; t <= max_threads; t *= 2) {
        omp_set_num_threads(t);

        for( i = 0; i < n; i++) temp[i] = arr[i];
        start = omp_get_wtime();
        shellSortParallel(temp, n);
        end = omp_get_wtime();
        parallel_time = end - start;

        double speedup = serial_time / parallel_time;
        double efficiency = (speedup / t) * 100.0;

        printf("%d\t%.6f\t%.2f\t\t%.2f\n", t, parallel_time, speedup, efficiency);
    }

    printf("-----------------------------------------------------\n");
    printf("Note: Efficiency = (Speedup / Threads) x 100\n");

    free(arr);
    free(temp);
    return 0;
}
