#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <cstdio>
#include <queue>
#include <stack>
#include <stdio.h>
using namespace std;
const int N = 1e5, oo = 1e9;
int mas[N], n, sz = 1;

void build (int k){
    if (k >= sz) return;
    build(k * 2);
    build(k * 2 + 1);
    mas[k] = max(mas[k * 2], mas[k * 2 + 1]);
}

void upd (int j, int m){
    j += sz;
    mas[j] = m;
    while (j) mas[j] = max(m, mas[j]), j /= 2;
}
void upd2 (int j, int m){
    j += sz;
    m -= mas[j];
    while (j) mas[j] += m, j /= 2;
}

int get_max (int l, int r){
    l += sz - 1, r += sz - 1;
    int mx = -oo;
    while (l <= r){
        if (l & 1) mx = max(mx, mas[l]), l++;
        if (~r & 1) mx = max(mx, mas[r]), r--;
        l /= 2; r /= 2;
    }
    return mx;
}

int sum_rec (int v, int l, int r, int vl, int vr){
    if (r < l) return 0;
    if (vl == l && vr == r) return mas[v];
    int mid = (vr + vl) / 2;
    return sum_rec(v * 2, l, min(r, mid), vl, mid) + sum_rec(v * 2 + 1, max(l, mid + 1), r, mid + 1, vr);
}

int main()
{
    ios::sync_with_stdio(false);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    /*3 6 4 9 14 3 2 8
     6   9    14  8
       9        14
           14*/

    cin >> n;
    while (sz < n) sz *= 2;
    for (int i = 0; i < n; ++i) cin >> mas[i + sz];
    for (int i = n; i < sz; ++i) mas[i + sz] = -oo;
    //build(1);
    for (int i = sz - 1; i > 0; --i){
        mas[i] = max(mas[i * 2], mas[i * 2 + 1]);
    }
    int v, m;
    //cin >> n >> m;
    //upd(v, m);
    //for (int i = 1; i < sz * 2; ++i) cout << mas[i] << ' ';
    int l, r;
    cin >> l >> r;
    int mx = get_max(l, r);
    cout << mx;

    return 0;
}