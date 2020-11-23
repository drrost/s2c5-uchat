//
//  test_lib.c
//  c-testlib
//
//  Created by Rostyslav Druzhchenko on 14/4/20.
//  Copyright © 2020 Rostyslav Druzhchenko. All rights reserved.
//

#include <test_lib.h>

#include <unistd.h>
#include <stdio.h>

int is_failed = 0;
char *tXX = "";
char *test_case_name = "";

int stdout_bk;
int pipefd[2];
char STDOUT_BUFF[101];

// Prints

void test_print_fail(const char *message) {
    printf("%s | ", tXX);
    printf("\033[0;31m");
    printf("%s", "FAILED:");
    printf("\033[0m |");
    printf("\033[1m %s\033[0m\n", test_case_name);
    printf("%s", message);

    is_failed = 1;
}

void test_print_ok() {
    printf("%s | ", tXX);
    printf("\033[0;32m");
    printf("%s", "  OK   \033[0m");
    printf(" |\033[1m %s\033[0m\n", test_case_name);
}

void test_finalize() {
    if (!is_failed) {
        test_print_ok();
    }
}

// Itercept stdout

void intercept_stdout() {
    stdout_bk = dup(fileno(stdout));
    pipe(pipefd);
    dup2(pipefd[1], fileno(stdout));
}

void restore_stdout() {
    fflush(stdout);
    close(pipefd[1]);
    dup2(stdout_bk, fileno(stdout));
    read(pipefd[0], STDOUT_BUFF, 100);
}
