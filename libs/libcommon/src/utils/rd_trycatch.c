//
// Created by Rostyslav Druzhchenko on 25.07.2020.
//

#include "rd_trycatch.h"

sigjmp_buf point;

void handler(int sig, siginfo_t *siginfo, void *p) {
    sig++;
    siginfo++;
    char *a = (char *) p;
    a++;
    longjmp(point, 1);
}
