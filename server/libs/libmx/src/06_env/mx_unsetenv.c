//
// Created by Karina Barinova on 09.10.2020.
//

#include <libmx.h>

int mx_unsetenv(const char *s) {
	return unsetenv(s);
}
