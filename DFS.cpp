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
vector <int> connected[N]; // ������ �������� ��� ������ �������, ���������� ������ ������� � ��� ������
bool use[N]; // ������, ����������� ����������, ����� �� ������ ��� ���� �������� � ���� ��������� 

void dfs (int current){
    if (use[current]) return; // ������� ������ �� �������� -  ������� �� ������� ���� ��� ���� ��������
    use[current] = 1; // �������� ������� ������� ��� ����������
    for (auto next : connected[current]) dfs(next); // �������� DFS �� ���� ������� � ������� ������
}

int main()
{
    ios::sync_with_stdio(false); cin.tie();
    //freopen("input.txt","r", stdin);
    //freopen("output.txt", "w", stdout);

    int sz, edges, start; // sz - ���-�� ������ � �����, edges - ���������� �����, start - ����� �������� �������
    cin >> sz >> edges >> start;
    for (int i = 0; i < edges; ++i){
        int v1, v2;
        cin >> v1 >> v2;
        v1--, v2--; // �������� ������� � ���, �������������� �� ������� � �������� (������� � 0, � �� � 1)
        connected[v1].push_back(v2); // ��������� ����������� ����� ������� � ������� ���� � �����
        connected[v2].push_back(v1); // ��� ������������������ ����� ����� ��������� ����� � �������� �����������
    }
    dfs(start - 1); // ��������� �������� �� ��������� �������

    return 0;
}