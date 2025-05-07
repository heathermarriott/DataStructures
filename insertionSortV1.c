#include <stdio.h>
#define SIZE 6

void insertion_sort(int unsorted[], int sorted[], int size) {
    int sorted_size = 0;

    for (int u = 0; u < size; u++) {
        int element = unsorted[u];
        int inserted = 0; //0 means not yet inserted

        // Try to insert into the correct position
        for (int i = 0; i < sorted_size; i++) {
            if (element < sorted[i]) {
                // Shift elements to the right
                for (int j = sorted_size; j > i; j--) {
                    sorted[j] = sorted[j - 1];
                }
                sorted[i] = element;
                inserted = 1; //1 means inserted
                sorted_size++;
                break;
            }
        }

        // If not inserted, append to end
        if (!inserted) {
            sorted[sorted_size] = element;
            sorted_size++;
        }
    }
}

int main() {
    int unsorted[SIZE] = {6, 2, 10, 7, 1, 5};
    int sorted[SIZE];  // same size as unsorted

    printf("Unsorted list: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", unsorted[i]);
    }
    printf("\n");

    insertion_sort(unsorted, sorted, SIZE);

    printf("Sorted list: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", sorted[i]);
    }
    printf("\n");

    return 0;
}
