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

const int N = 1e5, oo = 2e9; // oo - предельно большое расстояние от одной вершины до другой, N - предельное кол-во вершин
vector <int> connected[N]; // Массив векторов для каждой вершины, содержащий номера смежных с ней вершин
int shortest[N]; // Массив кратчайших расстояний до каждой из вершин из исходной
queue <int> q; 

void bfs (int n){
    fill(shortest, shortest + N, oo); // заполняем массив кратчайших расстояний значениями, которых невозможно достичь при заданных условиях
    shortest[n] = 0; // расстояние от исходной вершины до нее самой равно нулю
    q.push(n); // добавляем исходную вершину в очередь
    while (!q.empty()){
        int current = q.front(); // текущей вершиной на шаге цикла является первый элемент очереди
        q.pop(); // взятую вершину удаляем из очереди
        for (auto x : connected[current]){
            if (shortest[current] + 1 < shortest[x]){ // если, пройдя через текущую вершину, мы сможем добиться уменьшения расстояния от исходной вершины до вершины Х, то мы обновляем кратчайшее расстояние для нее и добавляем ее в очередь, чтобы попробовать улучшить расстояния для смежных с ней вершин, пройдя через нее
                shortest[x] = shortest[current] + 1;
                q.push(x);
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int sz, edges, start; // sz - кол-во вершин в графе, edges - количество ребер, start - номер исходной вершины
    cin >> sz >> edges >> start;
    for (int i = 0; i < edges; ++i){
        int v1, v2;
        cin >> v1 >> v2;
        v1--, v2--; // приводим вершины в вид, соответсвующий их номерам в массивах (начиная с 0, а не с 1)
        connected[v1].push_back(v2); // добавляем вершины ребра в вектора друг к другу
        connected[v2].push_back(v1); // для неориентированного графа также добавляем ребро в обратном направлении
    }
    bfs(start - 1); // запускаем алгоритм от стартовой вершины
    for (int i = 0; i < sz; ++i){ // выводим кратчайшее расстояние до каждой из вершин
        cout << start << " -> " << i + 1 << "  ";
        if (shortest[i] == oo) cout << "Impossible" << endl; // если расстояние от исходной вершины до текущей ни разу не было улучшено, значит, путь до нее невозможен
        else cout << shortest[i] << endl;
    }

    return 0;
}