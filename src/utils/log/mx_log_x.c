//
// Created by Rostyslav Druzhchenko on 27.09.2020.
//

#include <mx_log.h>

void mx_log_t(const char *subject, const char *details) {
    mx_log(subject, details, LOG_TRACE);
}

void mx_log_d(const char *subject, const char *details) {
    mx_log(subject, details, LOG_DEBUG);
}

void mx_log_i(const char *subject, const char *details) {
    mx_log(subject, details, LOG_INFO);
}

void mx_log_e(const char *subject, const char *details) {
    mx_log(subject, details, LOG_ERROR);
}
