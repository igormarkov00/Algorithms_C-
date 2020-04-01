#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <string>
#include <cstring>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <cstdio>
#include <queue>
#include <stack>
#include <stdio.h>
#include <vector>
#include <assert.h>
#include <iterator>
using namespace std;
using ll = long long;
using ull = unsigned long long;
const int N = 2e5 + 2, oo = 2e9, md = 1e9 + 7;
vector <int> v[N], point;
int t[N], mn[N], cur;
vector <pair<int, int>> bridge;
bool use[N];

void dfs (int prev, int k){
    use[k] = 1;
    t[k] = ++cur;
    int cur_mn = cur, cnt = 0;
    bool flag = 0;
    for (auto next : v[k]){
        if (prev == next) continue;
        if (!use[next]){
            dfs(k, next);
            cur_mn = min(cur_mn, mn[next]);
            if (mn[next] >= t[k] && prev != -1) flag = 1;
            cnt++;
        }
        else cur_mn = min(cur_mn, t[next]);
    }
    if (flag || (prev == -1 && cnt > 1)) point.push_back(k);
    mn[k] = cur_mn;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie();
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int n, m;
    cin >> n >> m;
    fill(mn, mn + n, oo);
    for (int i = 0; i < m; ++i){
        int a, b;
        cin >> a >> b;
        a--, b--;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    dfs(-1, 0);
    /*for (int i = 0; i < n; ++i){
        cout << t[i] << ' ' << mn[i] << endl;
    }*/
    for (auto x : point) cout << x + 1 << ' ';

    return 0;
}