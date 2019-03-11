#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

bool find_peak(int32_t *array, int32_t len, int *peak)
{
    int32_t     left = 0, right = len - 1;
    int32_t     mid = 0;
    
    while (left < right) {
        mid = (left + right) / 2;        
        printf("mid is %d\n", array[mid]);
        usleep(100*1000);
        if (array[mid] < array[mid + 1]) {
            // search left half part
            left = mid;
        }
        else if (array[mid] < array[mid - 1]) {
            // search right half part
            right = mid; 
        }
        else {
            // found 
            *peak = array[mid];
            return true;
        }
    }
    
    return false;
}


int main(void) 
{
    int32_t a[10] = {0}, peak = 0;
    time_t t;

    // generate random samples
    //    /* Intializes random number generator */
    srand((unsigned) time(&t));

    printf("source:\n");
    for (int32_t i = 0; i < sizeof(a) / sizeof(int32_t); ++i) {
        a[i] = (int32_t)rand() % 100;
        printf("%d ", a[i]);
    }
    printf("\n");

    bool result = find_peak(a, sizeof(a) / sizeof(int) , &peak);
    if (result) {
        printf("peak is %d\n", peak);
    }
    else {
        printf("no peak found\n");
    }

    return 0;
}
