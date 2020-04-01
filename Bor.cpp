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
const int N = 26, NN = 1e4, oo = 2e9;
int sz;
struct node{
    int mas[N] = {0};
    bool flag = 0;
};
node bor[NN];

void add (const string &s){
    int cur = 0;
    for (auto let : s){
        if (!bor[cur].mas[let - 'a']){
            bor[cur].mas[let - 'a'] = ++sz;
            //memset(bor[sz].mas, 0, N * sizeof(int));
        }
        cur = bor[cur].mas[let - 'a'];
    }
    bor[cur].flag = 1;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie();
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    string s;
    cin >> s;
    add(s);

    return 0;
}
