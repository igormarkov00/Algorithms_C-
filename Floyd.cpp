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
const int N = 500, oo = 2e9; // oo - предельно большое расстояние от одной вершины до другой, N - предельное кол-во вершин
int shortest[N][N]; // массив кратчайших расстояний между парами вершин

int main()
{
    ios::sync_with_stdio(false);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int sz, edges; // sz - кол-во вершин в графе, edges - кол-во ребер
    cin >> sz >> edges;
    for (int i = 0; i < sz; ++i)
        for (int j = 0; j < sz; ++j) if (i != j) shortest[i][j] = oo; // заполняем расстояния предельными значениями (кроме расстояний вершин до самих себя)
    for (int i = 0; i < edges; ++i){
        int v1, v2, len;
        cin >> v1 >> v2 >> len;
        v1--, v2--; // приводим вершины в вид, соответсвующий их номерам в массивах (начиная с 0, а не с 1)
        shortest[v1][v2] = len; // расстояние между вершинами равно длине ребра между ними 
        shortest[v2][v1] = len; // для неориентированного графа также добавляем ребро в обратном направлении
    }
    for (int k = 0; k < sz; ++k)
        for (int j = 0; j < sz; ++j)
            for (int i = 0; i < sz; ++i) shortest[j][i] = min(shortest[j][i], shortest[j][k] + shortest[k][i]); // пытаемся улучшить расстояние от вершины j до вершины i, пройдя через вершину k
    for (int i = 0; i < sz; ++i){
        for (int j = 0; j < sz; ++j){ // выводим кратчайшие расстояния между всеми парами вершин
            cout << i + 1 << " -> " << j + 1 << "  ";
            if (shortest[i][j] == oo) cout << "Impossible\n"; // если расстояние между парой вершин не улучшено, то путь от первой до второй невозможен
            else cout << shortest[i][j] << endl;
        }
    }

    return 0;
}