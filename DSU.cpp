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
#include <vector>
#include <assert.h>
#include <iterator>
using namespace std;
const int N = 1e5;
int mas[N], sz[N];

int find_head (int k){
    if (k == mas[k]) return k;
    return mas[k] = find_head(mas[k]);
}

void unite (int h1, int h2){
    h1 = find_head(h1), h2 = find_head(h2);
    if (h1 != h2){
        if (sz[h1] > sz[h2]) swap(h1, h2);
        sz[h2] += sz[h1];
        mas[h1] = h2;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    fill(sz, sz + N, 1);

    return 0;
}