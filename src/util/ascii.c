//
// Created by AIDAN PRATT on 7/3/2024.
//

#include "ascii.h"
#include <stdint.h>


void decimal_from_int32(int32_t n, char dest[12]) {
    char str[12];
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    dest[i] = '\0';

    int j;
    for(j = 0; j < i; j++) {
        dest[j] = str[i - 1 - j];
    }
}

void decimal_from_uint64(uint64_t n, char dest[20]) {
    char str[20];
    int i;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    str[i] = '\0';

    dest[i] = '\0';

    int j;
    for(j = 0; j < i; j++) {
        dest[j] = str[i - 1 - j];
    }
}