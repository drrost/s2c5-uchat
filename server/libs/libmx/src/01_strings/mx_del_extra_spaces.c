#include <libmx.h>

char *mx_del_extra_spaces(const char *str) {
    if (str == 0)
        return 0;

    int first_ch_idx = -1;
    int last_ch_idx = -1;

    int length = mx_strlen(str);
    for (int i = 0; i < length; i++) {
        if (!mx_isspace(str[i])) {
            last_ch_idx = i;
            if (first_ch_idx == -1) {
                first_ch_idx = i;
            }
        }
    }

    if (first_ch_idx == -1) {
        return mx_strnew(0);
    }

    int new_length = length - first_ch_idx - length + last_ch_idx + 1;
    char *result = mx_strnew(new_length);

    str += first_ch_idx;
    int j = 0;
    int prev_was_space = 0;
    for (int i = 0; i < new_length; i++) {
        int is_current_space = mx_isspace(str[i]);
        if (prev_was_space && is_current_space) {
            continue;
        }
        prev_was_space = is_current_space;
        result[j] = str[i];
        j++;
    }

    return result;
}
