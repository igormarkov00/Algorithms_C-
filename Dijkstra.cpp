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
const int N = 1e4, oo = 2e9; // oo - ��������� ������� ���������� �� ����� ������� �� ������, N - ���������� ���-�� ������
int shortest[N]; // ������ ���������� ���������� �� �������� ������� �� ���� ���������
set <pair<int, int>> s; // ���������, ���������� ������ ��������� ����� �������, � ������ - �� ���������� ���������� �� �������� 
vector <pair <int , int>> connected[N]; // ������ ��������, ���������� ��� n-�� ������� ��� ������� � ���. � i-�� �������� ���������� ����: ����� ������� � n-�� ������� � ���� ����� ����� ����

int main()
{
    ios::sync_with_stdio(false);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int sz, edges, start; // sz - ���-�� ������ � �����, edges - ���-�� �����, start - ����� �������� �������
    cin >> sz >> edges >> start; 
    fill(shortest, shortest + sz, oo); // ��������� ������ ����������� ����������
    start--;
    shortest[start] = 0; // ���������� �� �������� ������� �� ����� ���� ����� ���� 
    for (int i = 0; i < edges; ++i){ // ��������� ������� ������� ������
        int v1, v2, len;
        cin >> v1 >> v2 >> len;
        v1--, v2--;
        connected[v1].push_back({v2, len});
        connected[v2].push_back({v1, len}); // ��� ������������������ ����� ��������� ����� � �������� �����������
    }
    s.insert({0, start}); // ��������� �� ��������� �������� �������
    while (!s.empty()){
        int current = s.begin()->second; // � ���� ������� ������� �� ���� ����� ����� ��������� �� ������� �� ���������, �� ������� �� �������� ������� ���������� �����������
        s.erase(s.begin()); // ����� ��� ������� ��������� �� ���������
        for (auto x : connected[current]){
            if (shortest[x.first] > shortest[current] + x.second){ // ������� �������� ���������� ���������� ��� ������� � ������� �������� ����� ���������� ���������� �� �������� �� ������� � ����� ����� ����� ���������� � ������� ���������
                s.erase({shortest[x.first], x.first}); // ������� ������� �� ������ �� ���������� �� ��������� (���� �� ��� ���, ������ �� ����������)
                shortest[x.first] = shortest[current] + x.second; // ��������� ���������� ���������� �� �������� ������� �� ������
                s.insert({shortest[x.first], x.first}); // ��������� �� ��������� ��� ������� � ����������� ���������� �����������
            }
        }
    }
    for (int i = 0; i < sz; ++i){ // ������� ���������� ���������� �� ������ �� ������
        cout << start + 1 << " -> " << i + 1 << "  ";
        if (shortest[i] == oo) cout << "Impossible" << endl; // ���� ���������� �� �������� ������� �� ������� �� ���� �� ���� ��������, ������, ���� �� ��� ����������
        else cout << shortest[i] << endl;
    }

    return 0;
}