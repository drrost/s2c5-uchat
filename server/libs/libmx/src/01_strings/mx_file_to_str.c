#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <libmx.h>

char *mx_file_to_str(const char *file) {
    if (file == 0)
        return 0;
    int fd = open(file, O_RDONLY);
    if (fd == -1)
        return 0;

    char *result = mx_strnew(0);

    int len = 4;
    char buff[len];
    int bytes_read;
    while ((bytes_read = read(fd, buff, len - 1)) > 0) {
        buff[bytes_read] = 0;
        char *old_result = result;
        result = mx_strjoin(result, (char *)buff);
        free(old_result);
        if (result == 0) {
            return 0;
        }
    }

    close(fd);
    return result;
}
