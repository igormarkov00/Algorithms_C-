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
struct point2D{
    int x, y;

    point2D(){
        x = y = 0;
    }
    point2D(int x1, int y1) : x(x1), y(y1){}
    ~point2D(){cout << "distructor";}

    void scan(){
        cin >> x >> y;
    }
    void print();
};

int main()
{
    ios::sync_with_stdio(false);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    point2D p1, p2, p3;
    p1.scan();
    p2.scan();
    p3.scan();
    p1.print();

    return 0;
}
void point2D::print() { cout << x << ' ' << y << endl; }
