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
const int N = 1e5;
int sz = 1;
struct vertex{
    int sum, add = 0;
    bool flag = 0;
};
vertex tree[N];

void update (int left, int right, int add, int vLeft, int vRight, int ver){
    if (left > right) return;
    if (vLeft == left && vRight == right){
        tree[ver].add += add;
        tree[ver].sum += add * (vRight - vLeft + 1);
        return;
    }
    int mid = (vRight + vLeft) / 2;
    update(left, min(mid, right), add, vLeft, mid, ver * 2);
    update(max(mid + 1, left), right, add, mid + 1, vRight, ver * 2 + 1);
    tree[ver].sum = tree[ver * 2].sum + tree[ver * 2 + 1].sum;
}

void push (int ver){
    if (ver >= sz) return;
    tree[ver * 2].add += tree[ver].add;
    tree[ver * 2 + 1].add += tree[ver].add;
    tree[ver * 2].sum += tree[ver].add;
    tree[ver * 2 + 1].sum += tree[ver].add;
    tree[ver].add = 0;
}

void push2 (int ver){
    if (ver >= sz || !tree[ver].flag) return;
    tree[ver].flag = 0;
    tree[ver * 2].flag = tree[ver * 2 + 1].flag = 1;
    tree[ver * 2].sum = tree[ver * 2 + 1].sum = tree[ver].sum / 2;
}

int get_sum (int left, int right, int vLeft, int vRight, int ver){
    if (left > right) return 0;
    if (left == vLeft && vRight == right){
        return tree[ver].sum;
    }
    push(ver);
    int mid = (vLeft + vRight) / 2;
    return get_sum(left, min(mid, right), vLeft, mid, ver * 2) + get_sum(max(mid + 1, left), right, mid + 1, vRight, ver * 2 + 1);
}

void assignation (int left, int right, int ver, int vLeft, int vRight, int value){
    if (left > right) return;
    if (left == vLeft && right == vRight){
        tree[ver].flag = 1;
        tree[ver].sum = value * (vRight - vLeft + 1);
        return;
    }
    int mid = (vRight + vLeft) / 2;
    push2(ver);
    assignation(left, min(mid, right), ver * 2, vLeft, mid, value);
    assignation(max(mid + 1, left), right, ver * 2 + 1, mid + 1, vRight, value);
    tree[ver].sum = tree[ver * 2].sum + tree[ver * 2 + 1].sum;
}

int main()
{
    ios::sync_with_stdio(false);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int n, k;
    cin >> n >> k;
    while (sz < n) sz *= 2;
    for (int i = sz; i < sz + n; ++i) cin >> tree[i].sum;
    for (int i = sz + n; i < 2 * sz; ++i) tree[i].sum = 0;
    for (int i = sz - 1; i > 0; --i) tree[i].sum = tree[i * 2].sum + tree[i * 2 + 1].sum;
    for (int i = 0; i < k; ++i){
        string s;
        int left, right;
        cin >> s >> left >> right;
        if (s == "add"){
            int add;
            cin >> add;
            update (left, right, add, 1, sz, 1);
        }
        if (s == "sum") cout << get_sum(left, right, 1, sz, 1) << endl;
        if (s == "assign"){
            int value;
            cin >> value;
            assignation(left, right, 1, 1, sz, value);
        }
    }

    return 0;
}