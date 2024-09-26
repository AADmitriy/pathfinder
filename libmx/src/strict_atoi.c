#include "libmx.h"

int strict_atoi(const char *str) {
    int result = 0;

    if (*str == '-') {
        return -1;
    }
    else if (*str == '0') {
        return -1;
    }
    else if (*str == '+') {
        str++;
    }

    while (mx_isdigit(*str)) {
        if (INT_MAX / 10 < result) {
            return -1;
        }
        result *= 10;
        if (INT_MAX - (*str - '0') < result) {
            return -1;
        }
        result += *str - '0';

        str++;
    }

    if (*str != '\0') {
        return -1;
    }

    return result;
}


