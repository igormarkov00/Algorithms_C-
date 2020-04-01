I)
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>
#include <cstdio>
using namespace std;

struct Node {
    string color;
    Node *prev;
};

void add (Node *&head, string col){
    Node *n = new Node;
    n -> color = col;
    n -> prev = head;
    head = n;
}
void del (Node *&head) {
    Node *tmp = head;
    head = head -> prev;
    delete tmp;
}

int main()
{
    ios::sync_with_stdio(false);

    Node *head = 0;
    add (head, "red");
    add (head, "green");
    add (head, "blue");
    while (head){
        cout << head -> color << endl;
        del (head);
    }


    return 0;
}



II)
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>
#include <cstdio>
using namespace std;

struct Node {
    string color;
    Node *prev;
    Node (string col, Node *p){
        color = col;
        prev = p;
    }
};

void add (Node *&head, string col){
    Node *n = new Node (col, head);
    head = n;
}
void del (Node *&head) {
    Node *tmp = head;
    head = head -> prev;
    delete tmp;
}

int main()
{
    ios::sync_with_stdio(false);

    Node *head = 0;
    add (head, "red");
    add (head, "green");
    add (head, "blue");
    while (head){
        cout << head -> color << endl;
        del (head);
    }


    return 0;
}