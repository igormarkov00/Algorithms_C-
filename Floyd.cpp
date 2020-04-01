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
const int N = 500, oo = 2e9; // oo - ��������� ������� ���������� �� ����� ������� �� ������, N - ���������� ���-�� ������
int shortest[N][N]; // ������ ���������� ���������� ����� ������ ������

int main()
{
    ios::sync_with_stdio(false);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int sz, edges; // sz - ���-�� ������ � �����, edges - ���-�� �����
    cin >> sz >> edges;
    for (int i = 0; i < sz; ++i)
        for (int j = 0; j < sz; ++j) if (i != j) shortest[i][j] = oo; // ��������� ���������� ����������� ���������� (����� ���������� ������ �� ����� ����)
    for (int i = 0; i < edges; ++i){
        int v1, v2, len;
        cin >> v1 >> v2 >> len;
        v1--, v2--; // �������� ������� � ���, �������������� �� ������� � �������� (������� � 0, � �� � 1)
        shortest[v1][v2] = len; // ���������� ����� ��������� ����� ����� ����� ����� ���� 
        shortest[v2][v1] = len; // ��� ������������������ ����� ����� ��������� ����� � �������� �����������
    }
    for (int k = 0; k < sz; ++k)
        for (int j = 0; j < sz; ++j)
            for (int i = 0; i < sz; ++i) shortest[j][i] = min(shortest[j][i], shortest[j][k] + shortest[k][i]); // �������� �������� ���������� �� ������� j �� ������� i, ������ ����� ������� k
    for (int i = 0; i < sz; ++i){
        for (int j = 0; j < sz; ++j){ // ������� ���������� ���������� ����� ����� ������ ������
            cout << i + 1 << " -> " << j + 1 << "  ";
            if (shortest[i][j] == oo) cout << "Impossible\n"; // ���� ���������� ����� ����� ������ �� ��������, �� ���� �� ������ �� ������ ����������
            else cout << shortest[i][j] << endl;
        }
    }

    return 0;
}