void mx_swap_char(char *s1, char *s2) {
    if (s1 == 0 || s2 == 0)
        return;

    char tmp = *s1;
    *s1 = *s2;
    *s2 = tmp;
}
