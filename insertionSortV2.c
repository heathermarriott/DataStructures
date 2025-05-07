#include <stdio.h>
#define SIZE 6

void insertion_sort(int list[], int size) {
    int u, j;
    int element;
    for (u = 1; u < size; u++) {
        element = list[u];
        j = u;
        while (j > 0 && list[j - 1] > element) {
            list[j] = list[j - 1];
            j--;
        }
        list[j] = element;
    }
}

int main() {
    int list[SIZE] = {6, 2, 10, 7, 1, 5};
    int i;

    printf("Unsorted list: ");
    for (i = 0; i < SIZE; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");

    insertion_sort(list, SIZE);

    printf("Sorted list: ");
    for (i = 0; i < SIZE; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");

    return 0;
}
