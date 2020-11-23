//
// Created by Rostyslav Druzhchenko on 25.07.2020.
//

#pragma once

#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

extern sigjmp_buf point;

void handler(int sig, siginfo_t *siginfo, void *p);

#define TRY {\
    struct sigaction sa; \
    memset(&sa, 0, sizeof(struct sigaction)); \
    sigemptyset(&sa.sa_mask); \
\
    sa.sa_flags = SA_NODEFER; \
    sa.sa_sigaction = handler; \
\
    sigaction(SIGSEGV, &sa, NULL); \
    if (setjmp(point) == 0) { \

#define CATCH(f_name) \
    } else { \
    restore_stdout(); \
    char *s = (char *) malloc(1024); \
    sprintf(s, "     Segmentation fault: \"\033[1m%s\033[0m\"\n", f_name); \
    test_print_fail(s); \
    free(s); \
} \
}
