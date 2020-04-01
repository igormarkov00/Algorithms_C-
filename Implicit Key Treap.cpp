#include <bits/stdc++.h>
using namespace std;

mt19937 gen(time(0));
typedef struct item* pitem;
struct item
{
    int value{};
    unsigned long long prior{gen()};
    int cnt{1};
    pitem l{nullptr}, r{nullptr};
    item(int value) : prior(value) {}
    item(void) {}
};

int cnt(pitem t) {
    return t? t->cnt : 0;
}

void upd_cnt(pitem t) {
    if (t) t->cnt = cnt(t->l) + cnt(t->r) + 1;
}

void split(pitem t, pitem &l, pitem &r, int key, int add = 0) {
    if (!t) return void(l = r = nullptr);
    int cur_key = add + cnt(t->l) + 1;
    if (key <= cur_key) split(t->l, l, t->l, key, add), r = t;
    else split(t->r, t->r, r, key, cur_key), l = t;
    upd_cnt(t);
}

void merge(pitem &t, pitem l, pitem r) {
    if (!l || !r) {
        t = l? l : r;
    } else if (l->prior < r->prior) {
        merge(r->l, l, r->l), t = r;
    } else {
        merge(l->r, l->r, r), t = l;
    }
    upd_cnt(t);
}

void insert(pitem &t, int key, int value) {
    pitem t1, t2;
    split(t, t1, t2, key);
    pitem node = new item(value);
    merge(t1, t1, node);
    merge(t, t1, t2);
}

void erase(pitem &t, int key, int add = 0) {
    if (t == nullptr) return;
    int cur_key = add + cnt(t->l) + 1;
    if (cur_key == key) {
        pitem t_l = t->l, t_r = t->r;
        delete t;
        merge(t, t_l, t_r);
    } else if (cur_key < key) {
        erase(t->r, key, cur_key);
    } else {
        erase(t->l, key, add);
    }
    upd_cnt(t);
}

void print_tree(pitem t, int fst = 1) {
    if (t == nullptr) return;
    print_tree(t->l, 0);
    cout << t->prior << ' ';
    print_tree(t->r, 0);
    if (fst) cout << endl;
}

void delete_tree(pitem &t) {
    while (t != nullptr) {
        erase(t, 1);
    }
}

int main(void)
{
    int n;
    cout << "Enter number of elememts in the tree: ";
    cin >> n;
    vector<int> v;
    cout << "Enter elements' value: ";
    for (int i = 0; i < n; ++i) {
        int val;
        cin >> val;
        v.push_back(val);
    }
    pitem tree{};
    for (int i = 0; i < n; ++i) {
        insert(tree, i + 1, v[i]);
    }
    print_tree(tree);
    cout << "Enter your command: ";
    string s{};
    int val1, val2;
    cin >> s;
    while (s != "stop") {
        cin >> val1;
        if (s == "erase") erase(tree, val1);
        if (s == "insert") cin >> val2, insert(tree, val1, val2);
        print_tree(tree);
        cout << "Enter your command: ";
        cin >> s;
    }

    delete_tree(tree);

    return 0;
}
