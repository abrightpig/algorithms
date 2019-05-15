#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<string.h>


void swap(int* a, int* b) 
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void max_heap(int *arr, int len)
{
    if (arr == NULL || len <= 1) {
        return;
    }
    /*
    printf("heap-source: ");
    for (int32_t i = 0; i < len; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    */

    for (int i = len / 2 - 1; i >= 0; --i) {
        if (i * 2 + 1 == len - 1 || arr[i * 2 + 1] >= arr[i * 2 + 2]) {
            // only left chiled or left child is bigger
            if (arr[i] < arr[i * 2 + 1]) swap(arr + i, arr + 2 * i + 1);
        }
        else {
            // right child is bigger
            if (arr[i] < arr[i * 2 + 2]) swap(arr + i, arr + 2 * i + 2); 
        }
    }

    /*
    printf("max_heap: ");
    for (int32_t i = 0; i < len; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    */
}

void adjust_heap(int* arr, int begin, int len) {
    for (int i = begin; 2 * i + 1 < len; ) {
        int left = 2 * i + 1;
        int right = left + 1;
        int larger = left;
        if (right < len && arr[right] > arr[left]) larger = right;
        if (arr[larger] > arr[i]) {
            swap(arr + i, arr + larger);
            i = larger;
        }
        else break;
    }

}

void adjust_heap2(int *arr, int head, int end)
{
    if (arr == NULL || head < 0 || end < 1) {
        return;
    }
    
    for (int i = head, left = 2 * i + 1; left <= end; ) {
        int right = left + 1;
        int child = 0;
        if (left == end || arr[left] >= arr[right]) {
            child = left;
        }
        else {
            child = right;
        }

        if (arr[i] < arr[child]) {
            swap(arr + i, arr + child);
            i = child; 
            left = 2 * i + 1;
        }
        else {
            break;
        }

    }
}

void heap_sort(int *arr, int len)
{
    if (arr == NULL || len <= 1) {
        return;
    }
    
    /* build max heap*/
    for (int i = len / 2 - 1; i >= 0; --i) {
        adjust_heap(arr, i, len);
    }

    /* sort */
    for (int i = len - 1; i > 0; --i) {
        swap(arr, arr + i);
        adjust_heap(arr, 0, i);
    }
}


void heap_sort2(int *arr, int len)
{
    if (arr == NULL || len <= 1) {
        return;
    }

    for (int i = len - 1; i > 0; --i) {
        max_heap(arr, i + 1);
        //printf("max is %d\n", arr[0]);
        swap(arr, arr + i);

        /*
    printf("sorted-tmp: ");
    for (int32_t j = 0; j < len; ++j) {
        printf("%d ", arr[j]);
    }
    printf("\n");
        */
    }
}


int main(void) 
{
    int32_t a[10] = {0}, peak = 0;
    time_t t;
    int32_t     len = sizeof(a) / sizeof(int32_t);

    for (int j = 0; j <= len; ++j) {
        //int j = len;
        memset(a, 0, len);

        /* Intializes random number generator */
        srand((unsigned) time(&t));

        printf("source:\n");
        for (int32_t i = 0; i < j; ++i) {
            a[i] = (int32_t)rand() % 100;
            printf("%d ", a[i]);
        }
        printf("\n");

        //heap_sort(a, j);
        heap_sort2(a, j);

        printf("heap-sorted:\n");
        for (int32_t i = 0; i < j; ++i) {
            printf("%d ", a[i]);
        }
        printf("\n");
    
    }


    return 0;
}
