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
struct edge{
    int a, b, len; // ������� ���������, ��� ����� ��������� ����� � ���� ���� ����������: a - ������ �������, b - ������ �������, len ��� ����� 
};
vector <edge> ed; // ������, � ������� ����� ��������� ����� 

int main()
{
    ios::sync_with_stdio(false);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int sz, edges, start; // sz - ���-�� ������ � �����, edges - ���-�� �����, start - ����� �������� �������
    cin >> sz >> edges >> start;
    fill(shortest, shortest + sz, oo); // ��������� ������ ����������� ����������
    shortest[start - 1] = 0; // ���������� �� �������� ������� �� ����� ���� ����� ����
    for (int i = 0; i < edges; ++i){
        edge v;
        cin >> v.a >> v.b >> v.len;
        v.a--, v.b--;
        ed.push_back(v);
        v.a += v.b, v.b = v.a - v.b, v.a -= v.b;
        ed.push_back(v);// ��� ������������������ ����� ����� ��������� ����� � �������� �����������
    }
    for (int i = 0; i < sz - 1; ++i){
        for (int j = 0; j < ed.size(); ++j){
            if (shortest[ed[j].a] < oo) shortest[ed[j].b] = min(shortest[ed[j].b], shortest[ed[j].a] + ed[j].len); // �������� �������� ���������� �� ������ ������� �����, ����� �������������� ���������� �� ������ ������� � �������� �����. ��� ���� ������ �������� �� ��, ��� �� �������� ������� �� ������ ������� ����� ������� ����
        }
    }
    for (int i = 0; i < sz; ++i){ // ������� ���������� ���������� �� ������ �� ������
        cout << start << " -> " << i + 1 << "  ";
        if (shortest[i] == oo) cout << "Impossible" << endl; // ���� ���������� �� �������� ������� �� ������� �� ���� �� ���� ��������, ������, ���� �� ��� ����������
        else cout << shortest[i] << endl;
    }

    return 0;
}