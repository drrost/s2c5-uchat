//
// Created by Karina Barinova on 09.10.2020.
//

int mx_arr_size(char **arr) {
    int i = 0;

    if (arr != 0) {
        while (arr[i])
            i++;
        return i;
    }
    return 0;
}
