//
// Created by Rostyslav Druzhchenko on 12.10.2020.
//

#ifndef INC_04_USH_MX_LOG_H
#define INC_04_USH_MX_LOG_H

#include <libmx.h>

enum e_log_level {
    LOG_ALL,
    LOG_TRACE,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL,
    LOG_OFF
};

#define DETAILES_SIZE 1024

void mx_log(const char *subject, const char *details, int level);
void mx_log_t(const char *subject, const char *details);
void mx_log_di(const char *subject, int number);
void mx_log_d(const char *subject, const char *details, ...);
void mx_log_i(const char *subject, const char *details, ...);
void mx_log_e(const char *subject, const char *details, ...);

#endif //INC_04_USH_MX_LOG_H
