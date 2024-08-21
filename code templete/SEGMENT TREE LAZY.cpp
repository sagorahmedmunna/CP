// Range Update Queries
// https://cses.fi/problemset/task/1651

#include <bits/stdc++.h>
using namespace std;
 
struct SegmentTreeLazy {
  struct node { #change
    long long sum, lazy_add;
    node() {
      sum = lazy_add = 0;
    }
  };
  int size = 1;
  vector<node> st;
  SegmentTreeLazy() {}
  SegmentTreeLazy(int n) { Initial(n); }
  SegmentTreeLazy(vector<int>& a) {
    Initial((int)a.size() - 1);
    Build(1, 1, size, a);
  }
  void Initial(int _n) {
    size = _n;
    int tree_size = 1;
    while (tree_size < n) tree_size *= 2;
    st.resize(tree_size * 2);
  }
  node Make_node(long long val) { #change
    node res;
    res.sum = val;
    res.lazy_add = 0;
    return res;
  }
  node Merge(node& l, node& r) { #change
    node res;
    res.sum = l.sum + r.sum;
    return res;
  }
  void Push(int u, int l, int r) { #change
    if (st[u].lazy_add == 0) return;
    if (l != r) {
      int v = 2 * u, w = 2 * u + 1;
      st[v].lazy_add += st[u].lazy_add;
      st[w].lazy_add += st[u].lazy_add;
    }
    st[u].sum += (r - l + 1) * st[u].lazy_add;
    st[u].lazy_add = 0;
  }
  void Build(int u, int s, int e, vector<int>& a) {
    if (s == e) {
      st[u] = Make_node(a[s]);
      return;
    }
    int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
    Build(v, s, m, a);
    Build(w, m + 1, e, a);
    st[u] = Merge(st[v], st[w]);
  }
  void Update(int u, int s, int e, int l, int r, int val) {
    Push(u, s, e);
    if (e < l || r < s) return;
    if (l <= s && e <= r) {
      st[u].lazy_add += val;
      Push(u, s, e);
      return;
    }
    int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
    Update(v, s, m, l, r, val);
    Update(w, m + 1, e, l, r, val);
    st[u] = Merge(st[v], st[w]);
  }
  void Update(int l, int r, int val) {
    Update(1, 1, size, l, r, val);
  }
  node Query(int u, int s, int e, int l, int r) {
    Push(u, s, e);
    if (e < l || r < s) { #change
      node mx = Make_node(0);
      return mx;
    }
    if (l <= s && e <= r) return st[u];
    int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
    node lsum = Query(v, s, m, l, r);
    node rsum = Query(w, m + 1, e, l, r);
    return Merge(lsum, rsum);
  }
  node Query(int l, int r) {
    return Query(1, 1, size, l, r);
  }
};
 
int main() {
  int n, q; cin >> n >> q;
  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) cin >> a[i];
 
  SegmentTreeLazy sg(n);
  sg.Build(a);
 
  while (q--) {
    int type; cin >> type;
    if (type == 1) {
      int l, r, v; cin >> l >> r >> v;
      sg.Update(l, r, v);
    } else {
      int k; cin >> k;
      cout << sg.Query(k, k).sum << '\n';
    }
  }
}