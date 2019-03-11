#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>


void swap(int* a, int* b) 
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void insert_sort(int* arr, int size)
{
    if (arr == NULL || size <= 0) {
        printf("wrong arg");
        return;
    }

    for (int i = 1; i < size; ++i) {
        for (int j = i; j > 0; --j) {
            if (arr[j] < arr[j - 1]) swap(arr + j - 1, arr + j);
            else break;
        }
    }
}


int main(void) 
{
    int32_t a[10] = {0}, peak = 0;
    time_t t;
    int32_t     len = sizeof(a) / sizeof(int32_t);

    /* Intializes random number generator */
    srand((unsigned) time(&t));

    printf("source:\n");
    for (int32_t i = 0; i < len; ++i) {
        a[i] = (int32_t)rand() % 100;
        printf("%d ", a[i]);
    }
    printf("\n");

    insert_sort(a, len);

    printf("sorted:\n");
    for (int32_t i = 0; i < len; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}
