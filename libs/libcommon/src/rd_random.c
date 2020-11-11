//
//  rd_random.c
//  c-testlib
//
//  Created by Rostyslav Druzhchenko on 14/4/20.
//  Copyright © 2020 Rostyslav Druzhchenko. All rights reserved.
//

#include <time.h>
#include <stdlib.h>
#include <math.h>

static int is_initialized = 0;

static int rd_random_str_min = 3;
static int rd_random_str_max = 10;

int rd_random_int(int from, int to) {
    if (!is_initialized) {
        is_initialized = 1;
        srand(time(0));
    }
    return rand() % (to - from + 1) + from;
}

double rd_random_double(int from, int to) {
    double result = rd_random_int(from, to);
    int mantissa_len = rd_random_int(1, 6);
    int max = pow(10, mantissa_len);
    double mantissa = rd_random_int(0, max) / max;
    result += mantissa;
    return result;
}

void rd_random_fill(int *arr, int n, int from, int to) {
    for (int i = 0; i < n; i++) {
        arr[i] = rd_random_int(from, to);
    }
}

char rd_random_lower_char() {
    return rd_random_int(97, 122);
}

char rd_random_upper_char() {
    return rd_random_int(65, 90);
}

char rd_random_char() {
    if (rd_random_int(0, 1) % 2) {
        return rd_random_lower_char();
    }
    else {
        return rd_random_upper_char();
    }
}

char *rd_random_strn(int length) {
    char *str = (char *) malloc(sizeof(char) * (length + 1));
    for (int i = 0; i < length; i++) {
        str[i] = rd_random_char();
    }
    str[length] = '\0';
    return str;
}

char *rd_random_str() {
    int length = rd_random_int(rd_random_str_min, rd_random_str_max);
    return rd_random_strn(length);
}
