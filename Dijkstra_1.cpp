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
using namespace std;
const int N = 100000, oo = 1e9;
int mas[N], mn;
bool use[N];
struct edge{
    int a, b, l;
};
vector <pair<int, int>> v[N];


int main()
{
    ios::sync_with_stdio(false);
    //freopen("horse.in", "r", stdin);
    //freopen("horse.out", "w", stdout);
    
    for (int i = 0; i < N; i++){
        mas[i] = oo;
    }
    mas[0] = 0;
    for (int i = 0; i < N; i++){
        mn = -1;
        for (int j = 0; j < N; j++){
            if (!use[j] && (mn == -1 || mas[j] < mas[mn])) {
                mn = j;
            }
        }
        if (mas[mn] == oo) break;
        use[mn] = 1;
        for (auto x : v[mn]){
            mas[x.first] = min(mas[x.first], mas[mn] + x.second);
        }
    }

    return 0;
}