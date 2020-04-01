void quick_sort (int l, int r){
    int mid = mas[(r + l) / 2], i = l, j = r;
    while (i <= j){
        while (mid > mas[i]){
            i++;
        }
        while (mid < mas[j]){
            j--;
        }
        if (i <= j){
            swap (mas[i], mas[j]);
            i++; j--;
        }
    }
    if (l < j) quick_sort (l, j);
    if (i < r) quick_sort (i, r);
}