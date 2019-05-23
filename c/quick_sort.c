#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<string.h>


void swap(int* a, int x, int y) 
{
    int tmp = a[x];
    a[x] = a[y];
    a[y] = tmp;
}


void quick_sort(int* arr, int left, int right) 
{
    if (left >= right) return;
    else if (left + 1 == right) {
        if (arr[left] > arr[right]) swap(arr, left, right);
        return;
    }
    int i = left + 1, j = right;
    int target = arr[left];
    while (true) {
        while (arr[i] <= target && i < right) ++i;
        while (arr[j] >= target && j > left) --j;
        if (i >= j) break;
        else swap(arr, i, j);
    }
    swap(arr, left, j);
    quick_sort(arr, left, j - 1);
    quick_sort(arr, j + 1, right);
}


int main(void) 
{
    int32_t a[10] = {0}, peak = 0;
    time_t t;
    int32_t     len = sizeof(a) / sizeof(int32_t);

    for (int j = 2; j <= len; ++j) {
        memset(a, 0, len);

        /* Intializes random number generator */
        srand((unsigned) time(&t));

        printf("source: \t");
        for (int32_t i = 0; i < j; ++i) {
            a[i] = (int32_t)rand() % 100;
            printf("%d ", a[i]);
        }
        printf("\n");

        quick_sort(a, 0, j - 1);

        // check sort result
        bool success = true;
        for (int i = 1; i < j; ++i) {
            if (a[i] < a[i - 1]) {
                success = false;
                break;
            }
        }
        success ? printf("sort succeed:\t") : printf("sort failed:\t");
        for (int32_t i = 0; i < j; ++i) printf("%d ", a[i]);
        printf("\n");
    }


    return 0;
}
