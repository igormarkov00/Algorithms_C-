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
const int N = 1e5 + 2, oo = 2e9, md = 1e9 + 7;
vector <int> connected[N]; // Массив векторов для каждой вершины, содержащий номера смежных с ней вершин
bool use[N]; // массив, позволяющий определить, какие из вершин уже были посещены в ходе алгоритма 

void dfs (int current){
    if (use[current]) return; // условие выхода из рекурсии -  вершина на текущем шаге уже была посещена
    use[current] = 1; // помечаем текущую вершину как посещенную
    for (auto next : connected[current]) dfs(next); // вызываем DFS от всех смежных с текущей вершин
}

int main()
{
    ios::sync_with_stdio(false); cin.tie();
    //freopen("input.txt","r", stdin);
    //freopen("output.txt", "w", stdout);

    int sz, edges, start; // sz - кол-во вершин в графе, edges - количество ребер, start - номер исходной вершины
    cin >> sz >> edges >> start;
    for (int i = 0; i < edges; ++i){
        int v1, v2;
        cin >> v1 >> v2;
        v1--, v2--; // приводим вершины в вид, соответсвующий их номерам в массивах (начиная с 0, а не с 1)
        connected[v1].push_back(v2); // добавляем инцедентные ребру вершины в вектора друг к другу
        connected[v2].push_back(v1); // для неориентированного графа также добавляем ребро в обратном направлении
    }
    dfs(start - 1); // запускаем алгоритм от стартовой вершины

    return 0;
}