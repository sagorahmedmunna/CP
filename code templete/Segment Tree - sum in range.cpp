void build(int node, int s, int e) {
    if (s == e) {
        tree[node] = a[s]; return;
    }
    int m = (s + e) / 2;
    build(node * 2, s, m);
    build(node * 2 + 1, m + 1, e);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}
 
void update(int node, int s, int e, int idx, int val) {
    if (s == e) {
        tree[node] = val;
        a[idx] = val;
        return;
    }
    int m = (s + e) / 2;
    if (idx <= m) update(node * 2, s, m, idx, val);
    else update(node * 2 + 1, m + 1, e, idx, val);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}
 
long long query(int node, int s, int e, int l, int r) {
    if (s > r || e < l) return 0LL;
    if (s >= l && e <= r) return tree[node];
    int m = (s + e) / 2;
    long long q1 = query(node * 2, s, m, l, r);
    long long q2 = query(node * 2 + 1, m + 1, e, l, r);
    return q1 + q2;
}
