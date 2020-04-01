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
const int N = 1e4, oo = 2e9; // oo - предельно большое расстояние от одной вершины до другой, N - предельное кол-во вершин
int shortest[N]; // массив кратчайших расстояний от исходной вершины до всех остальных
struct edge{
    int a, b, len; // создаем структуру, где будут храниться ребра в виде трех переменных: a - первая вершина, b - вторая вершина, len вес ребра 
};
vector <edge> ed; // вектор, в котором будут храниться ребра 

int main()
{
    ios::sync_with_stdio(false);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int sz, edges, start; // sz - кол-во вершин в графе, edges - кол-во ребер, start - номер исходной вершины
    cin >> sz >> edges >> start;
    fill(shortest, shortest + sz, oo); // заполняем массив предельными значениями
    shortest[start - 1] = 0; // расстояние от исходной вершины до самой себя равно нулю
    for (int i = 0; i < edges; ++i){
        edge v;
        cin >> v.a >> v.b >> v.len;
        v.a--, v.b--;
        ed.push_back(v);
        v.a += v.b, v.b = v.a - v.b, v.a -= v.b;
        ed.push_back(v);// для неориентированного графа также добавляем ребро в обратном направлении
    }
    for (int i = 0; i < sz - 1; ++i){
        for (int j = 0; j < ed.size(); ++j){
            if (shortest[ed[j].a] < oo) shortest[ed[j].b] = min(shortest[ed[j].b], shortest[ed[j].a] + ed[j].len); // пытаемся улучшить расстояние до второй вершины ребра, путем задействования расстояния до первой вершины и текущего ребра. При этом делаем проверку на то, что от исходной вершины до первой вершины ребра имеется путь
        }
    }
    for (int i = 0; i < sz; ++i){ // выводим кратчайшее расстояние до каждой из вершин
        cout << start << " -> " << i + 1 << "  ";
        if (shortest[i] == oo) cout << "Impossible" << endl; // если расстояние от исходной вершины до текущей ни разу не было улучшено, значит, путь до нее невозможен
        else cout << shortest[i] << endl;
    }

    return 0;
}