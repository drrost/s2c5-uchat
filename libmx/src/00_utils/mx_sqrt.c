int mx_sqrt(int x) {
    if (x < 0)
        return 0;

    for (int i = 0; i * i <= x; i++) {
        long int mul = i * i;

        if (mul < 0) {
            return 0;
        }
        if (mul == x) {
            return i;
        }
    }
    return 0;
}
