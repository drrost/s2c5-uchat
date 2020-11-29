//
// Created by Rostyslav Druzhchenko on 27.09.2020.
//

#include <mx_log.h>

static void print_debug(const char *line) {
    FILE *file = fopen("/tmp/ulog.log", "a+");
    fprintf(file, "%s\n", line);
    fclose(file);
}

char *current_time() {
    time_t raw_time;
    struct tm *time_info;

    time(&raw_time);
    time_info = localtime(&raw_time);

    static char time_str[128];
    sprintf(time_str, "%04d-%02d-%02dT%02d:%02d:%02d",
            time_info->tm_year + 1900, time_info->tm_mon + 1,
            time_info->tm_mday, time_info->tm_hour,
            time_info->tm_min, time_info->tm_sec);

    return mx_strdup(time_str);
}

static void append_level(char **where, int level) {
    switch (level) {
        case LOG_TRACE:
            mx_str_append(where, " TRACE ");
            break;
        case LOG_DEBUG:
            mx_str_append(where, " DEBUG ");
            break;
        case LOG_INFO:
            mx_str_append(where, " INFO ");
            break;
        case LOG_ERROR:
            mx_str_append(where, " ERROR ");
            break;
        default:
            mx_str_append(where, " UNKNOWN ");
    }
}

void mx_log(const char *subject, const char *details, int level) {
    char *to_print = current_time();
    char *in_details = 0;
    if (details == 0)
        in_details = mx_strdup("<NULL>");
    else
        in_details = mx_strdup(details);

    append_level(&to_print, level);
    mx_str_append(&to_print, subject);

    if (mx_strlen(in_details)) {
        mx_str_append(&to_print, " - ");
        mx_str_append(&to_print, in_details);
    }

    print_debug(to_print);
    mx_strdel(&to_print);
    mx_strdel(&in_details);
}
