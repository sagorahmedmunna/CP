#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int a[N], tree[N * 4];

void build(int node, int st, int en) {
    if (st == en) {
        tree[node] = a[st]; return;
    }
    int mid = (st + en) / 2;
    build(node * 2, st, mid);
    build(node * 2 + 1, mid + 1, en);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

long long query(int node, int st, int en, int l, int r) {
    if (st > r || en < l) return 0LL;
    if (st >= l && en <= r) return tree[node];
    int mid = (st + en) / 2;
    long long q1 = query(node * 2, st, mid, l, r);
    long long q2 = query(node * 2 + 1, mid + 1, en, l, r);
    return q1 + q2;
}

void update(int node, int st, int en, int idx, int val) {
    if (st == en) {
        tree[node] = val;
        a[idx] = val;
        return;
    }
    int mid = (st + en) / 2;
    if (idx <= mid) update(node * 2, st, mid, idx, val);
    else update(node * 2 + 1, mid + 1, en, idx, val);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}