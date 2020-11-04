#include <wchar.h>

#include <libmx.h>

void mx_print_unicode(wchar_t c) {
    for (int i = 0, n = sizeof(c); i < n; i++) {
        mx_printchar(((unsigned char *)&c)[i]);
    }
}
