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
using ull = unsigned long long;
using ld = long double;
const int N = 1e5 + 2, oo = 2e9, md = 1e9 + 7, K = 5e3;

class Figure{
public:
    virtual void readALL() = 0;
    virtual void printALL() = 0;
    int a;
private:
    int b;
protected:
    int c;
public:
    virtual void func(){cout << "Hello\n";}
};

class Circle: public Figure{
    int x, y, r;
public:
    virtual void readALL()override{
        cin >> x >> y >> r;
    }
    virtual void func()override{cin >> a >> c;}
    virtual void printALL()override{
        cout << "Centre coordinates are: " << x << ' ' << y << endl << "Radius is: " << r << endl;
    }
};

class Rect: public Figure{
    int x, y, width, height;
public:
    virtual void readALL()override{
        cin >> x >> y >> width >> height;
    }
    virtual void printALL()override{
        cout << "Centre coordinates are: " << x << ' ' << y << endl << "Width is: " << width << endl << "Height is: " << height << endl;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(); cout.tie();

    //freopen("input.txt","r", stdin);
    //freopen("output.txt", "w", stdout);

    /*Circle cir;
    cir.readALL();
    cir.printALL();
    Rect rec;
    rec.readALL();
    rec.printALL();*/
    Figure *fig = new Circle();
    fig->func();
    delete fig;

    return 0;
}