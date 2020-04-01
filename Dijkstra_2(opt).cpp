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
int mn, mas[N]; 
vector <pair<int, int>> v[N];
set <pair<int, int>> s;

int main()
{
    ios::sync_with_stdio(false);
    //freopen("horse.in", "r", stdin);
    //freopen("horse.out", "w", stdout);
    
    fill(mas + 1, mas + N, oo);
    s.insert({0, 0});
    while(!s.empty()){
    	mn = s.begin()->second; 
        s.erase(s.begin());
        for (auto x : v[mn]){
	    if (mas[x.first] > mas[mn] + x.second) {
                s.erase({mas[x.first], x.first});
                mas[x.first] = min(mas[x.first], mas[mn] + x.second);
                s.insert({mas[x.first], x.first});
	    }
        }
    }

    return 0;
}