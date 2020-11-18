//
// Created by Rostyslav Druzhchenko on 27.09.2020.
//

#include <mx_log.h>
#include <libmx.h>

void mx_log_t(const char *subject, const char *details) {
    mx_log(subject, details, LOG_TRACE);
}

void mx_log_di(const char *subject, int number) {
    char *s = mx_itoa(number);
    mx_log_d(subject, s);
    mx_strdel(&s);
}

void mx_log_d(const char *subject, const char *details, ...) {
    char *in_details = mx_strnew(DETAILES_SIZE);

    va_list argp;
    va_start(argp, details);
    vsprintf(in_details, details, argp);
    va_end(argp);

    mx_log(subject, in_details, LOG_DEBUG);
    mx_strdel(&in_details);

}

void mx_log_i(const char *subject, const char *details, ...) {
    char *in_details = mx_strnew(DETAILES_SIZE);

    va_list argp;
    va_start(argp, details);
    vsprintf(in_details, details, argp);
    va_end(argp);

    mx_log(subject, in_details, LOG_INFO);
    mx_strdel(&in_details);
}

void mx_log_e(const char *subject, const char *details, ...) {
    char *in_details = mx_strnew(DETAILES_SIZE);

    va_list argp;
    va_start(argp, details);
    vsprintf(in_details, details, argp);
    va_end(argp);

    mx_log(subject, in_details, LOG_ERROR);
    mx_strdel(&in_details);
}
