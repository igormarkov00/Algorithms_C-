#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
const int N = 1e4 + 2, oo = 2e9;
vector <int> mas1, mas2;
int res[N];

void mult(){
    for (int i = 0; i < mas1.size(); ++i){
        for (int j = 0; j < mas2.size(); ++j){
            int k = i + j + 1;
            res[k] += mas1[i] * mas2[j];
            if (res[k] > 100000000){
                res[k + 1] += res[k] / 10;
                res[k] %= 10;
            }
        }
    }
    int sz = 1, per = 0;
    for (int i = 1; i < N; ++i){
        res[i] += per;
        per = res[i] / 10;
        res[i] %= 10;
        if (res[i]) sz = i;
    }
    res[0] = sz;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie();
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    string s1, s2;
    cin >> s1 >> s2;
    //if (s1 == "5" && s2 == "7") assert(0);
    for (int i = 0; i < s1.size(); ++i){
        mas1.push_back(s1[i] - '0');
    }
    reverse(mas1.begin(), mas1.end());
    for (int i = 0; i < s2.size(); ++i){
        mas2.push_back(s2[i] - '0');
    }
    reverse(mas2.begin(), mas2.end());
    mult();
    for (int i = res[0]; i > 0; --i){
        cout << res[i];
    }

    return 0;
}