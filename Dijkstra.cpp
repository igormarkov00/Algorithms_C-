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
set <pair<int, int>> s; // множество, содержащее вторым элементом номер вершины, а первым - ее кратчайшее расстояние до исходной 
vector <pair <int , int>> connected[N]; // массив векторов, содержащих для n-ой вершины все смежные с ней. В i-ом элементе содержится пара: номер смежной с n-ой вершины и длин ребра между ними

int main()
{
    ios::sync_with_stdio(false);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int sz, edges, start; // sz - кол-во вершин в графе, edges - кол-во ребер, start - номер исходной вершины
    cin >> sz >> edges >> start; 
    fill(shortest, shortest + sz, oo); // заполняем массив предельными значениями
    start--;
    shortest[start] = 0; // расстояние от исходной вершины до самой себя равно нулю 
    for (int i = 0; i < edges; ++i){ // заполняем вектора смежных вершин
        int v1, v2, len;
        cin >> v1 >> v2 >> len;
        v1--, v2--;
        connected[v1].push_back({v2, len});
        connected[v2].push_back({v1, len}); // для неориентированного графа добавляем ребро в обратном направлении
    }
    s.insert({0, start}); // добавляем во множество исходную вершину
    while (!s.empty()){
        int current = s.begin()->second; // в роли текущей вершины на шаге цикла будет выступать та вершина из множества, до которой от исходной вершины расстояние минимальное
        s.erase(s.begin()); // затем эта вершина удаляется из множества
        for (auto x : connected[current]){
            if (shortest[x.first] > shortest[current] + x.second){ // попытка улучшить кратчайшее расстояние для смежной с текущей вершиной через кратчайшее расстояние от исходной до текущей и длины ребра между улучшаемой и текущей вершинами
                s.erase({shortest[x.first], x.first}); // удаляем вершину на случай ее нахождения во множестве (если ее там нет, ничего не произойдет)
                shortest[x.first] = shortest[current] + x.second; // обновляем кратчайшее расстояние от исходной вершины до данной
                s.insert({shortest[x.first], x.first}); // вставляем во множество эту вершину с обновленным кратчайшим расстоянием
            }
        }
    }
    for (int i = 0; i < sz; ++i){ // выводим кратчайшее расстояние до каждой из вершин
        cout << start + 1 << " -> " << i + 1 << "  ";
        if (shortest[i] == oo) cout << "Impossible" << endl; // если расстояние от исходной вершины до текущей ни разу не было улучшено, значит, путь до нее невозможен
        else cout << shortest[i] << endl;
    }

    return 0;
}