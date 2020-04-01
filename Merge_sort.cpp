#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>
using namespace std;
int m[] = {2, 1, 5, 8, 40, 3, 6, 7, 2};
void mergee (int l, int r){
    int mid = (r + l) / 2 + 1, nn1 = l, nn2 = mid, mas[r - l + 1], n = 0;
    while (nn1 < mid && nn2 <= r){
        if (m[nn1] < m[nn2]){
            mas[n] = m[nn1];
            nn1++;
        }
        else {
            mas[n] = m[nn2];
            nn2++;
        }
        n++;
    }
    for (int i = nn1; i < mid; i++, n++){
        mas[n] = m[i];
    }
    for (int i = nn2; i <= r; i++, n++){
        mas[n] = m[i];
    }
    for (int i = l; i <= r; i++){
        m[i] = mas[i - l];
    }
}
void merge_sort (int l, int r){
    if (l < r){
        merge_sort (l, (l + r) / 2);
        merge_sort ((l + r) / 2 + 1, r);
        mergee (l, r);
    }
}

int main()
{
    merge_sort(0, 8);
    for (int i = 0; i < 9; i++){
        cout << m[i] << endl;
    }

    return 0;
}