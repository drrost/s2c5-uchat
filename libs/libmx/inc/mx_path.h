//
// Created by Rostyslav Druzhchenko on 08.10.2020.
//

#ifndef INC_04_USH_MX_PATH_H
#define INC_04_USH_MX_PATH_H

#include <stdbool.h>
#include <wordexp.h>

// File types

#define MX_IFMT 0170000 // Mask of file type
#define MX_IFIFO 0010000 // Named pipe(fifo)
#define MX_IFCHR 0020000 //character device
#define MX_IFDIR 0040000 //directory file
#define MX_IFBLK 0060000 //Block device
#define MX_IFREG 0100000 //regular file
#define MX_IFLNK 0120000 //symbolic link
#define MX_IFSOCK 0140000 //UNIX domain socket

#define MX_ISBLK(m) (((m) & MX_IFMT) == MX_IFBLK)
#define MX_ISCHR(m) (((m) & MX_IFMT) == MX_IFCHR)
#define MX_ISDIR(m) (((m) & MX_IFMT) == MX_IFDIR)
#define MX_ISFIFO(m) (((m) & MX_IFMT) == MX_IFIFO)
#define MX_ISREG(m) (((m) & MX_IFMT) == MX_IFREG)
#define MX_ISLNK(m) (((m) & MX_IFMT) == MX_IFLNK)
#define MX_ISXEC(m) ((m) & MX_IXUSR)
#define MX_ISSOCK(m) (((m) & MX_IFMT) == MX_IFSOCK)

typedef struct s_path {
    char *p;

    char *(*last)(struct s_path *, char *);
    void (*last_del)(struct s_path *);
    void (*append)(struct s_path *, char *);
    void (*print)(struct s_path *);

    bool (*is_dir)(struct s_path *);
    bool (*exists)(struct s_path *);

    char *(*reslolve)(struct s_path *);
}              t_path;

t_path *mx_path_new(const char *path);
void mx_path_del(t_path **path);

char *mx_real_path(char *file_name);

char *mx_path_resolve_all_escapes(char *s);

#endif //INC_04_USH_MX_PATH_H
