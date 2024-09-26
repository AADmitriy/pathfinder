#include "libmx.h"

int get_str_index(char** arr, int arr_size, char* str) {
    for (int i = 0; i < arr_size; i++) {
        if (mx_strcmp(arr[i], str) == 0) {
            return i;
        }
    }
    return -1;
}


