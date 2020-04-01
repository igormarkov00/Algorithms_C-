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

double f (double p){
    return 2 * p * p + 9 * p - 12;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie();
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    double l, r;
    cin >> l >> r;
    double a, b;
    while (fabs(r - l) > 1e-6){
        a = l + (r - l) / 3, b = r - (r - l) / 3;
        if (f(a) < f(b)) r = b;
        else l = a;
    }
    cout << l;

    return 0;
} 