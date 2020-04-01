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
    Node *next;
    Node (string col){
        color = col;
        next = 0;
    }
};

void add (Node *&head, Node *&tail, string col){
    //if (queue is empty) changing both;
    Node *n = new Node (col);
    head -> next = n;
    head = n;
}
void del (Node *&tail) {
    //if (queue becomes empty) both equal 0;
    Node *tmp = tail;
    tail = tail -> next;
    delete tmp;  
}

int main()
{
    ios::sync_with_stdio(false);

    Node *head = 0, *tail = 0;
    add (head, "red");
    add (head, "green");
    add (head, "blue");
    while (tail != head){
        cout << tail -> color << endl;
        del (tail);
    }


    return 0;
}
