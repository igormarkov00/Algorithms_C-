#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int l, r, mid;
    while (l < r){
        mid = (r + l) / 2;
        if (mas[mid] < mas2[i]) l = mid + 1;
        else r = mid;
    }
    if (mas[r] == mas2[i]) cout << "yes";
    else cout << "no";

    return 0;
}