#include <bits/stdc++.h>
using namespace std;
 
struct SegLazy {
 
  struct node {
    long long sum, lazy_add;
    node() {
      sum = lazy_add = 0;
    }
  };
 
  int size = 1;
  vector<node> st;
  void init(int n) {
    size = n;
    int tree_size = 1;
    while (tree_size < n) tree_size *= 2;
    st.resize(tree_size * 2);
  }
 
  node make_node(int val) {
    node res;
    res.sum = val;
    res.lazy_add = 0;
    return res;
  }
 
  node merge(node l, node r) {
    node res;
    res.sum = l.sum + r.sum;
    return res;
  }
 
  void push(int u, int l, int r) {
    if (st[u].lazy_add == 0) return;
    if (l != r) {
      int v = 2 * u, w = 2 * u + 1;
      st[v].lazy_add += st[u].lazy_add;
      st[w].lazy_add += st[u].lazy_add;
    }
    st[u].sum += (r - l + 1) * st[u].lazy_add;
    st[u].lazy_add = 0;
  }
 
  void build(int u, int s, int e, vector<int>& a) {
    if (s == e) {
      st[u] = make_node(a[s]);
      return;
    }
    int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
    build(v, s, m, a);
    build(w, m + 1, e, a);
    st[u] = merge(st[v], st[w]);
  }
  void build(vector<int>& a) {
    build(1, 1, size, a);
  }
 
  void update(int u, int s, int e, int l, int r, int val) {
    push(u, s, e);
    if (e < l || r < s) return;
    if (l <= s && e <= r) {
      st[u].lazy_add += val;
      push(u, s, e);
      return;
    }
    int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
    push(v, s, m);
    push(w, m + 1, e);
    update(v, s, m, l, r, val);
    update(w, m + 1, e, l, r, val);
    st[u] = merge(st[v], st[w]);
  }
  void update(int l, int r, int val) {
    update(1, 1, size, l, r, val);
  }
 
  node query(int u, int s, int e, int l, int r) {
    push(u, s, e);
    if (e < l || r < s) {
      node mx = make_node(0);
      return mx;
    }
    push(v, s, m);
    push(w, m + 1, e);
    if (l <= s && e <= r) return st[u];
    int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
    node lsum = query(v, s, m, l, r);
    node rsum = query(w, m + 1, e, l, r);
    return merge(lsum, rsum);
  }
  node query(int l, int r) {
    return query(1, 1, size, l, r);
  }
};
 
int main() {
  int n, q; cin >> n >> q;
  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) cin >> a[i];
 
  SegLazy sg;
  sg.init(n);
  sg.build(a);
 
  while (q--) {
    int type; cin >> type;
    if (type == 1) {
      int l, r, v; cin >> l >> r >> v;
      sg.update(l, r, v);
    } else {
      int k; cin >> k;
      cout << sg.query(k, k).sum << '\n';
    }
  }
}