//
//  rd_random.h
//  c-testlib
//
//  Created by Rostyslav Druzhchenko on 14/4/20.
//  Copyright © 2020 Rostyslav Druzhchenko. All rights reserved.
//

#ifndef __RD_RANDOM_H__
#define __RD_RANDOM_H__

int rd_random_int(int from, int to);
double rd_random_double(int from, int to);
void rd_random_fill(int *arr, int n, int from, int to);

char rd_random_lower_char();
char rd_random_upper_char();
char rd_random_char();

extern int rd_random_str_min;
extern int rd_random_str_max;
char *rd_random_str();
char *rd_random_strn(int length);

#endif // __RD_RANDOM_H__
