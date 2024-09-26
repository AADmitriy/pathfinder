#include "libmx.h"


void swap(int **arr, int ind1, int ind2) {
    int temp = (*arr)[ind1];
    (*arr)[ind1] = (*arr)[ind2];
    (*arr)[ind2] = temp;
}


void quickSort(int **arr, int left, int right) {
    int i = left, j = right;
    int pivot = (*arr)[(left + right) / 2];

    while (i <= j) {
        while ((*arr)[i] < pivot) { i++; }
        while ((*arr)[j] > pivot) { j--; }

        if (i <= j) {
            if (i != j && (*arr)[i] > (*arr)[j]) {
                swap(arr, i, j);
            }

            i++;
            j--;
        }
    }

    if (left < j) {
        quickSort(arr, left, j);
    }
    if (i < right) {
        quickSort(arr, i, right);
    }
}

void mx_quicksort(int **arr, int left, int right) {
    quickSort(arr, left, right);
}


