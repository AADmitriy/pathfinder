#include <unistd.h>

void mx_printint_err(int n) {
    if (n == -2147483648) {
        write(2, "-2147483648", 11);
        return;
    }
    
    if (n < 0) {
        write(2, "-", 1);
        n *= -1;
    }

    if (n > 9) {
        mx_printint_err(n / 10);
    }

    char num = n % 10 + '0';
    write(2, &num, 1);
}

