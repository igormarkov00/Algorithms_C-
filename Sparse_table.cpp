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
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5, oo = 2e9, NN = 30;
int tree[N][NN], mas[N];

int main()
{
    ios::sync_with_stdio(false); cin.tie();
    //freopen("input.in", "r", stdin);
    //freopen("output.out", "w", stdout);

    int n, m;
    cin >> n >> m >> tree[0][0];
    for (int j = 1; j < N; ++j) tree[j][0] = (tree[j - 1][0] * 23 + 21563) % 16714589;
    for (int i = 1; i < NN; ++i){
        for (int j = 0; j < N; ++j){
            if (j + (1 << i) <= n)tree[j][i] = min(tree[j][i - 1], tree[j + (1 << (i - 1))][i - 1]);
        }
    }
    int j = 1, l, r, ans, len, st = 0;
    for (int i = 1; i <= n; ++i){
        if (j * 2 <= i) j *= 2, st++;
        mas[i] = st;
    }
    /*for (int i = 0; i < n; ++i) cout << mas[i] << ' ';
    cout << endl;
    for (int i = 0; i < n; ++i) cout << tree[i][0] << ' ';*/
    cin >> l >> r;
    len = abs(r - l) + 1;
    ans = min(tree[min(l, r) - 1][mas[len]], tree[max(l, r) - (1 << mas[len])][mas[len]]);
    //cout << endl << len << ' ' << l << ' ' << r << ' ' << tree[min(l, r) - 1][mas[len]] << ' ' << tree[max(l, r) - (1 << mas[len])][mas[len]] << ' ' << ans << endl;
    for (int i = 1; i < m; ++i){
        l = (17 * l + 751 + ans + 2 * (i)) % n + 1;
        r = (13 * r + 593 + ans + 5 * (i)) % n + 1;
        len = abs(r - l) + 1;
        ans = min(tree[min(l, r) - 1][mas[len]], tree[max(l, r) - (1 << mas[len])][mas[len]]);
        //cout << len << ' ' << l << ' ' << r << ' ' << tree[min(l, r) - 1][mas[len]] << ' ' << tree[max(l, r) - (1 << mas[len])][mas[len]] << ' ' << ans << endl;
    }
    cout << l << ' ' << r << ' ' << ans;

    return 0;
}