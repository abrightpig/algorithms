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

void merge(int32_t *arr, int32_t left, int32_t right)
{
    int32_t size = right - left + 1;
    int32_t mid = (left + right) / 2;
    int32_t *tmp_arr = (int32_t*)malloc(sizeof(int32_t) * size);
    
    int32_t pos1 = left, pos2 = mid + 1, pos_tmp = 0;
    for (; pos1 <= mid && pos2 <= right;) {
        if (arr[pos1] <= arr[pos2]) {
            tmp_arr[pos_tmp] = arr[pos1];
            ++pos1;
        }
        else {
            tmp_arr[pos_tmp] = arr[pos2];
            ++pos2;
        }
        ++pos_tmp;
    } 

   for (; pos1 <= mid; ++pos1, ++pos_tmp) tmp_arr[pos_tmp] = arr[pos1];
   for (; pos2 <= right; ++pos2, ++pos_tmp) tmp_arr[pos_tmp] = arr[pos2]; 

   for (int32_t i = 0; i < size; ++i) arr[left + i] = tmp_arr[i]; 
    
    free(tmp_arr);
}

void merge_sort(int32_t *arr, int32_t left, int32_t right)
{
    if (left >= right) return;
    if (left + 1 == right) {
        if (arr[left] > arr[right]) swap(arr + left, arr + right); 
        return;
    } 

    int32_t mid = (left + right) / 2;
    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);

    merge(arr, left, right);
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

    merge_sort(a, 0, len - 1);

    printf("merge-sorted:\n");
    for (int32_t i = 0; i < len; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}
