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

const int N = 1e5, oo = 2e9; // oo - ��������� ������� ���������� �� ����� ������� �� ������, N - ���������� ���-�� ������
vector <int> connected[N]; // ������ �������� ��� ������ �������, ���������� ������ ������� � ��� ������
int shortest[N]; // ������ ���������� ���������� �� ������ �� ������ �� ��������
queue <int> q; 

void bfs (int n){
    fill(shortest, shortest + N, oo); // ��������� ������ ���������� ���������� ����������, ������� ���������� ������� ��� �������� ��������
    shortest[n] = 0; // ���������� �� �������� ������� �� ��� ����� ����� ����
    q.push(n); // ��������� �������� ������� � �������
    while (!q.empty()){
        int current = q.front(); // ������� �������� �� ���� ����� �������� ������ ������� �������
        q.pop(); // ������ ������� ������� �� �������
        for (auto x : connected[current]){
            if (shortest[current] + 1 < shortest[x]){ // ����, ������ ����� ������� �������, �� ������ �������� ���������� ���������� �� �������� ������� �� ������� �, �� �� ��������� ���������� ���������� ��� ��� � ��������� �� � �������, ����� ����������� �������� ���������� ��� ������� � ��� ������, ������ ����� ���
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

    int sz, edges, start; // sz - ���-�� ������ � �����, edges - ���������� �����, start - ����� �������� �������
    cin >> sz >> edges >> start;
    for (int i = 0; i < edges; ++i){
        int v1, v2;
        cin >> v1 >> v2;
        v1--, v2--; // �������� ������� � ���, �������������� �� ������� � �������� (������� � 0, � �� � 1)
        connected[v1].push_back(v2); // ��������� ������� ����� � ������� ���� � �����
        connected[v2].push_back(v1); // ��� ������������������ ����� ����� ��������� ����� � �������� �����������
    }
    bfs(start - 1); // ��������� �������� �� ��������� �������
    for (int i = 0; i < sz; ++i){ // ������� ���������� ���������� �� ������ �� ������
        cout << start << " -> " << i + 1 << "  ";
        if (shortest[i] == oo) cout << "Impossible" << endl; // ���� ���������� �� �������� ������� �� ������� �� ���� �� ���� ��������, ������, ���� �� ��� ����������
        else cout << shortest[i] << endl;
    }

    return 0;
}