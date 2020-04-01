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
using ll = long long;
const int N = 26, oo = 2e9;
int md = (1 << 20) + 1;

int trans (const string &s){
    int res = 0, p = 37, add = 1;
    for (int i = 0; i < s.size(); ++i){
        res += (s[i] * add) % md;
        add *= p;
        add %= md;
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie();
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    string s;
    cin >> s;
    cout << trans(s);

    return 0;
}