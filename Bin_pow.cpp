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
const int N = 1e5 + 2, oo = 2e9;

ll do_it (ll a, ll n){
    if (n == 1) return a;
    if (n & 1){
        return do_it(a, n - 1) * a;
    }
    else{
        ll ans = do_it(a, n / 2);
        return ans * ans;
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie();
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    long long a, n;
    cin >> n >> a;
    cout << do_it(n, a);

    return 0;
}